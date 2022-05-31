#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//function prototype

bool only_char(string arg);
bool dublicates_serch(string arg);
char rotate(char c, string key);

int main(int argc, string argv[])
{
    if (argc != 2) //checks argv of command line
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if ((strlen(argv[1]) != 26 || !only_char(argv[1])) || dublicates_serch(argv[1])) //checks argv of command line
    {
        printf("Key must contain 26 characters and without dublacates.\n");
        return 1;
    }
    string key = argv[1]; // key is array from argv[1]
    string str = get_string("plaintext:  "); //user input
    printf("ciphertext: ");
    int n = 0;
    while (str[n] != '\0')
    {
        printf("%c", rotate(str[n], key));
        n++;
    }
    printf("\n");
    return 0;
}

char rotate(char c, string key) // rotate the char to another char using key
{
    int upp = 'A';
    int low = 'a';
    int char_num;
    int ch = c;
    if ((c >= 'a' && c <= 'z') || ((c >= 'A' && c <= 'Z'))) // if letter - convert
    {
        if (isupper(c))
        {
            char_num = c - upp;
            ch = key[char_num];
            ch = toupper(ch);
        }
        else if (islower(c))
        {
            char_num = c - low;
            ch = key[char_num];
            ch = tolower(ch);
        }
    }
    return ch;
}

bool only_char(string arg) // checks the argv is contains only 26 char
{
    int count_l = 0;
    int n = strlen(arg);
    for (int i = 0; i < n; i++)
    {
        if ((arg[i] >= 'a' && arg[i] <= 'z') || (arg[i] >= 'A' && arg[i] <= 'Z'))
        {
            count_l++;
        }
    }
    if (count_l != n)
    {
        return false;
    }
    return true;
}

bool dublicates_serch(string arg)
{
    int n = 0, l = strlen(arg);
    for (int i = n; i < l - 1; i++)
    {
        for (int j = i + 1; j < l; j++)
        {
            //printf("%i - %c\n%i - %c\n", i, arg[i], j, arg[j]);
            if (tolower(arg[i]) == tolower(arg[j]))
            {
                //printf("#\n");
                return true;
            }
        }
        n++;
    }
    return false;
}