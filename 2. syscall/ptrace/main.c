#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void run_child(const char *program_name) {
    printf("Prog to run '%s'\n", program_name);
    if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) < 0) {
        perror("ptrace");
        exit(1);
    }
    int execl_err = execl(program_name, program_name, NULL);
    if (execl_err == -1) {
        perror("execv");
        exit(1);
    }
}

void run_parent(pid_t child_pid) {
    int wait_status;
    unsigned long long syscall;
    wait(&wait_status);
    while (WIFSTOPPED(wait_status)) {
        struct user_regs_struct regs;
        if (ptrace(PTRACE_SYSCALL, child_pid, 0, 0) < 0) {
            perror("ptrace");
            exit(1);
        }
        wait(&wait_status);
        if (WIFEXITED(wait_status)) {
            break;
        }
        if (ptrace(PTRACE_GETREGS, child_pid, 0, &regs) < 0) {
            perror("ptrace");
            exit(1);
        }
        syscall = regs.orig_rax;
        printf("Current syscall: %llu\n", syscall);
        if (ptrace(PTRACE_SYSCALL, child_pid, 0, 0) < 0) {
            perror("ptrace");
            exit(1);
        }
        wait(&wait_status);
    }
}

int main(int argc, char *argv[]) {
    pid_t child_pid;
    if (argc < 2) {
        fprintf(stderr, "Use: ./<this programm> <program to run>\n");
        return 1;
    }
    child_pid = fork();
    if (child_pid == 0) {
        run_child(argv[1]);
    } else if (child_pid > 0) {
        run_parent(child_pid);
    } else {
        perror("fork");
        return 1;
    }
    return 0;
}
