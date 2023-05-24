#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <string>
#include <jnivm/vm.h>
#include <jnivm/env.h>
#include <fstream>
#include <sstream>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <string_view>

static const char* libandroidSymbols[] = {
	
"ANativeWindow_setBuffersTimestamp",
"ASensor_getFifoMaxEventCount",
"AConfiguration_getKeyboard",
"AConfiguration_match",
"ANativeWindow_setBuffersDataSpace",
"ASensorManager_createSharedMemoryDirectChannel",
"AMotionEvent_getYPrecision",
"ASensorManager_getSensorList",
"AConfiguration_copy",
"AMotionEvent_getX",
"AConfiguration_getScreenHeightDp",
"AMotionEvent_getY",
"ASensor_getResolution",
"ASensorManager_getInstance",
"ASurfaceTexture_getTimestamp",
"AChoreographer_getInstance",
"ANativeWindow_lock",
"AMotionEvent_getPressure",
"AInputQueue_attachLooper",
"AHardwareBuffer_fromHardwareBuffer",
"AConfiguration_setMnc",
"AMotionEvent_getAction",
"AKeyEvent_getMetaState",
"AAsset_close",
"AInputQueue_detachLooper",
"AMotionEvent_getDownTime",
"AMotionEvent_getXPrecision",
"ALooper_wake",
"AMotionEvent_getPointerCount",
"AStorageManager_delete",
"ATrace_isEnabled",
"AAssetManager_fromJava",
"AConfiguration_getLanguage",
"AMotionEvent_getOrientation",
"ASensor_isDirectChannelTypeSupported",
"AStorageManager_mountObb",
"AAsset_isAllocated",
"ANativeActivity_setWindowFormat",
"AConfiguration_getScreenWidthDp",
"AMotionEvent_getEdgeFlags",
"ASurfaceTexture_detachFromGLContext",
"AHardwareBuffer_recvHandleFromUnixSocket",
"AConfiguration_setCountry",
"AStorageManager_getMountedObbPath",
"AConfiguration_setScreenWidthDp",
"AKeyEvent_getScanCode",
"AObbInfo_getPackageName",
"AObbInfo_getVersion",
"ANativeWindow_getFormat",
"AMotionEvent_getHistoricalAxisValue",
"ASensorEventQueue_hasEvents",
"AAssetDir_close",
"AInputQueue_getEvent",
"AConfiguration_getScreenLong",
"AConfiguration_getUiModeNight",
"AMotionEvent_getHistoricalTouchMinor",
"AConfiguration_getCountry",
"AMotionEvent_getMetaState",
"ALooper_pollAll",
"ANativeWindow_setBuffersGeometry",
"AConfiguration_setScreenHeightDp",
"AHardwareBuffer_toHardwareBuffer",
"AMotionEvent_getButtonState",
"AHardwareBuffer_lock",
"AKeyEvent_getEventTime",
"AMotionEvent_getXOffset",
"ANativeWindow_acquire",
"AConfiguration_getScreenRound",
"AStorageManager_new",
"ASensor_getType",
"ASensorManager_createHardwareBufferDirectChannel",
"ANativeWindow_OemStorageGet",
"AAsset_openFileDescriptor",
"ASharedMemory_getSize",
"AConfiguration_isBetterThan",
"AConfiguration_setNavHidden",
"AConfiguration_getTouchscreen",
"ANativeWindow_setSwapInterval",
"AConfiguration_setSdkVersion",
"AAsset_read",
"AAsset_getRemainingLength64",
"AMotionEvent_getTouchMinor",
"AChoreographer_postFrameCallbackDelayed",
"AConfiguration_getKeysHidden",
"AKeyEvent_getKeyCode",
"ANativeActivity_setWindowFlags",
"AConfiguration_getOrientation",
"AInputEvent_getDeviceId",
"AMotionEvent_getToolMinor",
"AConfiguration_getScreenSize",
"AConfiguration_setDensity",
"AConfiguration_setUiModeType",
"ASensor_getMinDelay",
"ANativeWindow_queryf",
"ASensor_isWakeUpSensor",
"AConfiguration_getSmallestScreenWidthDp",
"AMotionEvent_getEventTime",
"ANativeWindow_setBuffersDimensions",
"AMotionEvent_getRawX",
"AMotionEvent_getRawY",
"ALooper_release",
"ASensorManager_configureDirectReport",
"AConfiguration_getMcc",
"ALooper_removeFd",
"ANativeWindow_fromSurface",
"AHardwareBuffer_release",
"AInputEvent_getSource",
"AStorageManager_isObbMounted",
"AConfiguration_setLayoutDirection",
"ASensorManager_createEventQueue",
"AMotionEvent_getHistoricalRawX",
"AMotionEvent_getHistoricalRawY",
"AConfiguration_delete",
"AConfiguration_setNavigation",
"ANativeWindowBuffer_getHardwareBuffer",
"ASurfaceTexture_fromSurfaceTexture",
"AObbInfo_delete",
"ASurfaceTexture_release",
"ATrace_beginSection",
"ANativeWindow_unlockAndPost",
"AConfiguration_setKeyboard",
"AMotionEvent_getHistorySize",
"ASensorManager_destroyEventQueue",
"android_getaddrinfofornetwork",
"AKeyEvent_getRepeatCount",
"AAsset_seek",
"ANativeWindow_setBufferCount",
"AConfiguration_diff",
"AMotionEvent_getHistoricalTouchMajor",
"AInputQueue_preDispatchEvent",
"ALooper_forThread",
"AAsset_getLength",
"AConfiguration_getDensity",
"ASharedMemory_create",
"ANativeWindow_queueBuffer",
"AAsset_getRemainingLength",
"AMotionEvent_getHistoricalX",
"AMotionEvent_getHistoricalY",
"ASharedMemory_dupFromJava",
"ASurfaceTexture_attachToGLContext",
"AKeyEvent_getAction",
"AMotionEvent_getFlags",
"AMotionEvent_getSize",
"AMotionEvent_getHistoricalToolMinor",
"ANativeWindow_setAutoRefresh",
"ANativeWindow_setBuffersTransform",
"ASensorEventQueue_getEvents",
"AHardwareBuffer_getNativeHandle",
"AMotionEvent_getHistoricalEventTime",
"ASensor_getHighestDirectReportRateLevel",
"ANativeWindow_setUsage",
"AMotionEvent_getTouchMajor",
"ALooper_pollOnce",
"ASensorManager_destroyDirectChannel",
"ASensor_getFifoReservedEventCount",
"AHardwareBuffer_unlock",
"ALooper_addFd",
"ASensorManager_getInstanceForPackage",
"ANativeWindow_cancelBuffer",
"AAssetManager_open",
"AAsset_seek64",
"AMotionEvent_getHistoricalSize",
"ANativeWindow_toSurface",
"AConfiguration_setSmallestScreenWidthDp",
"AInputQueue_finishEvent",
"AMotionEvent_getToolMajor",
"ASensorEventQueue_setEventRate",
"ANativeWindow_dequeueBuffer",
"ASensor_getName",
"AHardwareBuffer_acquire",
"ANativeWindow_getWidth",
"AHardwareBuffer_describe",
"AKeyEvent_getFlags",
"android_setsocknetwork",
"AConfiguration_setUiModeNight",
"ASensorManager_getDefaultSensorEx",
"AAssetManager_openDir",
"AConfiguration_setMcc",
"ASensor_getReportingMode",
"ANativeWindow_getBuffersDataSpace",
"ANativeActivity_hideSoftInput",
"AInputQueue_hasEvents",
"AConfiguration_setLanguage",
"AConfiguration_setScreenLong",
"AAssetDir_getNextFileName",
"AConfiguration_setScreenRound",
"ANativeWindow_setSharedBufferMode",
"AMotionEvent_getToolType",
"ANativeWindow_setBuffersFormat",
"AMotionEvent_getHistoricalPressure",
"AMotionEvent_getPointerId",
"AConfiguration_getNavHidden",
"AConfiguration_getLayoutDirection",
"ALooper_acquire",
"AHardwareBuffer_allocate",
"AConfiguration_getMnc",
"ANativeActivity_showSoftInput",
"AConfiguration_setTouchscreen",
"ASurfaceTexture_updateTexImage",
"ASensorEventQueue_enableSensor",
"AConfiguration_getSdkVersion",
"AAssetDir_rewind",
"AConfiguration_fromAssetManager",
"AConfiguration_setOrientation",
"ATrace_endSection",
"AConfiguration_getUiModeType",
"AInputEvent_getType",
"ASensorEventQueue_disableSensor",
"ASensor_getVendor",
"AAsset_openFileDescriptor64",
"AMotionEvent_getYOffset",
"ASurfaceTexture_acquireANativeWindow",
"AKeyEvent_getDownTime",
"ANativeWindow_query",
"AMotionEvent_getHistoricalToolMajor",
"AConfiguration_setScreenSize",
"ANativeActivity_finish",
"ALooper_prepare",
"AStorageManager_unmountObb",
"AConfiguration_getNavigation",
"ANativeWindow_getHeight",
"AAsset_getBuffer",
"AObbScanner_getObbInfo",
"android_setprocnetwork",
"ASurfaceTexture_getTransformMatrix",
"AHardwareBuffer_sendHandleToUnixSocket",
"AMotionEvent_getAxisValue",
"ASensorEventQueue_registerSensor",
"AChoreographer_postFrameCallback",
"AMotionEvent_getHistoricalOrientation",
"ASharedMemory_setProt",
"AAsset_getLength64",
"AConfiguration_new",
"ANativeWindow_OemStorageSet",
"AObbInfo_getFlags",
"ASensorManager_getDefaultSensor",
"ASensor_getStringType",
"AConfiguration_setKeysHidden",
"ANativeWindow_release",
	
	
};
void (*mcpelauncher_preinithook)(const char*sym, void*val, void **orig);

