#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>

int main() {
    pid_t pid;
    int status;
    struct user_regs_struct regs;

    pid = fork();

    if (pid == 0) {
        // Child process
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("./e", "example", NULL);
    } else {
        // Parent process
        wait(&status);
        ptrace(PTRACE_GETREGS, pid, NULL, &regs);
        printf("Original value of b: %ld\n", regs.rdi);
        
        // Modify the value of x
        long new_value = 20;
        regs.rdi = new_value;
        ptrace(PTRACE_SETREGS, pid, NULL, &regs);
        printf("Modified value of b: %ld\n", regs.rdi);
        
        // Resume the execution of the running program
        ptrace(PTRACE_CONT, pid, NULL, NULL);
        wait(&status);
    }

    return 0;
}

