//#include <stdio.h>
#include "my_string.h"
#include "status.h"
#include <ctype.h>
#include <stdlib.h>

typedef struct my_string {
  int size;
  int cap;
  char *data;
} My_string;
// Precondition: None
// Postcondition: Allocate space for a string object that represents the empty
//  string. The string will have capacity 7 and size 0 by default. A copy of
//  the address of the opaque object will be returned on success and NULL on
//  failure.
MY_STRING my_string_init_default(void) {
  My_string *pMy_string = (My_string *)malloc(sizeof(My_string));
  if (pMy_string != NULL) {
    pMy_string->size = 0;
    pMy_string->cap = 7;
    pMy_string->data = (char *)malloc(pMy_string->cap * sizeof(char));
    if (pMy_string->data == NULL) {
      free(pMy_string);
      return NULL;
    }
    pMy_string->data[0] = '\0';
  }
  return pMy_string;
}

// Precondition: phMy_string holds the address of a valid handle to a MY_STRING
//  object.
// Postcondition: The memory used for the MY_STRING object has be reclaimed by
//  the system and the handle referred to by the pointer phMy_string has been
//  set to NULL.
void my_string_destroy(MY_STRING *phMy_string) {
  My_string *pString = (My_string *)*phMy_string;
  free(pString->data);
  free(pString);
  *phMy_string = NULL;
}

// Precondtion: c_string is a valid null terminated c-string.
// Postcondition: Allocate space for a string object that represents a string
//  with the same value as the given c-string. The capacity of the string
//  object will be set to be one greater than is required to hold the string.
//  As an example, the string "the" would set capacity at 4 instead of 3. A
//  copy of the address of the opaque object will be returned on success and
//  NULL on failure.
MY_STRING my_string_init_c_string(const char *c_string) {
  int i = 0;
  My_string *pMy_string = (My_string *)malloc(sizeof(My_string));
  if (pMy_string != NULL) {
    pMy_string->size = 0;
    while (c_string[++pMy_string->size] != '\0');
    pMy_string->cap = pMy_string->size+1;
    pMy_string->data = (char *)malloc(pMy_string->cap * sizeof(char));
    if (pMy_string->data == NULL) {
      free(pMy_string);
      return NULL;
    }
    for (i = 0; i < pMy_string->size; i++)
      pMy_string->data[i] = c_string[i];
  } else {
    return NULL;
  }
  return pMy_string;
}

// Precondition: hMy_string is the handle of a valid My_string object.
// Postcondtion: Returns a copy of the integer value of the object's capacity.
int my_string_get_capacity(MY_STRING hMy_string) {
  My_string *pString = (My_string *)hMy_string;
  return pString->cap;
}

// Precondition: hMy_string is the handle of a valid My_string object.
// Postcondtion: Returns a copy of the integer value of the object's size.
int my_string_get_size(MY_STRING hMy_string) {
  My_string *pString = (My_string *)hMy_string;
  return pString->size;
}

// Precondition: hLeft_string and hRight_string are valid My_string objects.
// Postcondition: returns an integer less than zero if the string represented
//  by hLeft_string is lexicographically smaller than hRight_string. If
//  one string is a prefix of the other string then the shorter string is
//  considered to be the smaller one. (app is less than apple). Returns
//  0 if the strings are the same and returns a number greater than zero
//  if the string represented by hLeft_string is bigger than hRight_string.
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string) {
  int i = 0;
  My_string *pLeft = (My_string *)hLeft_string;
  My_string *pRight = (My_string *)hRight_string;

  while (i < pLeft->size && i < pRight->size &&
         pLeft->data[i] == pRight->data[i]) {
    i++;
  }
  if (i < pLeft->size && i < pRight->size &&
      pLeft->data[i] != pRight->data[i]) {
    return pLeft->data[i] - pRight->data[i];
  }
  return pLeft->size - pRight->size;

  return 0;
}

