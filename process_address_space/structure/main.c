#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

int global_int = 10;
int global_var;
const int global_const = 2;

void print_locals() {
    printf("Local variables in function: \n");
    int a;
    long long b;
    char c;
    float d;
    printf("int 'a' and its address: %p \n", (void *) &a);
    printf("long long 'b' and its address: %p \n", (void *) &b);
    printf("char 'c' and its address: %p \n", (void *) &c);
    printf("float 'd' and its address: %p \n\n", (void *) &d);
}

void print_statics() {
    printf("Static variables in function: \n");
    static int a;
    static long long b;
    static char c;
    static float d;
    printf("int 'a' and its address: %p \n", (void *) &a);
    printf("long long 'b' and its address: %p \n", (void *) &b);
    printf("char 'c' and its address: %p \n", (void *) &c);
    printf("float 'd' and its address: %p \n\n", (void *) &d);
}

void print_constants() {
    printf("Const variables in function: \n");
    const int a;
    const long long b;
    const char c;
    const float d;
    printf("int 'a' and its address: %p \n", (void *) &a);
    printf("long long 'b' and its address: %p \n", (void *) &b);
    printf("char 'c' and its address: %p \n", (void *) &c);
    printf("float 'd' and its address: %p \n\n", (void *) &d);
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

int main() {
    print_locals();
    print_statics();
    print_constants();
    print_globals();
    printf("Variable address in main: %p \n", (void *) variable_address());
    //buffer_address(); // there is a problem with free in func have to be checked
    return 0;
}