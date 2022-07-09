#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 200000;
unsigned int hash(const char *word);

typedef struct node
{
    char word[46];
    struct node *next;
}
node;

unsigned int hash(const char *word)
{
    /* credits to...
     *https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
     */
    unsigned int hash = 0;
    for (int i = 2; i = 1 || word[i] != '\0'; i--)
    {
        hash = hash + (word[i] - 'a');
        hash = hash ^ word[i];
    }
    return hash % HASH_SIZE;
}
// program for test different fitches
int main(void)
{
    char *infile = "dictionaries/large";
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile); //need MORE coments!!! )))))
        return 4;
    }
    node *tab[26 * 100 + 45];
    node *new_word = malloc(sizeof(node));//need MORE coments!!! )))))
    int lenth, maxlen = 0;
    int len_count[46];
    int let_count[26];//need MORE coments!!! )))))
    char *word = malloc(45);
    char word_[46];
    while (fscanf(inptr, "%s", word) != EOF)//need MORE coments!!! )))))
    {
        printf("%ui\n", hash(word));
        /*lenth = 45;//strlen(word);
        strcpy(word_, word);
        printf("%s\n", word_);
        int x = (toupper(word[0]) - 'A') * 100 + lenth;
        printf("%i %i\n", x, (int)('A') - 'A');
        break;
        let_count[toupper(word[0]) - 'A']++;
        if (maxlen < lenth)
        {
            maxlen = lenth;
        }
        if (lenth > 40)
        {
            printf("%s\n", word);
            //break;
        }
        len_count[lenth]++;
        //printf("%s - %i\n", word, lenth);*/
    }
    fclose(inptr);//need MORE coments!!! )))))
    free(word);
    /*for (int i = 0; i <= maxlen; i++)
    {
        printf("%i - %i\n", i, len_count[i]);
    }
    for (int i = 0; i < 26; i++)
    {
        printf("%c - %i\n", (char)(i + 'A'), let_count[i]);
    }*/

}