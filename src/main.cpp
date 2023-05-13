#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <string>
#include <fstream>
#include <sstream>


extern "C" void __attribute__ ((visibility ("default"))) mod_preinit() {
    printf("Fake init\n");
    printf("Fake deinit\n");
}
