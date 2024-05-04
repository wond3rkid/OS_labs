#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

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

void buffer_address() {
    char *buffer = malloc(sizeof(char) * 100);
    assert(buffer != NULL);
    strcpy(buffer, "hello world, i like os");
    printf("String in first buffer before free: %s \n", buffer);
    free(buffer);
    printf("String in first buffer after free: %s \n", buffer);

    char *new_buffer = malloc(sizeof(char) * 100);
    strcpy(new_buffer, "have a good day, if u like os veryveryveryvery much and i hope u 2");
    printf("String in second buffer before free: %s \n", new_buffer);

    char *middle_buffer = (new_buffer + 50);

    printf("Content from the start of the second buffer: %s \n", new_buffer);
    printf("Content in the middle of the second buffer: %s \n", middle_buffer);
    free(middle_buffer);
    printf("Content from the start of the second buffer after free: %s \n", new_buffer);
    free(new_buffer);
}

void env_varible() {
    printf("Environment variable value: %s\n", getenv("MY_VAR"));
    setenv("MY_VAR", "i hope u love os, too", 1);
    printf("New environment variable value: %s\n", getenv("MY_VAR"));
}

int main() {
    pid_t pid = getpid();
    printf("PID of this process : %d \n\n", pid);
//    print_locals();
//    print_statics();
//    print_constants();
//    print_globals();
//    sleep(10); // для вывода proc/pid/maps
//
//    printf("Variable address in main: %p \n\n", (void *) variable_address());
//    sleep(10);
//    buffer_address();
    //sleep(10);
    env_varible();
    return 0;
}