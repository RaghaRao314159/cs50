// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int mod = 100009;
const unsigned int p = 7;
const unsigned int N = mod;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_idx = hash(word);
    node *trav = table[hash_idx];
    while (trav != NULL)
    {
        if (!strcasecmp(trav->word, word))
        {
            return true;
        }
        trav = trav->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    // Changes word to a polynomial f(p) of atmost degree 4, where the words prepresent the coefficients

    unsigned int hash_value = 0;
    int count = 0;
    while (*word != '\0' && count != 4)
    {
        hash_value = hash_value * p + (toupper(word[0]) - 'A');
        count += 1;
        if (hash_value >= mod)
        {
            hash_value = hash_value % mod;
        }
        word += 1;
    }
    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        return false;
    }
    char c;
    int index = 0;
    node *new = NULL;
    while (fread(&c, sizeof(char), 1, dict))
    {
        // Assumes dictionary contains only letters and new line character
        if (c != '\n')
        {
            if (index == 0)
            {
                new = malloc(sizeof(node));

                if (new == NULL)
                {
                    return false;
                }
            }
            // Append character to word
            new->word[index] = c;
            index++;
        }

        // We must have found a whole word
        else
        {
            // Terminate current word
            new->word[index] = '\0';

            int hash_idx = hash(new->word);

            new->next = table[hash_idx];
            table[hash_idx] = new;

            // Prepare for next word
            index = 0;
        }
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    int count = 0;
    node *trav;
    for (int i = 0; i < N; i++)
    {
        trav = table[i];
        while (trav != NULL)
        {
            count += 1;
            trav = trav->next;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
void destroy(node *curr_node)
{
    if (curr_node == NULL)
    {
        return;
    }
    destroy(curr_node->next);
    free(curr_node);
}

// recursive function to unload dictionary
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        destroy(table[i]);
    }

    return true;
}