// Precondition: hMy_string is the handle to a valid My_string object.
// Postcondition: hMy_string will be the handle of a string object that contains
//  the next string from the file stream fp according to the following rules.
//  1) Leading whitespace will be ignored.
//  2) All characters (after the first non-whitespace character is obtained
//  and included) will be added to the string until a stopping condition
//  is met. The capacity of the string will continue to grow as needed
//  until all characters are stored.
//  3) A stopping condition is met if we read a whitespace character after
//  we have read at least one non-whitespace character or if we reach
//  the end of the file.
//  Function will return SUCCESS if a non-empty string is read successfully.
//  and failure otherwise. Remember that the incoming string may aleady
//  contain some data and this function should replace the data but not
//  necessarily resize the array unless needed.
Status my_string_extraction(MY_STRING hMy_string, FILE *fp) {
  My_string *pMy_string = (My_string *)hMy_string;
  int noc, i = 0, j = 0, c;
  char *temp;
  if (pMy_string == NULL) {
    printf("pMy_string NULL\n");
    return FAILURE;
  }
  pMy_string->size = 0; // ignore anything inside.

  /* c = fgetc(fp); */
  /* while(c != EOF && c != '\n' && c != ' ') */
  /* { */
  /*     printf("noc is %d and char is %c\n", noc, first_char); */
  /*     noc = fscanf(fp," %c", &first_char); */
  /* } */
  /* pMy_string->data[pMy_string->size] = first_char; */
  /* pMy_string->size++; */

  c = fgetc(fp);
  if (c == ' ' && c != EOF)
    c = fgetc(fp);
  while (c != EOF && c != ' ' && c != '\n') {
    if (pMy_string->size >= pMy_string->cap) // strong condition
    {
      temp = (char *)malloc(sizeof(char) * (2 * pMy_string->cap));
      if (temp == NULL) {
        printf("temp equals NULL\n");
        return FAILURE;
      }
      for (i = 0; i < pMy_string->size; i++) {
        temp[i] = pMy_string->data[i];
      }
      free(pMy_string->data);
      pMy_string->data = temp;
      pMy_string->cap *= 2;
    }
    pMy_string->data[j] = c;
    j++;
    pMy_string->size++;
    c = fgetc(fp);
  }
  if (c == ' ') {
    if (j != 0)
      ungetc(c, fp);
  }
  if (pMy_string->size == 0) {
    return FAILURE;
  }
  return SUCCESS;
}

// Precondition: hMy_string is the handle to a valid My_string object.
// Postcondition: Writes the characters contained in the string object indicated
//  by the handle hMy_string to the file stream fp.
//  Function will return SUCCESS if it successfully writes the string and
//  FAILURE otherwise.
Status my_string_insertion(MY_STRING hMy_string, FILE *fp) {
  My_string *pMy_string = (My_string *)hMy_string;
  int i;
  for (i = 0; i < pMy_string->size; i++) {
    if (fputc(pMy_string->data[i], fp) == EOF) {
      return FAILURE;
    }
  }

  return SUCCESS;
}

// Precondition: hMy_string is the handle to a valid My_string object.
// Postcondition: If successful, places the character item at the end of the
//  string and returns SUCCESS. If the string does not have enough room and
//  cannot resize to accomodate the new character then the operation fails
//  and FAILURE is returned. The resize operation will attempt to amortize
//  the cost of a resize by making the string capacity somewhat larger than
//  it was before (up to 2 times bigger).
Status my_string_push_back(MY_STRING hMy_string, char item) {
  My_string *pMy_string = (My_string *)hMy_string;
  int i;
  if (pMy_string != NULL && pMy_string->size >= pMy_string->cap) {
    char *temp = (char *)malloc(sizeof(char) * 2 * pMy_string->cap);
    if (temp == NULL) {
      return FAILURE;
    }
    for (i = 0; i < pMy_string->size; i++)
      temp[i] = pMy_string->data[i];
    free(pMy_string->data);
    pMy_string->data = temp;
    pMy_string->cap *= 2;
    // resize then push back
    pMy_string->data[pMy_string->size++] = item;

    return SUCCESS;
  } else if (pMy_string != NULL) {
    // push back
    pMy_string->data[pMy_string->size++] = item;
    return SUCCESS;
  }
  return FAILURE;
}

// Precondition: hMy_string is the handle to a valid My_string object.
// Postcondition: Removes the last character of a string in constant time.
//  Guaranteed to not cause a resize operation of the internal data. Returns
//  SUCCESS on success and FAILURE if the string is empty.
Status my_string_pop_back(MY_STRING hMy_string) {
  My_string *pMy_string = (My_string *)hMy_string;
  if (pMy_string->size > 0) {
    pMy_string->size--;
    return SUCCESS;
  }
  return FAILURE;
}

// Precondition: hMy_string is the handle to a valid My_string object.
// Postcondition: Returns the address of the character located at the given
//  index if the index is in bounds but otherwise returns NULL. This address
//  is not usable as a c-string since the data is not NULL terminated and is
//  intended to just provide access to the element at that index.
char *my_string_at(MY_STRING hMy_string, int index) {
  My_string *pMy_string = (My_string *)hMy_string;
  if (index >= 0 && index < pMy_string->size) {
    return &pMy_string->data[index];
  }
  return NULL;
}

