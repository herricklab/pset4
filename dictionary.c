// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// counter for number of words
int counter = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; // to store the buffer value of /0
    struct node *next;
}
node;

// Represents a hash table with N = 26 buckets
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a'; // lowercase the letter and then subtract from letter a, if word[0] is 'a' it will return 0
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL; // all buckets are NULL at the moment
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Using a hashvalue then
    void insert(int hashvalue, char* word);

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        int hashvalue = hash(word); // obtain the hashvalue of the word
        insert(hashvalue, word); // insert the word into linked list according to the hashvalue
        counter++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}


// Insert function that creates a linked list
void insert(int hashvalue, char* word)
{
    node* new_node = malloc(sizeof(node)); // create a new node
    if(!new_node) // if new_node == NULL no memory is available etc
    {
        return;
    }

    //add word to a node, not pointing to anywhere yet
    strcpy(new_node->word, word);
    new_node->next = NULL;

    if (!hashtable[hashvalue]) //if inside a N array is empty
    {
        hashtable[hashvalue] = new_node;
    }
    else // if theres already a pointer
    {
        node* temp = hashtable[hashvalue];
        new_node->next = temp;
        hashtable[hashvalue]->next = new_node;
    }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node* ptr = hashtable[hash(word)];
    while (ptr != NULL)
    {
        int result = strcasecmp(ptr->word, word);
        if (result == 0)
        {
            return true;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i< N; i++) // traverse through the buckets
    {
        node* cursor = hashtable[i];
        while(cursor != NULL) // in each buckets linkedlist
        {
            node* temp2 = cursor;
            cursor = cursor->next;
            free(temp2);
        }
    }
    return true;
}
