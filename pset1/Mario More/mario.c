/* Javius Santiago
 * Harvard CS50
 * 02/05/2020
 * mario.c - This program prints a pyramid of "#"s similar to the blocks seen in Super Mario Brothers.
 * The size is determined by the users input.
 */

#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    // Boolean value (boolean type imported) representing the program being in its "on" state
    bool on = true;

    while (on)
    {
        // Requests the height from the user's input, will continue to ask if user doesn't enter value from 1-8
        int ht = get_int("height(1-8): ");
        // If input is between 1-8
        if (ht > 0 && ht < 9)
        {
            // This for loop creates the pyramid row by row
            for (int rowNum = 0; rowNum < ht; rowNum++)
            {
                // rowNum is subtracted to reduce the amount of spaces by 1 every iteration
                for (int spaceNum = ht - 1 - rowNum; spaceNum > 0; spaceNum--)
                {
                    printf(" ");
                }
                for (int hashNum = 0; hashNum < rowNum + 1; hashNum++)
                {
                    printf("#");
                }
                printf("  ");
                for (int secondHashNum = 0; secondHashNum < rowNum + 1; secondHashNum++)
                {
                    printf("#");
                }
                printf("\n");
            }
            on = false;
        }
    }
}
