#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("input start size of population greater than 8: ");
    }
    while (start_size < 9);


    // TODO: Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("input end size of population greater than start size: ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    int size = start_size;
    int years = 0;
    while (size < end_size)
    {
        int grow = size / 3;
        int dead = size / 4;
        size = size + grow - dead;
        years += 1;

    }

    // TODO: Print number of years
    printf("Years: %i \n", years);
}