// Precondition: hMy_string is the handle to a valid My_string object.
// Postcondition: Returns the address of the first element of the string object
//  for use as a c-string. The resulting c-string is guaranteed to be NULL
//  terminated and the memory is still maintained by the string object though
//  the NULL is not actually counted as part of the string (in size).
char *my_string_c_str(MY_STRING hMy_string) {
  My_string *pMy_string = (My_string *)hMy_string;
  if (hMy_string == NULL)
    return NULL;
  if (my_string_at(hMy_string, pMy_string->size - 1) != NULL) {
    my_string_push_back(hMy_string, '\0');
    my_string_pop_back(hMy_string);
  }
  return pMy_string->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend) {
  int i;
  // My_string* pMy_result = (My_string*) hResult;
  My_string *pMy_append = (My_string *)hAppend;

  for (i = 0; i < pMy_append->size; i++) {
    if (!my_string_push_back(hResult, pMy_append->data[i]))
      return FAILURE;
  }
  my_string_c_str(hResult);
  return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string) {
  My_string *pMy_string = (My_string *)hMy_string;
  return pMy_string->size == 0;
}
// Lab 6
Status my_string_assignment(MY_STRING hLeft, MY_STRING hRight) {
  int i, j;
  char *temp;
  My_string* pLeft = (My_string*)hLeft;
  My_string* pRight = (My_string*)hRight;
  if(pLeft == NULL){
    pLeft = my_string_init_c_string(my_string_c_str(pRight));
    if(pLeft == NULL){
      return FAILURE;
    }
    return SUCCESS;
  }
  if (pRight->size >= pLeft->cap) {
    /* printf("Resize\n"); */
    temp = (char *)malloc(sizeof(char) * pRight->size + 1);
    if (temp == NULL) {
      return FAILURE;
    }
    free(pLeft->data);
    pLeft->data = temp;
    pLeft->cap = pRight->size + 1;
  }
  for (i = 0; i < pRight->size; i++) {
    pLeft->data[i] = pRight->data[i];
  }
  pLeft->size = pRight->size;
  return SUCCESS;
}

//Precondition: hMy_string is the handle to a valid MY_STRING object.
//Postcondition: Will return the handle to a valid MY_STRING object that
//is a deep copy of the object indicated by hMy_string. This means the
//copied object will be a complete and independent copy and not share
//any data with the object we are copying from. On failure the function will
//return NULL.
MY_STRING my_string_init_copy(MY_STRING hMy_string){
   My_string *pMy_string = (My_string *)hMy_string;
   int i;
   MY_STRING pCopy_string = my_string_init_default();
   if(my_string_assignment(pCopy_string, pMy_string))
       return pCopy_string;
   else{
     printf("Failed assignment -- destroying");
       my_string_destroy(&pCopy_string); // clean up
       return NULL;
   }
}

//Precondition: hLeft and hRight are handles to valid MY_STRING objects.
//Postcondition: After the function hLeft will contain the size capacity and
//data of the object indicated by hRight and hRight will contain
//the size capacity and data of the oject indicated by hLeft. This function
//will be much faster than making deep copies of the objects using
//my_string_assignment and attempting to swap them in the traditional way
//calling my_string assignment in place of the '=' below.
//temp = a;
//a = b;
//b = temp;
void my_string_swap(MY_STRING hLeft, MY_STRING hRight){
  My_string* pLeft = (My_string*)hLeft;
  My_string* pRight = (My_string*)hRight;
  My_string* pTemp = (My_string*) malloc(sizeof(My_string));
  if(pTemp == NULL){
    printf("Failed swap");
  }
  else{
    pTemp->cap = 0;
    pTemp->size = 0;
    pTemp->data = NULL;
    /* pTemp = pLeft; */
    pTemp->cap = pLeft->cap;
    pTemp->size = pLeft->size;
    pTemp->data = pLeft->data;
    /* pLeft = pRight; */
    pLeft->cap = pRight->cap;
    pLeft->size = pRight->size;
    pLeft->data = pRight->data;
    /* pRight = pTemp; */
    pRight->cap = pTemp->cap;
    pRight->size = pTemp->size;
    pRight->data = pTemp->data;
    free(pTemp);
  }
}


//Precondition:current_word_family, new_key and word are all handles to valid
// MY_STRING opaque objects. guess is an alphabetical character that can be either
// upper or lower case.
//Postcondition: Returns SUCCESS after replacing the string in new_key with the key
// value formed by considering the current word family, the word and the guess.
// Returns failure in the case of a resizing problem with the new_key string.
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key,
                          MY_STRING word, char guess) {
  My_string *pCurrent_word_family = (My_string *)current_word_family;
  My_string *pNew_key = (My_string *)new_key;
  My_string *pWord = (My_string *)word;
  int i, size = 0;
  char temp;
  for(i= 0 ; i< my_string_get_size(new_key); i++)
    my_string_pop_back(new_key);

  guess = (char)tolower(guess);
  // find instances of guess letter in the word
  for (i = 0; i < pWord->size; i++) {
    temp = pWord->data[i];
    temp = (char)tolower(temp);

    if (temp == guess) {
      if (!my_string_push_back(pNew_key, guess)) {
        return FAILURE;
      }
    } else {
      if (!my_string_push_back(pNew_key, pCurrent_word_family->data[i])) {
        return FAILURE;
      }
    }
  }
  return SUCCESS;

  // if word contains guess char then
  // current word family gets updates with the new guess
  // new_key gets the current family
  // else then the new_key = current word family
}

Boolean HasItBeenUsed(MY_STRING hMy_string, char guess){
  My_string *pMy_string = (My_string *)hMy_string;
  int i;
  for(i = 0; i < pMy_string->size; i++){
    if(pMy_string->data[i] == guess){
      return TRUE;
    }
  }
  return FALSE;
}
