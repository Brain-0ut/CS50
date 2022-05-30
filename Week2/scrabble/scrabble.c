#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
int check_win(int score1, int score2);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    int x = check_win(score1, score2);
    if (x == 0)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player %i wins!\n", x);
    }
}

int compute_score(string word)
{
    int score = 0;
    int n = 0;
    int upp = 'A';
    int low = 'a';
    while (word[n] != '\0')
    {
        int ch = word[n];
        if (isupper(ch))
        {
            score += POINTS[ch - upp];
        }
        else if (islower(ch))
        {
            score += POINTS[ch - low];
        }
        n++;
    }
    return score;
}

int check_win(int score1, int score2) //Checking which player is Wins.
{
    if (score1 > score2)
    {
        return 1; //Win the first player
    }
    else if (score1 < score2)
    {
        return 2; //Win the second player
    }
    else
    {
        return 0; //Tie!
    }
}