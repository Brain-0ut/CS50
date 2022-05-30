#include <cs50.h>
#include <stdio.h>
#include <math.h>

int get_cents(void);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();
    int i = ceil(log10(cents + 1));
    printf("%i\n", i);
    int y = round(pow(10,i-i));
    int x = cents % y;
    printf("%i\n", x);
    int coins = round(cents/pow(10,i));
    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int cents;
    //int dollars;
    do
    {
        //dollars = get_int("Change owed: "); //put cents
        cents = get_int("Change owed: ");
    }
    while (cents < 1);
    return cents;
}