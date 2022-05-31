#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//function prototype
int str_to_int(string arg);
bool only_digits(string arg);
char rotate(char ch, int key);

int main(int argc, string argv[])
{
    if (argc != 2 || !only_digits(argv[1])) //checks argv of command line
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = str_to_int(argv[1]) % 26; // convert argv from str to int
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

char rotate(char c, int key) // rotate the char to another char using key
{
    int upp = 'A';
    int low = 'a';
    int ch = c;
    if ((c >= 'a' && c <= 'z') || ((c >= 'A' && c <= 'Z'))) // if letter - convert
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

bool only_digits(string arg) // checks the argv is contains only digits
{
    for (int i = 0, n = strlen(arg); i < n; i++)
    {
        if (arg[i] < '0' || arg[i] > '9')
        {
            return false;
        }
    }
    return true;
}

int str_to_int(string arg) //convert input key from string to int
{
    int num = 0;
    for (int i = 0, n = strlen(arg); i < n; i++)
    {
        num += ((int)arg[i] - (int)'0') * pow(10, n - i - 1);
        char c = arg[1];
        int x = (int)c - (int)'0';
    }
    return num;
}