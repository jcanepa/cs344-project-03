#include <stdio.h>

int main(void)
{
    char s[2048];

    printf("Enter something: ");

    fflush(stdout); // Make sure the prompt is displayed

    fgets(s, sizeof s, stdin); // Read a line from stdin

    printf("s is \"%s\"\n", s);
}