cmsghdr* ___cmsg_nxthdr(msghdr* msg, cmsghdr* cmsg) {
  cmsghdr* ptr;
  ptr = reinterpret_cast<cmsghdr*>(reinterpret_cast<char*>(cmsg) + CMSG_ALIGN(cmsg->cmsg_len));
  size_t len = reinterpret_cast<char*>(ptr+1) - reinterpret_cast<char*>(msg->msg_control);
  if (len > msg->msg_controllen) {
    return nullptr;
  }
  return ptr;
}

int (*__socket_org)(int affamily, int type, int protocol);
int __socket(int affamily, int type, int protocol) {
    switch(affamily) {
        case AF_INET:
        case AF_INET6:
            return socket(affamily, type, protocol);
        default:
            printf("socket EAFNOSUPPORT: socket(%lld, %lld, %lld)\n", (long long)affamily, (long long)type, (long long)protocol);
            errno = EAFNOSUPPORT;
            return -1;
    }
}

struct macOS_msghdr {
	void            *msg_name;      /* [XSI] optional address */
	socklen_t       msg_namelen;    /* [XSI] size of address */
	struct          iovec *msg_iov; /* [XSI] scatter/gather array */
	int             msg_iovlen;     /* [XSI] # elements in msg_iov */
	void            *msg_control;   /* [XSI] ancillary data, see below */
	socklen_t       msg_controllen; /* [XSI] ancillary data buffer len */
	int             msg_flags;      /* [XSI] flags on received message */
};
struct macOS_cmsghdr {
	socklen_t       cmsg_len;       /* [XSI] data byte count, including hdr */
	int             cmsg_level;     /* [XSI] originating protocol */
	int             cmsg_type;      /* [XSI] protocol-specific type */
/* followed by	unsigned char  cmsg_data[]; */
};

