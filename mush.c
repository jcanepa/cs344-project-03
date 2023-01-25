#include <stdio.h>    // printf, fgets, perror
#include <stdlib.h>   // exit
#include <string.h>   // strtok, strcmp
#include <unistd.h>   // fork, execvp
#include <sys/wait.h> // wait

void print_prompt(void)
{
    printf("$ ");
}

int main(int argc, char const *argv[])
{
    while (1)
    {
        print_prompt();

        /**
         * Get text from stdin
         */
        char str[100];
        fgets(str, 100, stdin);
        printf("🦜 %s\n", str);

        /**
         * Separate str into individual words
         */
        char delimiter[2] = " ";
        char *token = strtok(str, delimiter);

        /**
         * Add words to an array
         */
        int i = 0;
        const char *command_words[5];

        while (token != NULL)
        {
            command_words[i] = token;
            i++;
            printf("Command parts are: %s\n", token);
            token = strtok(NULL, delimiter);
        }
        // terminate the array
        command_words[i] = "\0";

        // Next: make it into a command...
    }
    return 0;
}