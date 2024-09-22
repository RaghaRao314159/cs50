#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);


    //build height number of rows
    for (int i = 1; i <= height; i++)
    {
        //each row starts with spaces
        for (int m = 1; m <= height - i; m++)
        {
            printf(" ");
        }

        //add hashes
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}