#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int counter = 0;
// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int key = hash(word);
    node* nodePtr = table[key];
    while(nodePtr != NULL)
    {
        if(strcasecmp(nodePtr->word, word) == 0)
        {
            return true;
        }
        nodePtr = nodePtr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int number = 0;
    
    for(int i = 0; word[i] != '\0'; i++)
    {
        number += tolower(word[i]);
    }
    return number % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE* filePtr = fopen(dictionary, "r");
    if(filePtr == NULL)
    {
        return false;
    }
    
    for(int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    
    char tempWord[LENGTH+1];
    
    while(fscanf(filePtr, "%s\n", tempWord) != EOF)
    {
        node* tempNode = malloc(sizeof(node));
        strcpy(tempNode->word, tempWord);
        int key = hash(tempWord);
        
        if (table[key] == NULL)
        {
            tempNode->next = NULL;
            table[key] = tempNode;
        }
        else
        {
            tempNode->next = table[key];
            table[key] = tempNode;
        }
        counter++;
    }
    fclose(filePtr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    return true;
}