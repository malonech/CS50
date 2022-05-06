// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hashes word to a number
unsigned int hash(const char *word)         // recived from http://www.cse.yorku.ca/~oz/hash.html
{
    char firstletter = tolower(word[0]);
    int hash = firstletter - 'a';
    return hash;
    
}

// Hash table
node *table[N] = {NULL};

//word count
long wordcount = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dictionaryfile = fopen(dictionary, "r");      //open the dictionary file to read the contents

    if (dictionaryfile == NULL)
    {
        printf("Could not open %s.\n", dictionary);     //Check if the dictionary file was opened properly, and return if not
        unload();
        return false;
    }
    
    char word[LENGTH + 1];

    while (fscanf(dictionaryfile, "%s", word) != EOF) //looping until we reach the end of the dictionary file, marked by EOF, copying each word
    {
        int hashindex = hash(word);
        
        node *n = malloc(sizeof(node));                  //allocate memory for the current node
        if (n == NULL)
            return false;                               //return false if insufficient memory
        
        strcpy(n->word, word);                        //copying the word variable into its respective node
                                                     //calling the hash function to store the node in the hash table
        n->next = table[hashindex];
        table[hashindex] = n;

        wordcount++;
    }
    fclose(dictionaryfile);
    
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int hashcheck = hash(word);
    node *cursor = table[hashcheck];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;

    }
    //printf("%s was not located in bucket %i", word, hashcheck);
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for (int i = 0; i < N; i++)
    {
        node *temp = table[i];
        node *cursor = table[i];

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }

    return true;
}
