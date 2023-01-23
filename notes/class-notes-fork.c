#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Before fork\n");

    // makes a new process that's a copy of the current process
    fork();

    printf("After fork\n");
}