ssize_t __sendmsg(int socket, const struct msghdr *message, int flags) {
    macOS_msghdr mmessage;
    if(message->msg_namelen > 0) {
        printf("sendmsg message->msg_namelen > 0: %lld\n", (long long)message->msg_controllen);
    }
    mmessage.msg_name = nullptr; //message->msg_name;
    mmessage.msg_namelen = 0; //message->msg_namelen
    mmessage.msg_iov = message->msg_iov;
    mmessage.msg_iovlen = (decltype(mmessage.msg_iovlen))message->msg_iovlen;
    if(message->msg_controllen > 0) {
        printf("sendmsg message->msg_controllen > 0: %lld\n", (long long)message->msg_controllen);
    }
    mmessage.msg_control = nullptr;
    mmessage.msg_controllen = 0;
    mmessage.msg_flags = message->msg_flags;
    auto ret = sendmsg(socket, (struct msghdr *)&mmessage, flags);
    return ret;
}

ssize_t __recvmsg(int socket, struct msghdr *message, int flags) {
    macOS_msghdr mmessage;
    if(message->msg_namelen > 0) {
        printf("recvmsg message->msg_namelen > 0: %lld\n", (long long)message->msg_controllen);
    }
    mmessage.msg_name = nullptr; //message->msg_name;
    mmessage.msg_namelen = 0; //message->msg_namelen
    mmessage.msg_iov = message->msg_iov;
    mmessage.msg_iovlen = (decltype(mmessage.msg_iovlen))message->msg_iovlen;
    if(message->msg_controllen > 0) {
        printf("recvmsg message->msg_controllen > 0: %lld\n", (long long)message->msg_controllen);
    }
    mmessage.msg_control = nullptr;
    mmessage.msg_controllen = 0;
    mmessage.msg_flags = message->msg_flags;
    auto ret = recvmsg(socket, (struct msghdr *)&mmessage, flags);
    if(mmessage.msg_namelen > 0) {
        printf("recvmsg mmessage.msg_namelen > 0: %lld\n", (long long)mmessage.msg_controllen);
    }
    message->msg_name = nullptr; //mmessage.msg_name;
    message->msg_namelen = 0; //mmessage.msg_namelen
    message->msg_iov = mmessage.msg_iov;
    message->msg_iovlen = (decltype(message->msg_iovlen))mmessage.msg_iovlen;
    if(mmessage.msg_controllen > 0) {
        printf("recvmsg mmessage.msg_controllen > 0: %lld\n", (long long)mmessage.msg_controllen);
    }
    message->msg_control = nullptr;
    message->msg_controllen = 0;
    message->msg_flags = mmessage.msg_flags;
    return ret;
}

