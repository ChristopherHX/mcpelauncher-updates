#include <dlfcn.h>
#include <malloc.h>

extern "C" void __attribute__ ((visibility ("default"))) mod_preinit() {
    auto h = dlopen("libmcpelauncher_mod.so", 0);
    if(!h) {
        return;
    }
    void (*mcpelauncher_preinithook)(const char*sym, void*val, void **orig);
    mcpelauncher_preinithook = (decltype(mcpelauncher_preinithook)) dlsym(h, "mcpelauncher_preinithook");
    mcpelauncher_preinithook("malloc", (void*)+[](size_t s) {
	return malloc(s + 64);
    }, nullptr);
}
