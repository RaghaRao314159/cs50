#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int n = strlen(input);
    if (n == 1)
    {
        return input[0] - 48;
    }
    char new_input[n-1];

    for (int i = 0; i < n-1; i++)
    {
        new_input[i] = input[i];
    }

    return (input[n-1] - 48) + 10*convert(new_input);
    // TODO
}