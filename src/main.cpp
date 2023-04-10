#include <cstring>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include "../libjnivm/include/jni.h"

static const char * SkipJNIType(const char *cur, const char *end) {
    switch (*cur) {
    case 'V':
            // Void has size 0 ignore it
            break;
    case 'Z':
    case 'B':
    case 'S':
    case 'C':
    case 'I':
    case 'J':
    case 'F':
    case 'D':
            break;
    case '[':
            cur = SkipJNIType(cur + 1, end) - 1;
            break;
    case 'L':
            cur = std::find(cur, end, ';');
            break;
    case '(':
            return SkipJNIType(cur + 1, end);
    }
    return cur + 1;
}

static std::vector<jvalue> JValuesfromValist(va_list list, const char* signature) {
	auto org = signature;
	const char* end = signature + strlen(signature);
	std::vector<jvalue> values;
	if(signature[0] != '(') {
		throw std::invalid_argument("Signature doesn't begin with '(' " + std::string(signature));
	}
	signature++;
	for(size_t i = 0; *signature != ')' && signature != end; ++i) {
		values.emplace_back();
		switch (*signature) {
		case 'V':
				// Void has size 0 ignore it
				break;
		case 'Z':
				// These are promoted to int (gcc warning)
				values.back().z = (jboolean)va_arg(list, int);
				break;
		case 'B':
				// These are promoted to int (gcc warning)
				values.back().b = (jbyte)va_arg(list, int);
				break;
		case 'S':
				// These are promoted to int (gcc warning)
				values.back().s = (jshort)va_arg(list, int);
				break;
		case 'C':
				// These are promoted to int (gcc warning)
				values.back().c = (jchar)va_arg(list, int);
				break;
		case 'I':
				values.back().i = va_arg(list, jint);
				break;
		case 'J':
				values.back().j = va_arg(list, jlong);
				break;
		case 'F':
				values.back().f = (jfloat)va_arg(list, jdouble);
				break;
		case 'D':
				values.back().d = va_arg(list, jdouble);
				break;
		case '[':
				signature = SkipJNIType(signature + 1, end) - 1;
				values.back().l = va_arg(list, jobject);
				break;
		case 'L':
				signature = std::find(signature, end, ';');
				if(signature == end) {
					throw std::invalid_argument("Signature missing ';' after 'L'");
				}
				values.back().l = va_arg(list, jobject);
				break;
		}
		signature++;
	}
	return values;
}

extern "C" const char* (*GetJMethodIDSignature)(jmethodID id);

template <class T, class...Y> struct MDispatchBase {
    static T CallMethod(JNIEnv * env, Y...p, jmethodID id, va_list param);
};

template<class S, size_t i, class...Ts> struct TypeIndex {
    static const constexpr int Index = -1;
};

template<class S, size_t i, class T, class...Ts> struct TypeIndex<S, i, T, Ts...> {
    static const constexpr int Index = std::is_same_v<S, T> ? i : TypeIndex<S, i + 1, Ts...>::Index;
};

template <class T> struct MDispatchBase2 {
    static T CallMethod(JNIEnv * env, jobject obj, jmethodID id, jvalue * param) __attribute__((weak));
    static T CallMethod(JNIEnv * env, jobject obj, jclass cl, jmethodID id, jvalue * param) __attribute__((weak));
    static T CallMethod(JNIEnv * env, jclass cl, jmethodID id, jvalue * param) __attribute__((weak));

    static T CallMethodT(JNIEnv * env, jobject obj, jmethodID id, jvalue * param) {
        return ((T(*)(JNIEnv * env, jobject obj, jmethodID id, jvalue * param))(((void**)env->functions)[offsetof(JNINativeInterface, CallObjectMethodA) + 3 * TypeIndex<T, 0, jobject, jboolean, jbyte, jchar, jshort, jint, jlong, jfloat, jdouble, void>::Index]))(env, obj, id, param);
    }
    static T CallMethodT(JNIEnv * env, jobject obj, jclass cl, jmethodID id, jvalue * param) {
        return ((T(*)(JNIEnv * env, jobject obj, jclass cl, jmethodID id, jvalue * param))(((void**)env->functions)[offsetof(JNINativeInterface, CallNonvirtualObjectMethodA) + 3 * TypeIndex<T, 0, jobject, jboolean, jbyte, jchar, jshort, jint, jlong, jfloat, jdouble, void>::Index]))(env, obj, cl, id, param);
    }
    static T CallMethodT(JNIEnv * env, jclass cl, jmethodID id, jvalue * param) {
        return ((T(*)(JNIEnv * env, jclass cl, jmethodID id, jvalue * param))(((void**)env->functions)[offsetof(JNINativeInterface, CallStaticObjectMethodA) + 3 * TypeIndex<T, 0, jobject, jboolean, jbyte, jchar, jshort, jint, jlong, jfloat, jdouble, void>::Index]))(env, cl, id, param);
    }
};

