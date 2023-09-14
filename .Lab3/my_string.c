#include <stdio.h>
#include "my_string.h"
#include <stdlib.h>
#include <ctype.h>

typedef struct my_string{
    int size;
    int cap;
    char* data;
}My_string;
//Precondition: None
//Postcondition: Allocate space for a string object that represents the empty
// string. The string will have capacity 7 and size 0 by default. A copy of
// the address of the opaque object will be returned on success and NULL on
// failure.
MY_STRING my_string_init_default(void)
{
    My_string* pMy_string = (My_string*) malloc(sizeof(My_string));
    if(pMy_string != NULL){
        pMy_string->size = 0;
        pMy_string->cap = 7;
        pMy_string->data = (char*) malloc(pMy_string->cap * sizeof(char));
        if(pMy_string->data == NULL)
        {
            free(pMy_string);
            return NULL;
        }
    }
    return pMy_string;

}

//Precondition: phMy_string holds the address of a valid handle to a MY_STRING
// object.
//Postcondition: The memory used for the MY_STRING object has be reclaimed by
// the system and the handle referred to by the pointer phMy_string has been
// set to NULL.
void my_string_destroy(MY_STRING* phMy_string)
{
    My_string* pString = (My_string*) *phMy_string;
    free(pString->data);
    free(pString);
    *phMy_string = NULL;
}

//Precondtion: c_string is a valid null terminated c-string.
//Postcondition: Allocate space for a string object that represents a string
// with the same value as the given c-string. The capacity of the string
// object will be set to be one greater than is required to hold the string.
// As an example, the string "the" would set capacity at 4 instead of 3. A
// copy of the address of the opaque object will be returned on success and
// NULL on failure.
MY_STRING my_string_init_c_string(const char* c_string)
{
    My_string* pMy_string = (My_string*) malloc(sizeof(My_string));
    int i = 0;
    
    if(pMy_string != NULL){
        pMy_string->size = 0;
        while(c_string[pMy_string->size++] != '\0');
        pMy_string->cap = pMy_string->size + 1;
        pMy_string->data = (char*) malloc(pMy_string->cap * sizeof(char));
        if(pMy_string->data == NULL)
        {
            free(pMy_string);
            return NULL;
        }
        for(i=0; i<pMy_string->size; i++)
            pMy_string->data[i] = c_string[i];
    }
    else{
        return NULL;
    }
    return pMy_string;
    
}

//Precondition: hMy_string is the handle of a valid My_string object.
//Postcondtion: Returns a copy of the integer value of the object's capacity.
int my_string_get_capacity(MY_STRING hMy_string)
{
    My_string* pString = (My_string*) hMy_string;
    return pString->cap;
}

//Precondition: hMy_string is the handle of a valid My_string object.
//Postcondtion: Returns a copy of the integer value of the object's size.
int my_string_get_size(MY_STRING hMy_string)
{
    My_string* pString = (My_string*) hMy_string;
    return pString->size;
}

//Precondition: hLeft_string and hRight_string are valid My_string objects.
//Postcondition: returns an integer less than zero if the string represented
// by hLeft_string is lexicographically smaller than hRight_string. If
// one string is a prefix of the other string then the shorter string is
// considered to be the smaller one. (app is less than apple). Returns
// 0 if the strings are the same and returns a number greater than zero
// if the string represented by hLeft_string is bigger than hRight_string.
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
   int i = 0;
   My_string* pLeft = (My_string*) hLeft_string;
   My_string* pRight = (My_string*) hRight_string;
   /*
   while((i < pLeft->size) && (i < pRight->size))
    {
        printf("comparing %s to %s\n", pLeft->string, pRight->string);
        if(pLeft->string[i] < pRight->string[i])
        {
            printf("%c against %c\n", pLeft->string[i], pRight->string[i]);
            result += (pLeft->string[i] - pRight->string[i]);
            i++;
        }
        else if (pLeft->string[i] > pRight->string[i])
        {
            printf("%c against %c\n", pLeft->string[i], pRight->string[i]);
            result += (pLeft->string[i] - pRight->string[i]);
            i++;
        }
        else
        {
            printf("%c against %c\n", pLeft->string[i], pRight->string[i]);
            result += 0;
            i++;
        }
    }
    if(result == 0 && (pLeft->size < pRight->size))
    {
        return -1;
    }
    else if (result == 0 && (pLeft->size > pRight->size))
    {
        return 1;
    }
    else
        return result;
    */
   while(i < pLeft->size && i < pRight->size && pLeft->data[i] == pRight->data[i])
   {
        i++;
   }
   if(i < pLeft->size && 1< pRight->size && pLeft->data[i] != pRight->data[i])
   {
        return pLeft->data[i] - pRight->data[i];
   }
   return pLeft->size - pRight->size;
   
   return 0;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: hMy_string will be the handle of a string object that contains
// the next string from the file stream fp according to the following rules.
// 1) Leading whitespace will be ignored.
// 2) All characters (after the first non-whitespace character is obtained
// and included) will be added to the string until a stopping condition
// is met. The capacity of the string will continue to grow as needed
// until all characters are stored.
// 3) A stopping condition is met if we read a whitespace character after
// we have read at least one non-whitespace character or if we reach
// the end of the file.
// Function will return SUCCESS if a non-empty string is read successfully.
// and failure otherwise. Remember that the incoming string may aleady
// contain some data and this function should replace the data but not
// necessarily resize the array unless needed.
Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
    My_string* pMy_string = (My_string*) hMy_string;
    int noc, i, c;
    char first_char;
    char* temp;
    if(pMy_string == NULL)
    {
        return FAILURE;
    }
    pMy_string->size = 0; // ignore anything inside.


    noc = fscanf(fp," %c", &first_char);
    if(noc != 1)
    {
        return FAILURE;
    }
    pMy_string->data[pMy_string->size] = first_char;
    pMy_string->size++;

    c = fgetc(fp);
    while(c != EOF && !isspace(c))
    {
        if(pMy_string->size >= pMy_string->cap) // strong condition
        {
            temp = (char*) malloc(sizeof(char)* (2 * pMy_string->cap));
            if(temp == NULL)
            {
                return FAILURE;
            }
            for(i = 0; i < pMy_string->size; i++)
            {
                temp[i] = pMy_string->data[i];
            }
            free(pMy_string->data);
            pMy_string->data = temp;
            pMy_string->cap *= 2;
        }
        pMy_string->data[pMy_string->size] = c;
        pMy_string->size++;
        c = fgetc(fp);
    }
    if(c != EOF)
    {
        ungetc(c, fp);
    }
    return SUCCESS;
}
//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Writes the characters contained in the string object indicated
// by the handle hMy_string to the file stream fp.
// Function will return SUCCESS if it successfully writes the string and
// FAILURE otherwise.
Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
    My_string* pMy_string = (My_string*) hMy_string;
    int i;
    for(i = 0; i < pMy_string->size; i++)
    {
        if(fputc(pMy_string->data[i], fp) == EOF)
        {
            return FAILURE;
        }
    }
    
    return SUCCESS;
}