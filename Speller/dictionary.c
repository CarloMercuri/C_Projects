// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
    
}
node;



typedef struct _node
{
    char c;
    struct _node *nArray[26];
    bool isEnd;
}
_node;

_node ogArray[26];
typedef uint8_t BYTE;
int dictSize = 0;
_node *currentNodePtr;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int wLenght = strlen(word);
    
    char copy[strlen(word) + 1];
    strcpy(copy, word);
    char *p = copy;
    for (; *p; ++p)
    {
        *p = ToLower(*p);
    }
    
    // make it lower case
    for (int i = 0; i < wLenght; i++)
    {
        if (!IsCharLetter(copy[i]))
        {
            continue;
        }
        
        copy[i] = ToLower(copy[i]);
    }
    
    _node *tmpNode;// = malloc(sizeof(struct _node));
    _node *transNode;//  = malloc(sizeof(struct _node));
    char cc = copy[0];
    int alphaNumber = GetAlphabetNr(cc);

    if (alphaNumber < 0 || alphaNumber > 25)
    {
        printf("Error");
     
    }
    
    if (ogArray[alphaNumber].c == (char)0x00)
    {
        return false;
    }
    

    
    tmpNode = &ogArray[alphaNumber];
    
    if (tmpNode == NULL)
    {

        return false;
    }
    
    if (wLenght == 1)
    {
        if (ogArray[alphaNumber].isEnd == true)
        {
            return true;
        }
        else
        {
            return false;
            
        }
    }
  
    
    for (int i = 1; i < wLenght; i++)
    {
        cc = copy[i];
        alphaNumber = GetAlphabetNr(cc);
        
        if (alphaNumber < 0 || alphaNumber > 25)
        {
            continue;
        }
        
        if (tmpNode->nArray[alphaNumber] == NULL)
        {
            return false;
        }
        
        if (tmpNode->nArray[alphaNumber]->c == 0x00)
        {

            return false;
        }
        
    
        
        transNode = tmpNode->nArray[alphaNumber];
        tmpNode = transNode;
    }
    if (tmpNode->isEnd)
    {

        return true;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    return 0;
}

void ListAdd(char _word[])
{
   
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dicFile = fopen(dictionary, "r");
    char *_word[LENGTH + 1];
    char *_letter[1];
     

    char buffer[LENGTH];
    
    int wLenght = 0;
    int alphaNumber = 0;
    char cc;
    int loops = 0;
    dictSize = 0;
    
    _node *tmpNode;// = malloc(sizeof(struct _node));
    _node *transNode;//  = malloc(sizeof(struct _node));
    
    while (fscanf(dicFile, "%s", buffer) != EOF)
    {
        dictSize++;
        loops++;
        wLenght = strlen(buffer);
        cc = buffer[0];
        alphaNumber = GetAlphabetNr(cc);
        
        if (ogArray[alphaNumber].c == 0x00)
        {
            ogArray[alphaNumber].c = cc;
        }
        
        tmpNode = &ogArray[alphaNumber];
        
        for (int i = 1; i < wLenght; i++)
        {
            
            cc = buffer[i];
            alphaNumber = GetAlphabetNr(cc);
            
            if (alphaNumber < 0 || alphaNumber > 25)
            {
                continue;
            }

            if (tmpNode->nArray[alphaNumber] == NULL)
            {
                tmpNode->nArray[alphaNumber] = malloc(sizeof(_node));

            }

            if (tmpNode->nArray[alphaNumber]->c == 0x00)
            {
                
                tmpNode->nArray[alphaNumber]->c = cc;
            }

            transNode = tmpNode->nArray[alphaNumber];
            tmpNode = transNode;
            
            
        }
        tmpNode->isEnd = true;
    }

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictSize;
    //return 0;
}

bool SearchAndDestroy()
{
    return false;
    
}

// Unloads dictionary from memory, returning true if successful else false
_node *tmp;
bool unload(void)
{
    

     for(int i = 0; i < 26; i++)
     {
         for(int u = 0; u < 26; u++)
         {
             tmp = ogArray[i].nArray[u];
         }
         
         free(tmp);
         
     }
     
     
     return true;
    
}

int GetAlphabetNr(char c)
{
    return c - 97;
}

char ToLower(char c)
{
    int cInt = (int)c;
    
    if (cInt > 64 && cInt < 91)
    {
        return (char)cInt + 32;
    }
    else
    {
        return c;
    }
}

bool IsCharLetter(char c)
{
    // making my life easier
    int cInt = (int)c;

    if (cInt > 64 && cInt < 91)
    {
        return true;
    }
   
    if (cInt > 96 && cInt < 123)
    {
        return true;
    }
   
   
    return false;
        
}