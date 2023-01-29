#include <stdio.h>
#include <string.h> // for strtok()

int main(void)
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