#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_int = 10;
int global_var;
const int global_const = 2;

void print_locals() {
    printf("Local variables in function: \n");
    int local_a;
    long long local_b;
    char local_c;
    float local_d;
    printf("int 'a' and its address: %p \n", (void *) &local_a);
    printf("long long 'b' and its address: %p \n", (void *) &local_b);
    printf("char 'c' and its address: %p \n", (void *) &local_c);
    printf("float 'd' and its address: %p \n\n", (void *) &local_d);
}

void print_statics() {
    printf("Static variables in function: \n");
    static int static_a;
    static long long static_b;
    static char static_c;
    static float static_d;
    printf("int 'a' and its address: %p \n", (void *) &static_a);
    printf("long long 'b' and its address: %p \n", (void *) &static_b);
    printf("char 'c' and its address: %p \n", (void *) &static_c);
    printf("float 'd' and its address: %p \n\n", (void *) &static_d);
}

void print_constants() {
    printf("Const variables in function: \n");
    const int const_a;
    const long long const_b;
    const char const_c;
    const float const_d;
    printf("int 'a' and its address: %p \n", (void *) &const_a);
    printf("long long 'b' and its address: %p \n", (void *) &const_b);
    printf("char 'c' and its address: %p \n", (void *) &const_c);
    printf("float 'd' and its address: %p \n\n", (void *) &const_d);
}

void print_globals() {
    printf("Global variables in function: \n");
    printf("int 'global_int' and its address: %p \n", (void *) &global_int);
    printf("int 'global_var' and its address: %p \n", (void *) &global_var);
    printf("int 'global_const' and its address: %p \n\n", (void *) &global_const);
}


int *variable_address() {
    int a = 10;
    printf("Variable address in func: %p \n", (void *) &a);
    return &a;
}

int main() {
    pid_t pid = getpid();
    printf("PID of this process : %d \n\n", pid);

    print_locals();
    print_statics();
    print_constants();
    print_globals();
    sleep(10); // для вывода proc/pid/maps

    printf("Variable address in main: %p \n\n", (void *) variable_address());
    return 0;
}