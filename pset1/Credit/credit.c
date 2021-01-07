/* Javius Santiago
 * 02/04/2020
 * credit.c - This program uses Luhn's algorithm to determine the syntactic -
 * validity of a given credit card number and returns the name of the company -
 * who issued it if valid.
 */

#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Function prototypes
long getLen(long x);
void checkSum(long cn);

int main(void)
{
    // Uses cs50 library to get input, should be a credit card number
    long cardNo = get_long("Number: ");
    // Checks syntactic validity of card number
    checkSum(cardNo);
}

// Checks card validity according to Luhn's algorithm
void checkSum(long cn)
{
    // Holds the card number, being shortened with each iteration of the while loop
    long tempNum = cn;
    // This will be set to tempNum's far right digit with each iteration of the loop
    long curDig;
    // Used to determine which digits are a part of every other number starting with the 2nd to last digit
    bool otherDig = false;
    // sum is the sum of the digits of the products of every other number starting with the second to last digit * 2
    long sum = 0;
    // This will hold the sum of the numbers that were not multiplied by 2
    long secondSum = 0;
    // Used to identify which company issued the card if it is valid
    long companyID;

    // Determines whether to multiply curDig by 2 and add its product's digits to sum or just add curDig to secondSum
    while (getLen(tempNum) > 0)
    {
        // Once shortened to two digits we can determine the company that issued the card
        if (getLen(tempNum) == 2)
        {
            companyID = tempNum;
        }

        // Sets curDig to the far right digit of tempNum
        curDig = tempNum % 10;

        // If digit is part of every other number (right to left) starting with the 2nd to last
        if (otherDig)
        {
            // If curDig * 2 = to a 2 digit number
            if (curDig * 2 > 9)
            {
                // Then both digits in the product are added to the sum
                sum += (curDig * 2) - 9;
            }
            // Otherwise if the product is 1 digit long
            else
            {
                // Then the product is added without having to account for other digits
                sum += curDig * 2;
            }
            // Ensures that when the loop reiterates curDig is handled correctly
            otherDig = false;
        }
        // Else if curDig does not belong in the first sum
        else if (!otherDig)
        {
            // Then it belongs in secondSum (the sum not being multiplied)
            secondSum += curDig;
            // Ensures that the next digit is multiplied by 2 and its product's digits are added to first sum
            otherDig = true;
        }

        // Prevents an infinite loop
        if (tempNum < 10)
        {
            break;
        }

        // Removes far right digit from tempNum before reiterating
        tempNum /= 10;
    }

    // Determines syntactic validity
    if ((sum + secondSum) % 10 == 0)
    {
        // Determines issuer
        if ((companyID == 34 || companyID == 37) && getLen(cn) == 15)
        {
            printf("AMEX\n");
        }
        else if ((companyID > 50 && companyID < 56) && getLen(cn) == 16)
        {
            printf("MASTERCARD\n");
        }
        else if ((getLen(cn) == 16 || getLen(cn) == 13) && companyID / 10 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Determines the length of a long or int
long getLen(long x)
{
    return 1 + (long)log10(x);
}
