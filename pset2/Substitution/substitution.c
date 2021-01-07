/* Javius Santiago
 * 03/31/2020
 * Substitution.c - This program uses a given key to cipher text using substitution
 */

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

const int keyLength = 26;
const string alphabet = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

bool lettersUsed[26];

int getIndex(string array, char element);
void cipher(string input, string key);

int main(int argc, char const *argv[])
{
    string key = " ";

    // If no arguments or too many are given -> error
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Arguement 1 should be a 26 digit key
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Key is set to the given arguement
    key = (string)argv[1];

    // Checks key to make sure no letter is reused or non letters used
    for (int i = 0; i < strlen(key); i++)
    {
        // Position of the current char in the key relative to the alphabet
        int index = getIndex(alphabet, key[i]);

        // Checks for symbols
        if (isalpha(key[i]) == false)
        {
            printf("ERROR: key must not contain symbols\n");
            return 1;
        }

        // Checks if letter is used more than once
        if (lettersUsed[index] == true)
        {
            printf("\nERROR: '%c' is used more than once in the key", key[i]);
            return 1;
        }
        else
        {
            lettersUsed[index] = true;
        }
    }

    // Get plain text
    string plainText = get_string("plaintext: ");
    cipher(plainText, key);
}

// Function to cypher a given input using a given key
void cipher(string input, string key)
{
    char output[strlen(input)];

    for (int i = 0; i < strlen(input); i++)
    {
        char currentChar = input[i];
        int alphaIndex = getIndex(alphabet, input[i]);

        if (isupper(currentChar))
        {
            output[i] = toupper(key[alphaIndex]);
        }
        else if (islower(currentChar))
        {
            output[i] = tolower(key[alphaIndex]);
        }
        else
        {
            output[i] = currentChar;
        }
    }

    printf("ciphertext: %s\n", output);
}

int getIndex(string array, char element)
{
    for (int i = 0; i < strlen(array); i++)
    {
        if (array[i] == toupper(element))
        {
            return i;
        }
    }
    return -1;
}
