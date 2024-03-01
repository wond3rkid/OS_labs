#include <stdio.h>
#include <dlfcn.h>

void runtime_hello() {
	void *handle;
	void (*print_hello)(void);
	
	handle = dlopen("./lib_runtime_hello.so", RTLD_LAZY);
	if (!handle) {
		printf("You have a problem with opening library.so: %s\n", dlerror());
		return;
	}

	print_hello = (void (*)(void))dlsym(handle, "hello_from_dynamic_runtime_lib");

	if (!print_hello) {
		printf("Error with function: %s", dlerror());
		return;
	}
	print_hello();
	dlclose(handle);
}

int main() {
	runtime_hello();
	return 0;
}

