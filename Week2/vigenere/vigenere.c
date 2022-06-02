#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//function prototype

bool only_char(string arg);
int shift(char c);
char rotate(char c, int key);

int main(int argc, string argv[])
{
    if (argc != 2 || !only_char(argv[1])) //checks argv of command line
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    int keyLen = strlen(argv[1]); //lenght of array of keys
    int keys[keyLen]; //array of keys
    for (int i = 0; i < keyLen; i++) //make the array of keys
    {
        int k = (int)argv[1][i];
        keys[i] = shift((char)k);
        printf("%i\n", keys[i]);
    }
    //return 1;
    string str = get_string("plaintext:  "); //user input
    printf("ciphertext: ");
    int n = 0;
    int keyPos = 0;
    while (str[n] != '\0')
    {
        if (keyPos == keyLen)
        {
            keyPos = 0;
        }
        printf("%c", rotate(str[n], keys[keyPos]));
        n++;
        if (isalpha(str[n]))
        {
            keyPos++;
        }
    }
    printf("\n");
    return 0;
}

char rotate(char c, int key) // rotate the char to another char using key
{
    int upp = 'A';
    int low = 'a';
    int ch = c;
    if (isalpha(c)) // if letter - convert
    {
        if (isupper(c))
        {
            ch = ((c + key - upp) % 26) + upp;
        }
        else if (islower(c))
        {
            ch = ((c + key - low) % 26) + low;
        }
    }
    return ch;
}

bool only_char(string arg) // checks the argv is contains only 26 char
{
    for (int i = 0, n = strlen(arg); i < n; i++)
    {
        if (!isalpha(arg[i]))
        {
            return false;
        }
    }
    return true;
}

int shift(char c)
{
    int upp = 'A';
    int low = 'a';
    int key;
    if (isupper(c))
    {
        key = (int)c - upp;
    }
    else
    {
        key = (int)c - low;
    }
    return key;
}
