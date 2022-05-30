#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

bool check(long card, int len_card)
{
    bool res = false;
    int n = 0;
    int temp, mas[len_card];
    while (card > 0)
    {
        mas[n] = card % 10;
        //printf("%i\n", mas[n]);
        card = card / 10;
        n++;
    }
    int sum = mas[0];
    for (int x = 1; x < len_card; x++)
    {
        if (x % 2)
        {
            temp = mas[x] * 2;
            //printf("mas[%i] = %i, temp = %i;\n", x, mas[x], temp);
            if (temp > 9)
            {
                temp = trunc(temp / 10) + temp % 10;
            }
        }
        else
        {
            temp = mas[x];
        }
        //printf("%i+", temp);
        sum = sum + temp;
    }
    //printf("\n%i\n", sum);
    if (!(sum % 10))
    {
        res = true;
    }
    else
    {
        printf("INVALID\n");
    }
    return res;
}

int main(void)
{
    long card;
    int len_card;
    //do
    //{
    card = get_long("Number: "); //put card number
    len_card = ceil(log10(card + 1));
    //printf("%i\n", len_card);
    //}
    //while ( (len_card < 13) || (len_card > 16));
    if (len_card < 13 || len_card > 16 || len_card == 14)
    {
        printf("INVALID\n");
        exit(0);
    }
    int emitent = trunc(card / pow(10, len_card - 2));
    if (trunc(emitent / 10) == 4)
    {
        if (check(card, len_card))
        {
            printf("VISA\n");
        }
    }
    else if (emitent > 50 && emitent < 56)
    {
        if (check(card, len_card))
        {
            printf("MASTERCARD\n");
        }
    }
    else if (emitent == 34 || emitent == 37)
    {
        if (check(card, len_card))
        {
            printf("AMEX\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    //printf("%i\n", emitent);
}