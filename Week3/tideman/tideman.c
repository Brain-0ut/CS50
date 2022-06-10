#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);
        printf("\n");
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int x = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            int y = ranks[j];
            preferences[x][y]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int x = preferences[i][j];
            int y = preferences[j][i];
            if (x > y)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (x < y)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair tmpMaxPair = {0, 0}, tmpMinPair = {0, 0};
    int tmpPairCountStop = pair_count - 1;
    int k = 0, m;
    for (int i = 0; i < tmpPairCountStop; i++)
    {
        int maxWinScore1 = preferences[pairs[i].winner][pairs[i].loser];
        int minWinScore = maxWinScore1;
        int maxWinScore2;
        for (int j = i + 1; j <= tmpPairCountStop; j++)
        {
            m = j;
            maxWinScore2 = preferences[pairs[j].winner][pairs[j].loser];
            if (maxWinScore2 > maxWinScore1)
            {
                maxWinScore1 = maxWinScore2;
                k = j;
            }
            if (maxWinScore2 < minWinScore)
            {
                minWinScore = maxWinScore2;
                m = j;
            }
        }
        //if the max and the min scores is in the middle of list, move max score to the start and min score to the end of the list
        if (k != i && m != tmpPairCountStop)
        {
            tmpMaxPair = pairs[i];
            pairs[i] = pairs[k];
            tmpMinPair = pairs[tmpPairCountStop];
            pairs[tmpPairCountStop] = pairs[m];
            pairs[m] = tmpMaxPair;
            pairs[k] = tmpMinPair;
            tmpPairCountStop--;
        }
        //if the max score is in the middle, then move it to the start of the list
        else if (k != i)
        {
            tmpMaxPair = pairs[i];
            pairs[i] = pairs[k];
            pairs[k] = tmpMaxPair;
        }
        //if the minimum score is in the middle, then move it to the end of the list
        else if (m != tmpPairCountStop && minWinScore != maxWinScore2)
        {
            tmpMinPair = pairs[tmpPairCountStop];
            pairs[tmpPairCountStop] = pairs[m];
            pairs[m] = tmpMinPair;
            tmpPairCountStop--;
        }
    }
    return;
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int x = pairs[i].winner;
        int y = pairs[i].loser;
        locked[x][y] = true;
        int z_w = y;
        for (int j = 0; j < i; j++)
        {
            if (pairs[j].winner == y)
            {
                z_w = pairs[j].loser;
                for (int n = 0; n < i; n++)
                {
                    if (pairs[n].winner == z_w && pairs[n].loser == x)
                    {
                        locked[x][y] = false;
                        break;
                    }
                }
            }
            if (!locked[x][y])
            {
                break;
            }
        }
    }
    return;
}

/*/ Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int x = pairs[i].winner;
        int y = pairs[i].loser;
        locked[x][y] = true;
        for (int j = 0; j < i; j++)
        {
            if (pairs[j].loser == x) //if current winner was be the looser before
            {
                for (int k = 0; k < i; k++)
                {
                    if (pairs[k].winner == y) //if the loop present, then skip
                    {
                        locked[x][y] = false;
                        break;
                    }
                }
            }
        }
    }
    return;
}/*/

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool winner = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])//if arrow is present, current candidate is not the winner
            {
                winner = false;
                break;
            }
            winner = true;
        }
        if (winner)
        {
            printf("%s\n", candidates[i]);//print the winner
            return;
        }
    }
    return;
}