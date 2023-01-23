#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    printf("Before fork...\n");

    // makes a new process that's a copy of the current process
    pid_t pid = fork();

    // if we run this again, both parent and child will create a child (4 total)
    // fork();

    // printf("Fork returned %d\n", pid);

    if (pid == 0)
    {
        // child
        // printf("Child PID is %d\n", getpid());
        // printf("Child parent PID is %d\n", getppid());

        char *new_argv[] = {"ls", "-a", "-l", "/usr/bin", NULL};

        execvp("ls", new_argv);

        perror("exec");
        exit(0);
    }

    // parent
    wait(NULL); // use null when we don't care about the exit status
    // os wakes parent when one of child processes dies

    // printf("Parent PID is %d\n", getpid());
    // printf("Parent child PID is %d\n", pid);

    // this is run 2^ (times fork was run)
    printf("All done!\n");
}