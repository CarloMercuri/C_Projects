#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

bool IsCypherKeyValid(string key);
bool IsCharLetter(char c);
bool IsUpperCase(char c);
int GetAlphabetCharPosition(char c, bool isUpper);
char ToUpper(char c);
char ToLower(char c);
string EncryptText(string text, string cypher);

int cypherLenght = 26;



int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Only accepting one argument in the form of the cypher key\n");
        return 1;
    }
    else
    {
        if (!IsCypherKeyValid(argv[1]))
        {
            printf("Invalid key. Must be 26 characters long, only contain a-z letters and no letter repetition allowed.\n");
            return 1;
        }

    }
    
    string plainText = get_string("plaintext: ");
    
    string encryptedText = EncryptText(plainText, argv[1]);
    
    printf("ciphertext: %s\n", encryptedText);
    

}

// I'm not checking if it's a letter, because when it gets called it's already been checked
// Returns 0 to 25 (a = 0, z = 25)
int GetAlphabetCharPosition(char c, bool isUpper)
{
    int cInt = (int)c;
    
    if (isUpper)
    {
        return cInt - 65;
    }
    else
    {
        return cInt - 97;
    }
}

string EncryptText(string text, string cypher)
{
    bool isUpper;
    
    for (int i = 0; i < strlen(text); i++)
    {
        if (!IsCharLetter(text[i]))
        {
            continue;
        }
        // Gather some info on the char
        int tCharInt = (int)text[i];
        isUpper = IsUpperCase(text[i]);
        // Get the alphabet position (0-25) of the char in the text to encrypt
        int alphabetPos = GetAlphabetCharPosition(text[i], isUpper);
          
        if (isUpper)
        {
            text[i] = ToUpper(cypher[alphabetPos]);
        }
        else
        {
            text[i] = ToLower(cypher[alphabetPos]);
        }
    }
    return text;
}

char ToUpper(char c)
{
    int cInt = (int)c;
    
    // if it's lower case
    if (cInt > 96 && cInt < 123)
    {
        return (char)cInt - 32;
    }
    else
    {
        return c;
    }
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

bool IsUpperCase(char c)
{
    if ((int)c > 64 && (int)c < 91)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool IsCharInArray(char array[], int n, char c)
{
    int charInt = (int)c;
    
    bool isUpper = IsUpperCase(c);
    
    for (int i = 0; i < n; i++)
    {
        if (isUpper)
        {
            if (charInt == array[i] || charInt + 32 == array[i])
            {
                return true;
            }

        }
        else
        {
            if (charInt == array[i] || charInt - 32 == array[i])
            {
                return true;
            }
        }
        
    }
    
    return false;
}

bool IsCypherKeyValid(string key)
{
    int stringLenght = strlen(key);
    
    if (stringLenght != cypherLenght)
    {
        return false;
    }

    char charArray[cypherLenght];
    
    // Need this because the char array gets created with random chars, and sometimes there are letters already in it
    for (int u = 0; u < cypherLenght; u++)
    {
        charArray[u] = '_';
    }
    
    for (int i = 0; i < stringLenght; i++)
    {
        if (!IsCharLetter(key[i]))
        {
            return false;
        }
        
        if (IsCharInArray(charArray, cypherLenght, key[i]))
        {
            return false;
        }
        else
        {
            charArray[i] = key[i];
        }
    }
    
    return true;
    
    
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