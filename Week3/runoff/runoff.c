#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

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

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    /*for(int i = 0; i < MAX_VOTERS; i++)
    {
        for(int j = 0; j < MAX_CANDIDATES; j++)
        {
            preferences[i][j] = -1;
        }
    }*/

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
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
    }

    /*for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }
    return 0;*/

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        /*for (int j = 0; j < candidate_count; j++)
        {
            printf("%s - %i ", candidates[j].name, candidates[j].votes);
            printf("\n");
        }
        printf("\n");
        //return 0;*/

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        //printf("%i\n", min);
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
/*bool vote(int voter, int rank, string name)
{
    int x = 0;
    int s = strcmp(candidates[x].name, name);
    while (s != 0 && x < candidate_count-1)
    {
        x++;
        s = strcmp(candidates[x].name, name);
    }
    x++;
    //printf("%i\n", x);
    if (s)
    {
        return false;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (preferences[voter][i] == x)
        {
            return false;
        }
    }
    preferences[voter][rank] = x;
    return true;
}*/
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int x;
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            x = preferences[i][j];
            if (!candidates[x].eliminated)
            {
                candidates[x].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int x;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        if (!candidates[i].eliminated)
        {
            x = candidates[i].votes;
            if (x > candidates[i + 1].votes && !candidates[i+1].eliminated)
            {
                x = candidates[i + 1].votes;
            }
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
    if (x + y == candidate_count && y > 1)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
            for (int k = 0; k < voter_count; k++)
            {
                if (preferences[k][0] == i + 1)
                {
                    for (int j = 0; j < candidate_count - 1; j++)
                    {
                        preferences[k][j] = preferences[k][j + 1];
                    }
                }
            }
        }
    }
    return;
}
