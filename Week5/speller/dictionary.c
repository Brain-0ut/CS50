// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
unsigned int dict_size = 0;
int hash_idx;

// Hash table
node *table[(N - 1) * 100 + LENGTH];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    hash_idx = hash(word);
    node *tmp = table[hash_idx];
    while (tmp != NULL)
    {
        if (!strcasecmp(tmp->word, word))
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return (toupper(word[0]) - 'A') * 100 + strlen(word);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    char *current_word = malloc(LENGTH + 1);
    if (current_word == NULL)
    {
        return false;
    }
    while (fscanf(dict, "%s", current_word) != EOF)
    {
        dict_size++;
        node *new_word = malloc(sizeof(node));
        if (new_word == NULL)
        {
            return false;
        }
        hash_idx = hash(current_word);
        strcpy(new_word->word, current_word);
        new_word->next = table[hash_idx];
        table[hash_idx] = new_word;
    }
    free(current_word);
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *tmp = NULL; //current;
    for (int i = 1; i < sizeof(table) / 8; i++)
    {
        tmp = table[i];
        if (tmp != NULL)
        {
            while (tmp != NULL)
            {
                tmp = table[i]->next;
                free(table[i]);
                table[i] = tmp;
            }
        }
    }
    return true;
}
