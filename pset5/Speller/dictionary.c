// Implements a dictionary's functionality

/* 1/2021 Javius Santiago */

#include <stdbool.h>
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];
// Counts number of words
unsigned long wordCount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Creates a lowercase copy of word, lower
    char lower[strlen(word) + 1];
    // "+ 1" is added wordsize to include the terminating null character '\0'
    int wordSize = strlen(word) + 1;
    for (int i = 0; i < wordSize; i++)
    {
        lower[i] = tolower(word[i]);
    }

    // The lowercase version is hashed since our dictionary is all lowercase
    unsigned long hashIndex = hash(lower);
    node *cursor = table[hashIndex];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary as a readable file and check for errors
    FILE *infile = fopen(dictionary, "r");
    if (infile == NULL)
    {
        return false;
    }

    unsigned long hashIndex;
    node *newNode;

    // Ensure hash table is all NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Our buffer for each word
    char word[LENGTH + 1];
    while (fscanf(infile, "%s", word) != EOF)
    {
        newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            return false;
        }

        strcpy(newNode->word, word);
        newNode->next = NULL;

        hashIndex = hash(word);

        // If there is already a linked list at that hash index, or "bucket"
        if (table[hashIndex] != NULL)
        {
            // New node now points to the head of that list
            newNode->next = table[hashIndex];
        }

        // Our new node becomes the new head of the linked list
        table[hashIndex] = newNode;
        wordCount++;
    }

    fclose(infile);
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned long size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Loop through each index in the hash table
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            // In order to avoid losing the rest of the list, tmp is used
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}

/* djb2 by Dan Bernstein
Hash function found online @
site: http://www.cse.yorku.ca/~oz/hash.html
This function has been modified (added "% n") in
order to reduce size of hash table*/
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % N;
}
