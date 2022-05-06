#include <cs50.h>
#include <stdio.h>
#include<string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

bool been_here[MAX];
int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool circle_check(int i, int search);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

//if (!vote(j, name, ranks)), j is the rank vu the voter, name is the vote, ranks[i] is the voters ith preference meaning ranks[0] gives the candidates indeces for the first vote
// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    bool found = false;

    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(candidates[j], name) == 0)
        {
            ranks[rank] = j;
            found = true;
        }
        else
        {
            continue;
        }
    }
    if (found == false)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // preferences[i][j] is number of voters who prefer i over j
    //Might need to first set all preferences[i][j] equal to zero, outside of the function since its calledc for each voter


    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i >= j)
            {
                continue;
            }
            else
            {
                preferences[ranks[i]][ranks[j]] = preferences[ranks[i]][ranks[j]] + 1;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)                                            //This function and up are right. no changes required
{
    pair_count = 0;
    // pairs[].winner   pairs[].loser   ||  integers. input the index for the winner and the index for the loser
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i >= j)
            {
                continue;
            }
            else if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count = pair_count + 1;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count = pair_count + 1;
            }
            else
            {
                continue;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair swap[MAX * (MAX - 1) / 2];
    for (int j = 0; j < pair_count; j++)
    {
        int largest = 0;
        int index = 0;

        for (int i = 0 + j; i < pair_count; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] >= largest)
            {
                largest = preferences[pairs[i].winner][pairs[i].loser];
                index = i; //index identifies where our maximum value is located in pairs
            }
            else
            {
                continue;
            }
        }
        //printf("%i\n", index);
        if (index == j)
        {
            //printf("index = j meaning we have our largest in position, so continuing: %d, %d should be 0, 1\n", pairs[j].winner, pairs[j].loser);
            continue;
        }
        else
        {
            swap[j].winner = pairs[j].winner;
            swap[j].loser = pairs[j].loser;

            pairs[j].winner = pairs[index].winner;
            pairs[j].loser = pairs[index].loser;

            pairs[index].winner = swap[j].winner;
            pairs[index].loser = swap[j].loser;

            //printf("a and b have been swapped. %d, %d\n", pairs[j].winner, pairs[j].loser);
        }
    }
    for (int j = 0; j < pair_count; j++)
    {
        //printf("winner: %d, loser: %d\n", pairs[j].winner, pairs[j].loser);
    }
    return;
}

bool circle_check(int i, int search)
{
    if (been_here[i])
    {
        return false;
    }
    been_here[i] = true;

    if (locked[i][search])
    {
        return true;
    }
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[i][j])
        {
            if (circle_check(j, search))
            {
                return true;
            }
        }
    }

    return false;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int lead = pairs[0].winner;
    locked[pairs[0].winner][pairs[0].loser] = true;
    
    for (int i = 1; i < pair_count; i++)
    {
        if (pairs[i].loser != pairs[0].winner)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else
        {
            if (!circle_check(pairs[0].winner, pairs[i].winner))
            {
                lead = pairs[i].winner;
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
        }
        
        for (int j = 0; j < candidate_count; j++)
        {
            been_here[j] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int i;
    int j;
    
    for (j = 0; j < candidate_count; j++)
    {
        for (i = 0; i < candidate_count ; i++)
        {
            if (locked[i][j])
            {
                break;
            }
        }

        if (i == candidate_count)
        {
            printf("%s\n", candidates[j]);
        }
    }
    return;
}

