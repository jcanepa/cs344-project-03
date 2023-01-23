#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Before exec\n");

    // an array of strings (pointer to a pointer)
    char *new_argv[] = {
        "ls", // program identifier (doesn't matter as label below)
        NULL  // zero/null-pointer, cannot dereference it or crash, indicates args are over (because we don't pass the arg count into execvp)
    };

    // will replace the current running program with this new child
    execvp(
        "ls", // process name (this matters)
        new_argv);
    // orgiginal program is gone by now

    // never gets here because
    printf("After exec\n");
}
