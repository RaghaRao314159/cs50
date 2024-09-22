//import libraries
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// initialise functions
int count_letters(string par);
int count_words(string par);
int count_sentences(string par);

int main(void)
{
    //ask user for a paragarph (par)
    string par = get_string("Text: ");

    int letters = count_letters(par);
    int words = count_words(par);
    int sentences = count_sentences(par);

    //Coleman-Liau formula
    float L = 100.0 * letters / words;
    float S = 100.0 * sentences / words;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    //Decide grade
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index <= 16)
    {
        printf("Grade %i\n", (int) round(index));
    }
    else
    {
        printf("Grade 16+\n");
    }


}

int count_letters(string par)
{
    int letter_count = 0;
    int i = 0;

    //loop through par and count number of alphabets
    while (par[i] != 0)
    {
        if (isalpha(par[i]))
        {
            letter_count++;
        }
        i++;
    }
    return letter_count;
}

int count_words(string par)
{
    int word_count = 0;
    int i = 0;

    //loop through par and count number of spaces
    while (par[i] != 0)
    {
        if (isspace(par[i]))
        {
            word_count++;
        }
        i++;
    }

    //add one to word-count as number of words = number of spaces + 1
    word_count++;
    return word_count;
}

int count_sentences(string par)
{
    int sentence_count = 0;
    int i = 0;

    //loop through par and count number of sentence enders
    while (par[i] != 0)
    {
        if (par[i] == '.' || par[i] == '!' || par[i] == '?')
        {
            sentence_count++;
        }
        i++;
    }
    return sentence_count;
}
