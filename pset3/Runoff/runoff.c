/* Javius Santiago
   Runoff.c
   4/5/2020
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    // Get number of voters
    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Check if name is the name of a valid candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // If name is a valid candidate
        if (strcmp(name, candidates[i].name) == 0)
        {
            // Updates global preferences array
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Loops through each voters preferences
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // If the candidate of their preference closest to the first isn't eliminated
            if (candidates[preferences[i][j]].eliminated == false)
            {
                // The vote is cast for their closest preference
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Loops through every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // If the candidate has a majority of the votes
        if (candidates[i].votes > voter_count / 2)
        {
            // That candidate is the winner
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int currentMinimum;
    bool setMin = false;
    int x = 0;

    // Sets the currentMinimum to the first non-eliminated candidates votes
    while (!setMin)
    {
        if (candidates[x].eliminated == false)
        {
            currentMinimum = candidates[x].votes;
            setMin = true;
        }
        x++;
    }

    // Loops through each candidate, finding the least  amount of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes < currentMinimum)
            {
                currentMinimum = candidates[i].votes;
            }
        }
    }

    return currentMinimum;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Loops through all the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If any non-eliminated candidate's votes aren't equal to the minimum
        if (candidates[i].votes != min && candidates[i].eliminated == false)
        {
            // Then it can't be a tie
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Loops through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // If the candidate's vote count is equal to the min
        if (candidates[i].votes == min)
        {
            // Then they are eliminated
            candidates[i].eliminated = true;
        }
    }
    return;
}
