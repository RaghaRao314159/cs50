#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    int root = sqrt(number);
    if (number == 2)
    {
        return true;
    }
    else if (number%2 == 0 || number == 1)
    {
        return false;
    }
    for (int j = 3;j <= root; j+=2)
    {
        if (!(number%j))
        {
            return false;
        }
    }

    return true;
}
