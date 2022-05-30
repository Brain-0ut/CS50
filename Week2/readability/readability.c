#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    //return 1;
    int words = count_words(text);
    //return 1;
    int sentences = count_sentences(text);
    //return 1;
    //printf("Letters: %i\n", letters);
    //printf("Words: %i\n", words);
    //printf("Sentences: %i\n", sentences);
    float l = (float)letters / (float)words * 100;
    float s = (float)sentences / (float)words * 100;
    float grade = l * 0.0588 - s * 0.296 - 15.8;
    //printf("L %f\nS %f\ngrade %f\n", l, s, grade);
    if (grade < 1.0)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16.0)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)round(grade));
    }

}

int count_letters(string text) //count letters
{
    int count_l = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || ((text[i] >= 'A' && text[i] <= 'Z')))
        {
            count_l++;
        }
    }
    //printf("Letters: %i\n", count_l);
    return count_l;
}

int count_words(string text) // Count words
{
    int count_w = 0;
    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        if (text[i] == ' ' || text[i] == '\0')
        {
            count_w++;
        }
    }
    //printf("Words: %i\n", count_w);
    return count_w;
}

int count_sentences(string text) //Count sentences
{
    int count_s = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count_s++;
        }
    }
    //printf("Sentences: %i\n", count_s);
    return count_s;
}