int __ioctl(int fd, unsigned long cmd, void *arg) {
    switch(cmd) {
        case FIONBIO:
        case SIOCGIFNETMASK:
        case SIOCGIFCONF:
            return ioctl(fd, cmd, arg);
        default:
            printf("ioctl no support: %lld\n", (long long)cmd);
            errno = EINVAL;
            return -1;
    }
}

extern "C" void __attribute__ ((visibility ("default"))) mod_preinit() {
    auto h = dlopen("libmcpelauncher_mod.so", 0);
    if(!h) {
        return;
    }
    mcpelauncher_preinithook = (decltype(mcpelauncher_preinithook)) dlsym(h, "mcpelauncher_preinithook");
    dlclose(h);
    mcpelauncher_preinithook("__cmsg_nxthdr", (void*)&___cmsg_nxthdr, nullptr);
    mcpelauncher_preinithook("socket", (void*)&__socket, nullptr);
    mcpelauncher_preinithook("sendmsg", (void*)&__sendmsg, nullptr);
    mcpelauncher_preinithook("recvmsg", (void*)&__recvmsg, nullptr);
    mcpelauncher_preinithook("ioctl", (void*)&__ioctl, nullptr);
	
	
    auto libandroid = dlopen("libandroid.so", 0);
    for(size_t i = 0; i < sizeof(libandroidSymbols) / sizeof(*libandroidSymbols); i++) {
        if(!dlsym(libandroid, libandroidSymbols[i])) {
            mcpelauncher_preinithook(libandroidSymbols[i], (void*)+[]() {
                printf("libandroidSymbols stub called, provided by a mod");
            }, nullptr);
        }
    }
    static std::map<std::string_view, void(*)()> modoverrides = { { "glVertexAttribDivisorOES", nullptr}, { "glDrawArraysInstancedOES", nullptr}, { "glDrawElementsInstancedOES", nullptr} } };
    auto libEGL = dlopen("libEGL.so", 0);    
    static void (* eglGetProcAddress(char const * procname))(void) = (decltype(eglGetProcAddress))dlsym(libEGL, "eglGetProcAddress");
    mcpelauncher_preinithook("eglGetProcAddress", (void*)+[](char const * procname) -> void(*)() {
        auto iter = modoverrides.find(procname);
        if(iter != modoverrides.end()) {
            return *iter;
        }
        return eglGetProcAddress(procname);
    });
}
