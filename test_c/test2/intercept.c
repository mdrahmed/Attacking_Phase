#include <stdio.h>
#include <dlfcn.h>

typedef int (*is_DIN_func)();

int intercepted_is_DIN() {
    printf("Intercepted is_DIN() function called\n");
    return 1;  // Change the return value to the desired value
}

int is_DIN() {
    is_DIN_func original_is_DIN = NULL;
    void* handle = dlopen("libc.so.6", RTLD_LAZY);  // Adjust the library name if needed
    if (handle) {
        original_is_DIN = (is_DIN_func)dlsym(handle, "is_DIN");
        dlclose(handle);
    }
    if (original_is_DIN)
        return original_is_DIN();
    else
        return 0;  // Return a default value if the original function couldn't be found
}

void __attribute__((constructor)) init() {
    printf("Interceptor initialized\n");
}

