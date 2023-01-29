#include <stdio.h>    // printf, fgets, perror
#include <stdlib.h>   // exit
#include <string.h>   // strtok, strcmp
#include <unistd.h>   // fork, execvp
#include <sys/wait.h> // wait

int main(void)
{

    while (1) // until the user quits (control c)
    {
        char cwd[100];
        getcwd(cwd, 100);

        printf("$ ");

        /**
         * Get text from stdin
         */
        char str[2048];
        fgets(str, 2048, stdin);
        // printf("🦜 %s\n", str);      // parrot it back

        if (strcmp(str, "exit\n") == 0) // end shell on `exit`
            exit(0);

        /**
         * Separate command into words
         */
        int i = 0;
        char delimiter[2] = " ";
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
         * Print words
         */
        // int word_count = i;
        // printf("Word count is %d\n", word_count);
        // for (int i = 0; i < word_count; i++)
        //     printf("%s\n", command_words[i]);

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
            // printf(
            //     "Child process to run %s\n",
            //     command_words[0]);

            execvp(command_words[0], command_words);

            perror("exec");
            exit(1); // failure
        }

        wait(NULL);
    }
    return 0;
}