#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // collect name of user
    string name = get_string("what is your name?: ");

    //display name of user
    printf("hello, %s\n", name);
}
