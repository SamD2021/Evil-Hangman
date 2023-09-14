#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>

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
        pMy_string->data = (char*) malloc(pMy_string->cap*sizeof(char));
        if(pMy_string == NULL)
        {
            free(pMy_string);
            return NULL;
        }
    }
    else{
        return NULL;
    }
    return (MY_STRING) pMy_string;

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
    pString = NULL;
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
    int len = 0, i = 0;
    while(c_string[len++] != '\0');
    My_string* pMy_string = (My_string*) malloc(sizeof(My_string));
    if(pMy_string != NULL){
        pMy_string->size = len-1;
        pMy_string->cap = len;
        pMy_string->data = (char*) malloc(pMy_string->cap*sizeof(char));
        if(pMy_string == NULL)
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
    return (MY_STRING) pMy_string;
    
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
    /*
    String* left = (String*) hLeft_string;
    String* right = (String*) hRight_string;
    while(*(left->string))
    {
        if(*(left->string) != *(right->string))
        {
            break;
        }
        left->string++;
        right->string++;
    }
    return (const unsigned char*) *(left->string) - (const unsigned char*) *(right->string);
    */
   int result = 0, i = 0;
   My_string* pLeft = (My_string*) hLeft_string;
   My_string* pRight = (My_string*) hRight_string;
   while((i < pLeft->size) && (i < pRight->size))
    {
        printf("comparing %s to %s\n", pLeft->data, pRight->data);
        if(pLeft->data[i] < pRight->data[i])
        {
            printf("%c against %c\n", pLeft->data[i], pRight->data[i]);
            result += (pLeft->data[i] - pRight->data[i]);
            i++;
        }
        else if (pLeft->data[i] > pRight->data[i])
        {
            printf("%c against %c\n", pLeft->data[i], pRight->data[i]);
            result += (pLeft->data[i] - pRight->data[i]);
            i++;
        }
        else
        {
            printf("%c against %c\n", pLeft->data[i], pRight->data[i]);
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
}
