#include <cs50.h>
#include <stdio.h>
#include <math.h>

//helper function that adds digits in a number
int sum_digits(int x);

//function that checks validity using Luhn's Algo
bool valid(long number, int len);

int main(void)
{
    // obtain credit card number
    long number;
    int len;

    number = get_long("Number: ");
    len = log10(number) + 1;

    // determine first 2 digits
    int first_2 = number / pow(10, (len - 2));
    int first = first_2 / 10;


    if (valid(number, len))
    {
        if (len == 15 && (first_2 == 34 || first_2 == 37))
        {
            printf("AMEX\n");
        }
        else if (len == 16 && first_2 > 50 && first_2 < 56)
        {
            printf("MASTERCARD\n");
        }
        else if ((len == 16 || len == 13) && first == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }



}

int sum_digits(int x)
{
    //loops through all digits in x and returns sum
    // needed for 'valid' function below
    int res = 0;
    while (x > 0)
    {
        res += x % 10;
        x /= 10;
    }
    return res;
}


bool valid(long number, int len)
{
    //Luhn's Algorithm
    int even_sum = 0;
    int odd_sum = 0;

    for (int i = 0; i < len; i++)
    {
        if (i % 2)
        {
            //add digits of 2 x digit in even place
            even_sum += sum_digits(2 * (number % 10));
        }
        else
        {
            //add digits in odd place
            odd_sum += number % 10;
        }
        number /= 10; //determine once place digit 
    }
    return !((odd_sum + even_sum) % 10);
}
