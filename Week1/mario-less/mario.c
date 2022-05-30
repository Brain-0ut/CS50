#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    string s;
    do
    {
        height = get_int("What height of pyramid you whant? "); //put height of pyramid
    }
    while (height < 1 || height > 8);
    for (int i = 1; i <= height; i++)
    {
        for (int x = height; x > 0; x--) //reverse loop
        {
            if (x > i)
            {
                printf(" "); // print " "
            }
            else
            {
                printf("#"); // print #
            }
        }
        printf("\n");
    }
}