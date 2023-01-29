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

        if (strcmp(str, "exit\n") == 0) // end on `exit`
            break;

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
         * Create a child process to run the command
         */
        pid_t process_id = fork();

        if (process_id == 0)
        {
            // printf(
            //     "Child process to run %s\n",
            //     command_words[0]);

            execvp("ls", command_words);
            perror("exec");
            exit(0); // success!
        }

        wait(NULL);
    }
    return 0;
}