template <class T, class...Y> struct MDispatch : MDispatchBase<T, Y...>, MDispatchBase2<T> {
    using MDispatchBase<T, Y...>::CallMethod;
    using MDispatchBase2<T>::CallMethod;
    static T CallMethod(JNIEnv * env, Y...p, jmethodID id, ...);
};

template <class...Y> struct MDispatch<void, Y...> : MDispatchBase<void, Y...>, MDispatchBase2<void> {
    using MDispatchBase<void, Y...>::CallMethod;
    using MDispatchBase2<void>::CallMethod;
    static void CallMethod(JNIEnv * env, Y...p, jmethodID id, ...);
};

template<class ...jnitypes> struct JNINativeInterfaceCompose;
template<class X, class ...jnitypes> struct JNINativeInterfaceCompose<X, jnitypes...> {
	using Type = decltype(std::tuple_cat(std::declval<std::tuple<X, X, X>>(), std::declval<typename JNINativeInterfaceCompose<jnitypes...>::Type>()));
};
template<> struct JNINativeInterfaceCompose<> {
	using Type = std::tuple<>;
	template<class Y> using index = std::integral_constant<size_t, 0>;	
};

template<size_t Y> struct NullTemplate {
    static constexpr void* value = NULL;
};

template<class T, class... Y> T MDispatchBase<T, Y...>::CallMethod(JNIEnv *env, Y ...p, jmethodID id, va_list param) {
    return MDispatch<T, Y...>::CallMethodT(env, p..., id, id ? JValuesfromValist(param, GetJMethodIDSignature(id)).data() : nullptr);
};

template<class T, class... Y> T MDispatch<T, Y...>::CallMethod(JNIEnv *env, Y ...p, jmethodID id, ...) {
    va_list l;
    va_start(l, id);
    T ret = MDispatch<T, Y...>::CallMethod(env, p..., id, l);
    va_end(l);
    return ret;
};

template<class... Y> void MDispatch<void, Y...>::CallMethod(JNIEnv *env, Y ...p, jmethodID id, ...) {
    va_list l;
    va_start(l, id);
    MDispatch<void, Y...>::CallMethod(env, p..., id, l);
    va_end(l);
};

template<class ...jnitypes> struct InterfaceFactory {
	using SeqM2 = std::make_index_sequence<sizeof...(jnitypes) - 2>;
	using SeqM1 = std::make_index_sequence<sizeof...(jnitypes) - 1>;
	using Seq = std::make_index_sequence<sizeof...(jnitypes) * 3>;
	using compose = JNINativeInterfaceCompose<jnitypes...>;
	using composeType = typename compose::Type;
	template<class seq> struct Impl;
	template<size_t...I> struct Impl<std::integer_sequence<size_t, I...>> {
		template<class seq> struct Impl2;
		template<size_t...IM2> struct Impl2<std::integer_sequence<size_t, IM2...>> {
			template<class seq> struct Impl3;
			template<size_t...IM1> struct Impl3<std::integer_sequence<size_t, IM1...>> {
				static constexpr JNINativeInterface Get() {
					return {
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
						MDispatch<jobject, jclass>::CallMethod,
						MDispatch<jobject, jclass>::CallMethod,
						MDispatch<jobject, jclass>::CallMethod,
						NULL,
						NULL,
						NULL,
						MDispatch<std::tuple_element_t<I, composeType>, jobject>::CallMethod ...,
						MDispatch<std::tuple_element_t<I, composeType>, jobject, jclass>::CallMethod ...,
						NULL,
						(NullTemplate<IM1>::value ? nullptr : nullptr)...,
						(NullTemplate<IM1>::value ? nullptr : nullptr)...,
						NULL,
						MDispatch<std::tuple_element_t<I, composeType>, jclass>::CallMethod ...,
					};
				}
			};
		};
	};
	using Type = typename Impl<Seq>::template Impl2<SeqM2>::template Impl3<SeqM1>;
};

JNINativeInterface GetNativeInterfaceTemplate() {
	return InterfaceFactory<jobject, jboolean, jbyte, jchar, jshort, jint, jlong, jfloat, jdouble, void>::Type::Get();
}

void PatchJNINativeInterface(JNINativeInterface& interface) {
    auto tmpl = GetNativeInterfaceTemplate();
    for(int i = 0; i < sizeof(tmpl) / sizeof(void*); i++) {
        if(((void**)&tmpl)[i]) {
            ((void**)&interface)[i] = ((void**)&tmpl)[i];
        }
    }
}

