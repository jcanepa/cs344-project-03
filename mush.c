#include <stdio.h>    // printf, fgets, perror
#include <stdlib.h>   // exit
#include <string.h>   // strtok, strcmp
#include <unistd.h>   // fork, execvp
#include <sys/wait.h> // wait

int main(int argc, char const *argv[])
{
    while (1)
    {
        printf("going...");
    }
    return 0;
}
