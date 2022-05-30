#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height, count;
    string s;
    do
    {
        height = get_int("What height of pyramid you whant? "); //put height of pyramid
    }
    while (height < 1 || height > 8);
    for (int i = 1; i <= height; i++)
    {
        count = 0;
        for (int x = 1; x <= height * 2 + 2; x++) //reverse loop
        {
            if (x <= height - i || (x > height && x <= height + 2) || x > height + 2 + i)
            {
                printf(" "); // print " "
            }
            else
            {
                printf("#"); // print #
                count += 1;
            }
            if (count == i * 2)
            {
                break;
            }
        }
        printf("\n");
    }
}