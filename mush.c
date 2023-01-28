#include <stdio.h>    // printf, fgets, perror
#include <stdlib.h>   // exit
#include <string.h>   // strtok, strcmp
#include <unistd.h>   // fork, execvp
#include <sys/wait.h> // wait

void print_prompt(void)
{
    printf("$ ");
}

int main(void)
{
    // until the user quits (control c)
    while (1)
    {
        // 1. print a prompt
        // 2. read a line fgets()
        // 3. parse down to individual words strtok()
        // 4. put words into char* aray
        // 5. terminate array with NULL
        // 6. call execvp() on words array

        print_prompt();

        /**
         * Get text from stdin
         */
        char str[2048];
        fgets(str, 2048, stdin);
        printf("🦜 %s\n", str);

        // end execution on `exit`
        if (strcmp(str, "exit\n") == 0)
            break;

        /**
         * Separate command into individual words
         */
        char delimiter[2] = " ";
        char *token = strtok(str, delimiter);

        int i = 0;
        char *command_words[128];

        while (token != NULL)
        {
            command_words[i] = token;
            printf("Word %d is %s\n", i, token);
            i++;
            token = strtok(NULL, delimiter);
        }
        // command_words[i] = '\0';

        // for (unsigned long i = 0; i < sizeof(command_words); i++)
        //     printf("%s ", command_words[i]);

        // pid_t pid = fork();

        // if (pid == 0)
        // {
        //     // child process
        //     printf("Child process running: %s\n", command_words[0]);

        //     execvp("foo", command_words);
        //     perror("exec");
        //     exit(0); // success!
        // }

        // wait(NULL);
        // printf("done!\n");
    }
    return 0;
}