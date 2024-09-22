#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
// void merge_sort(int left, int right);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");
    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}


// Print the winner (or winners) of the election
void print_winner(void)
{
    //intitalise variable to keep track of largest value
    int max[] = {-1, 0};

    //intitalise list to keep track of names that have already bene printed
    int used[candidate_count];
    int highest = -1;
    for (int k = 0; k < candidate_count; k++)
    {
        used[k] = 0;
    }

    //keep looping until all largest ties are expended
    for (int i = candidate_count - 1; i >= 0; i--)
    {
        for (int j = candidate_count - 1; j >= 0; j--)
        {
            if ((used[j] == 0) && (candidates[j].votes >= max[0]))
            {
                max[0] = candidates[j].votes;
                max[1] = j;
            }
        }
        //printf("%i %i",highest, max[0]);
        if (max[0] < highest)
        {
            break;
        }

        used[max[1]] = 1;
        printf("%s\n", candidates[max[1]].name);
        highest = max[0];

        max[0] = -1;
        max[1] = 0;
    }
    return;
}