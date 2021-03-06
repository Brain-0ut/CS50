#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9
//#define LENARR(x)  (sizeof(x) / sizeof((x)[0])) //Calculate lenths of array

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
    //int voter_count = 9;
    //string ansv[] = {"a", "b", "c", "a", "b", "c", "a", "b", "c", "b", "c", "a", "b", "c", "a", "c", "a", "b", "c", "a", "b","c", "a", "b","c", "a", "b"};
    //int ansvInd = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            //string name = ansv[ansvInd];
            //ansvInd++;
            string name = get_string("Rank %i: ", j + 1);
            //printf("Rank %i to cand %s\n", j, name);
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
/*/-----------------------------------------//
        for (int j = 0; j < candidate_count; j++)
        {
            printf("Rank %i - %i - %s\n", j, ranks[j], candidates[ranks[j]]);
        }
//-----------------------------------------/*/

        record_preferences(ranks);

        printf("\n");
    }
/*/-----------------------------------------//
//        printf("For cycle '%i'\n", i);
        for (int k = 0; k < candidate_count; k++)
        {
            printf("-------\n|");
            for (int l = 0; l < candidate_count; l++)
            {
                printf("%i|", preferences[k][l]);
            }
            printf("\n");
        }
        printf("-------\n");
//-----------------------------------------/*/

//-----------------------------------------//
    printf("-------------------\n");
    for (int i = 0; i < candidate_count; i++)
    {
        printf("|");
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i|", preferences[i][j]);
        }
        printf("\n");
    }
    printf("-------------------\n");
//-----------------------------------------/*/

    add_pairs();

//-----------------------------------------//
    printf("Pairs without sorting\n");
    for (int i = 0; i < pair_count; i++)
    {
         int x = pairs[i].winner;
         int y = pairs[i].loser;
         printf("(%i-%i) [%i - %i]\n", x, y, preferences[x][y], preferences[y][x]);
    }
    printf("-------------------------\n");

//-----------------------------------------/*/

    sort_pairs();

//-----------------------------------------//
    printf("SORTED PAIRS\n");
    for (int i = 0; i < pair_count; i++)
    {
         int x = pairs[i].winner;
         int y = pairs[i].loser;
         printf("(%i-%i) [%i - %i]\n", x, y, preferences[x][y], preferences[y][x]);
    }
    printf("-------------------------\n");
//-----------------------------------------/*/

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
            //printf("Rank %i to cand %s\n", rank, candidates[i]);
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
        for (int j = i + 1; j < candidate_count; j++)
        {
            int x = ranks[i];
            int y = ranks[j];
            //printf("[%i][%i]", x, y);
            preferences[x][y]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count-1; i++)
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
            //printf("Cand '%s' over Cand '%s'\n", candidates[pairs[pair_count].winner], candidates[pairs[pair_count].loser]);
        }
    }
    //printf("Pairs - %i\n", pair_count);
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair tmpMaxPair = {0, 0}, tmpMinPair = {0, 0};
    int tmpPairCountStop = pair_count - 1;
    int k = 0, m = 0;

/*/-----------------------------------------//
    for (int i = 0; i < pair_count; i++)
    {
        string win = candidates[pairs[i].winner];
        int winScore = preferences[pairs[i].winner][pairs[i].loser];
        string los = candidates[pairs[i].loser];
        int losScore = preferences[pairs[i].loser][pairs[i].winner];
        printf("Pair #%i '%s' - '%s' = %i - %i\n", i + 1, win, los, winScore, losScore);
    }
    printf("-------------------------\n");
//-----------------------------------------/*/

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
            //printf("POS maxWinScore1 - %i\nPOS minWinScore - %i\n", k, m);
        }
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
        else if (k != i)
        {
            tmpMaxPair = pairs[i];
            pairs[i] = pairs[k];
            pairs[k] = tmpMaxPair;

        }
        else if (m != tmpPairCountStop && minWinScore != maxWinScore2)
        {
            tmpMinPair = pairs[tmpPairCountStop];
            pairs[tmpPairCountStop] = pairs[m];
            pairs[m] = tmpMinPair;
            tmpPairCountStop--;
        }
    }

//-----------------------------------------//
    for (int i = 0; i < pair_count; i++)
    {
        int s = 1;
        while (preferences[pairs[i].winner][pairs[i].loser] == preferences[pairs[i + s].winner][pairs[i + s].loser])
        {
            printf("Score i - %i, i = %i\n", preferences[pairs[i].winner][pairs[i].loser], i);
            printf("Score i+s - %i, s = %i\n", preferences[pairs[i + s].winner][pairs[i + s].loser], s);
            s++;
        }
        printf("S - %i\n", s);
        printf("I - %i\n", i);
        for (int j = i; j < i + s; j++)
        {
            pair max = pairs[j];
            int max_pos;
            for (int l = j + 1; l < i + s; l++)
            {
                if (max.winner > pairs[l].winner)
                {
                    max = pairs[l];
                    max_pos = l;
                }
            }
            if (max.winner != pairs[j].winner)
            {
                pair tmp = pairs[j];
                pairs[j] = max;
                pairs[max_pos] = tmp;
            }
        }
        i = i + s - 1;
        printf("I - %i\n", i);

    }

    for (int i = 0; i < pair_count; i++)
    {
        int s = 1;
        while (pairs[i].winner == pairs[i + s].winner)
        {
            //printf("Score i - %i, i = %i\n", preferences[pairs[i].winner][pairs[i].loser], i);
            //printf("Score i+s - %i, s = %i\n", preferences[pairs[i + s].winner][pairs[i + s].loser], s);
            s++;
        }
        //printf("S - %i\n", s);
        //printf("I - %i\n", i);
        for (int j = i; j < i + s; j++)
        {
            pair max = pairs[j];
            int max_pos;
            for (int l = j + 1; l < i + s; l++)
            {
                if (max.loser > pairs[l].loser)
                {
                    max = pairs[l];
                    max_pos = l;
                }
            }
            if (max.loser != pairs[j].loser)
            {
                pair tmp = pairs[j];
                pairs[j] = max;
                pairs[max_pos] = tmp;
            }
        }
        i = i + s - 1;
        //printf("I - %i\n", i);

    }
//-----------------------------------------/*/

//-----------------------------------------//
    for (int z = 0; z < pair_count; z++)
    {
        string win = candidates[pairs[z].winner];
        int winScore = preferences[pairs[z].winner][pairs[z].loser];
        string los = candidates[pairs[z].loser];
        int losScore = preferences[pairs[z].loser][pairs[z].winner];
        printf("Pair #%i '%s' - '%s' = %i - %i\n", z + 1, win, los, winScore, losScore);
    }
    printf("-------------------------\n");
//-----------------------------------------/*/
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
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
                        printf("Pair [%i][%i] is loop\n", x, y);
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
//-----------------------------------------//
    printf("[A][B][C][D][E][F][G][H][I]\n");
    printf("---------------------------\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("[%i]", locked[i][j]);
        }
    printf("\n");
    }
//-----------------------------------------/*/
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool winner = false;
        for (int j = 0; j < candidate_count; j++)
        {
            winner = true;
            if (locked[j][i])
            {
                winner = false;
                break;
            }
        }
        if (winner)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}