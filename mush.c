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
            // printf("Word %d is %s\n", i, token);
            command_words[i] = token;
            token = strtok(NULL, delimiter);
            i++;
        }
        command_words[i] = NULL;

        // get the arg count
        // int word_count = i;
        // printf("Word count is %d\n", word_count);

        // for (int i = 0; i < word_count; i++)
        //     printf("%s\n", command_words[i]);

        pid_t pid = fork();

        if (pid == 0)
        {
            // child process
            printf("Child process running: %s\n", command_words[0]);

            execvp(command_words[0], command_words);
            perror("exec");
            exit(0); // success!
        }

        wait(NULL);
        printf("done!\n");
    }
    return 0;
}