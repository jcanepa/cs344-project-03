#include <stdio.h>    // printf, fgets, perror
#include <stdlib.h>   // exit
#include <string.h>   // strtok, strcmp
#include <unistd.h>   // fork, execvp
#include <sys/wait.h> // wait

void print_prompt(void) { printf("$ "); }

int main(void)
{
    while (1) // until the user quits (control c)
    {
        print_prompt();

        /**
         * Get text from stdin
         */
        char str[2048];
        fgets(str, 2048, stdin);
        // printf("🦜 %s\n", str);

        if (strcmp(str, "exit\n") == 0) // end shell on `exit`
            exit(0);

        /**
         * Separate command into words
         */
        char delimiter[2] = " ";
        char *token = strtok(str, delimiter);

        int i = 0;
        char *command_words[128];

        while (token != NULL)
        {
            command_words[i] = token;
            token = strtok(NULL, delimiter);
            i++;
        }
        // delete new line char on last word
        strtok(command_words[i - 1], "\n");

        command_words[i] = "/usr/bin";
        command_words[i + 1] = NULL;

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

        if (strcmp(command_words[0], "cd\n") == 0)
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

            // char *new_argv[] = {
            //     "ls",
            //     "-a",
            //     "-h",
            //     "/Users/jcanepa/code/cs344-project-03",
            //     NULL};
            // execvp("ls", new_argv);

            perror("exec");
            exit(1); // failure
        }

        wait(NULL);
    }
    return 0;
}