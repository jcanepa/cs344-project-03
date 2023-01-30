#include <stdio.h>    // printf, fgets, perror
#include <stdlib.h>   // exit
#include <string.h>   // strtok, strcmp
#include <unistd.h>   // fork, execvp
#include <sys/wait.h> // wait

int main(void)
{

    // until the user quits (control c)
    while (1)
    {
        char cwd[100];
        getcwd(cwd, 100);

        printf("%s $ ", cwd);

        /**
         * Get text from stdin
         */
        char str[2048];
        fgets(str, 2048, stdin);

        // end shell on `exit` command
        if (strcmp(str, "exit\n") == 0)
            exit(0);

        /**
         * Separate command into words, split on any word boundary
         */
        int i = 0;
        char delimiter[4] = " \t\n\r";
        char *command_words[128];
        char *token = strtok(str, delimiter);

        while (token != NULL)
        {
            command_words[i] = token;
            token = strtok(NULL, delimiter);
            i++;
        }

        // delete new line char on last word
        strtok(command_words[i - 1], "\n");

        if (strcmp(command_words[0], "ls") == 0)
        {
            command_words[i] = cwd;
            command_words[i + 1] = NULL;
        }
        else
        {
            command_words[i] = NULL;
        }

        /**
         * Handle `cd`
         */
        int result;

        if ((strcmp(command_words[0], "cd") == 0))
        {
            result = chdir(command_words[1]);

            if (result == -1)
                perror("chdir");
        }

        /**
         * Create a child process to run the command
         */
        pid_t process_id = fork();

        if (process_id == 0)
        {
            execvp(command_words[0], command_words);

            // handle failure
            perror("exec");
            exit(1);
        }

        wait(NULL);
    }
    return 0;
}