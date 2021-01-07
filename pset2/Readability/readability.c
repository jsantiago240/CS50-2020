/* Javius Santiago
 * 02/28/2020
 * Readability.c - This program calculates the approximate grade level required
 * to comprehend given text according to the Coleman-Liau index.
 */
 
#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int count_letters(string rawInput);
int count_words(string rawInput);
int count_sentences(string input);
void calculate_readability(string input);

int main(void)
{
    // Gets user input
    string rawInput = get_string("Text: ");
    calculate_readability(rawInput);
}

// Counts every letter
int count_letters(string input)
{
    int numLetters = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (isalpha(input[i]))
        {
            numLetters++;
        }
    }
    return numLetters;
}

// Counts every word
int count_words(string input)
{
    int numWords = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (isspace(input[i]) || input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            numWords++;
            if (input[i] == '.' && isspace(input[i + 1]))
            {
                numWords--;
            }
        }
    }
    return numWords;
}

// Counts every sentence
int count_sentences(string input)
{
    int numSentences = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            numSentences++;
        }
        if (input[i] == '.' && input[i + 1] == '.')
        {
            numSentences--;
        }
    }
    return numSentences;
}

// Calculates readability using Coleman-Liau index
void calculate_readability(string input)
{
    int numLetters = count_letters(input), numWords = count_words(input), numSentences = count_sentences(input);
    float avgLetters = (numLetters * 100.0) / numWords;
    float avgSentences = (numSentences * 100.0) / numWords;

    int gradeLevel = round(0.0588 * avgLetters - 0.296 * avgSentences - 15.8);

    if (gradeLevel >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (gradeLevel < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", gradeLevel);
    }
}
