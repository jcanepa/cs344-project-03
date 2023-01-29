#include <stdio.h>
#include <string.h> // for strtok()

int main_0(void)
{
    char s[] = "  This  is a   test!   ";
    char *token;

    token = strtok(s, " "); // First
    printf("%s\n", token);

    token = strtok(NULL, " "); // Subsequent
    printf("%s\n", token);

    token = strtok(NULL, " "); // Subsequent
    printf("%s\n", token);
}

int main(void)
{
    char s[2048];

    printf("Enter something: ");
    fflush(stdout);
    fgets(s, sizeof s, stdin);

    char *token;

    if ((token = strtok(s, " \t\n\r")) != NULL)
    {
        do
        {
            printf("Token: \"%s\"\n", token);
        } while ((token = strtok(NULL, " \t\n\r")) != NULL);
    }
}