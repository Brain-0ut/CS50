#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 5
#define MAX_CANDIDATES 3

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES] = {{2, 3, 1}, {3, 2, 1}, {3, 1, 2}, {1, 3, 2}, {2, 3, 1}};

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = MAX_VOTERS;
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    /*for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }*/

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }
    //return 0;

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        for (int j = 0; j < candidate_count; j++)
        {
            printf("%s - %i ", candidates[j].name, candidates[j].votes);
            printf("\n");
        }
        printf("\n");
        //return 0;

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        //printf("%i\n", min);
        //break;
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i].name, name))
        {
            if (preferences[voter][i])
            {
                return false;
            }
            preferences[voter][i] = rank+1;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        if (!candidates[preferences[i][0]-1].eliminated)
        {
            candidates[preferences[i][0]-1].votes++;
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes > voter_count/2)
        {
            printf("%s\n", candidates[j].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int x = candidates[0].votes;
    for (int j = 1; j < candidate_count; j++)
    {
        if (x > candidates[j].votes)
        {
            x = candidates[j].votes;
        }
    }
    return x;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int x = 0, y = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated)
        {
            x++;
        }
        else
        {
            if (candidates[i].votes == min)
            {
                y++;
            }
        }
    }
    if (x + y == candidate_count && !(y & 1))
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < voter_count; i++)
    {
        if (candidates[preferences[i][0]-1].votes == min)
        {
            candidates[preferences[i][0]-1].eliminated = true;
            for (int j = 0; j < candidate_count - 1; j++)
            {
                preferences[i][j] = preferences[i][j + 1];
            }
        }
    }
    return;
}