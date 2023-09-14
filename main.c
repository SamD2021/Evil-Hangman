#include "generic_vector.h"
#include "my_string.h"
#include "associativearray.h"
#include "status.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define Whole_dictionary 0
#define main_fn 1
#define hangman 0
#define Associate 0
#define Checkpoint_lab_8 0
GENERIC_VECTOR GetWholeDictionary(void);

#if main_fn

#define MAX_LENGTH 30
#define MAX_LETTERS 26

Boolean Evil_Hangman(int word_length, int guess_amount, Boolean ShowTotalRemaining, GENERIC_VECTOR hVectorOfWordLenth);
int getWordLength(void);
int getGuessAmount(void);
char getCurrentGuess(MY_STRING guessList);
Boolean getCheatsChoice(void);
Boolean getReplay(void);
void printHangman(void);
GENERIC_VECTOR CheckIfGuessInWord(MY_STRING* phGuessList, GENERIC_VECTOR hVectorOfWordList, MY_STRING hCurrentKey, char currentGuess, Boolean showTotalRemaining);


void ClearKeyboardBuffer(void);

int main(int argc, char *argv[]) {
  /* GetWholeDictionary */
  GENERIC_VECTOR hVectorOfWholeDicitionary[MAX_LENGTH] = {NULL};
  int i = 0, j;
  FILE *fp;
  for (i = 0; i < MAX_LENGTH; i++) {
    hVectorOfWholeDicitionary[i] =
        generic_vector_init_default(my_string_init_copy, my_string_destroy);
    if (hVectorOfWholeDicitionary[i] == NULL) {
      printf("Failed to allocate space for generic vector.\n");
      exit(1);
    }
  }
  MY_STRING hMyString = my_string_init_default();
  if (hMyString == NULL) {
    printf("Failed to get item at my_string_init_default for hMyString.\n");
    exit(1);
  }
  fp = fopen("dictionary.txt", "r");
  if (fp == NULL) {
    printf("Failed to open dictionary.txt\n");
    exit(1);
  }

  while (my_string_extraction(hMyString, fp)) {
    j = my_string_get_size(hMyString);
    if (j >= 0 && j < MAX_LENGTH)
      generic_vector_push_back(hVectorOfWholeDicitionary[j], hMyString);
  }
  for(i = 0; i < MAX_LENGTH; i++)
    printf("%d:%d\n", i, generic_vector_get_size(hVectorOfWholeDicitionary[i]));

  fclose(fp);
  my_string_destroy(&hMyString);

  /*  End of GetWhole Dictionary */

  Boolean KeepGoing = TRUE;
  do {
    printHangman();
    // prompt user for word length
    int word_len = 0;
    word_len = getWordLength();
    // prompt user for number of guesses
    int guesses = 0;
    guesses = getGuessAmount();
    // prompt user for total numbers of remaining words
    Boolean ShowTotalRemaining = FALSE;
    ShowTotalRemaining = getCheatsChoice();
    // algorithm
    //
    // a) selecting the vector of all words that matches word len

    Evil_Hangman(word_len, guesses, ShowTotalRemaining,
                 hVectorOfWholeDicitionary[word_len]);
    KeepGoing = getReplay();
  } while (KeepGoing);
  /* Clean up */
  for (i = 0; i < MAX_LENGTH; i++) {
    generic_vector_destroy(&hVectorOfWholeDicitionary[i]);
  }
  return 0;
}

Boolean Evil_Hangman(int word_length, int guess_amount, Boolean ShowTotalRemaining, GENERIC_VECTOR hVectorOfWordLength){
   //algorithm
  //
  //

  int i, j;
  GENERIC_VECTOR hNewWordFamily = NULL;
  Boolean TheyWon= FALSE;
  MY_STRING hMyString = NULL, hCurrentKey = NULL, hNewKey = NULL, hCurrentWord = NULL, guessedLetters = NULL;
  char currentGuess;

  //a) selecting the vector of all words that matches word len


  guessedLetters = my_string_init_default();
  if (guessedLetters == NULL) {
    printf("Failed to get item at my_string_init_default for hMyString.\n");
    exit(1);
  }

  hMyString = my_string_init_default();
  if (hMyString == NULL) {
    printf("Failed to get item at my_string_init_default for hMyString.\n");
    exit(1);
  }

  hCurrentKey = my_string_init_default();
  if (hCurrentKey == NULL) {
    printf("Failed to get item at my_string_init_default for hMyString.\n");
    exit(1);
  }

  hNewWordFamily = generic_vector_init_default(my_string_init_copy, my_string_destroy);
  if (hNewWordFamily == NULL) {
    printf("Failed to generic_vector_init_default for hNewWordFamily.\n");
    exit(1);
  }
  for(i = 0; i < generic_vector_get_size(hVectorOfWordLength); i++){
    generic_vector_push_back(hNewWordFamily, (MY_STRING)*generic_vector_at(hVectorOfWordLength, i));
  }


  for(i = 0; i < word_length; i++)
    my_string_push_back(hCurrentKey, '-');

  for (i = guess_amount; i > 0; i--) {
    // b) print guesses remaining, guessed letters, current blanked-out word
    printf("Remaining guesses: %d\n", i);

    printf("Guessed letters: ");
    if (my_string_get_size(guessedLetters) == 0)
      printf("None yet!\n");
    else {
      my_string_insertion(guessedLetters, stdout);
      printf("\n");
    }

    printf("Current word:%s", my_string_c_str(hCurrentKey));

    if (ShowTotalRemaining) { // use search to print every key and the size of
                              // the vector
      generic_vector_get_size(hVectorOfWordLength);
    }
    printf("\n");

    // c)prompt user to guess letter
    //
    currentGuess = getCurrentGuess(guessedLetters);
    my_string_push_back(guessedLetters, currentGuess);
    my_string_push_back(guessedLetters, '|');
    hNewWordFamily =
        CheckIfGuessInWord(&guessedLetters, hNewWordFamily, hCurrentKey,
                           currentGuess, ShowTotalRemaining);
    if (my_string_compare((MY_STRING)*generic_vector_at(hNewWordFamily, 0),
                          hCurrentKey) == 0) {
      printf("You Won!\n Here's the Word:");
      printf("%s\n",
             my_string_c_str((MY_STRING)*generic_vector_at(hNewWordFamily, 0)));
      TheyWon = TRUE;
      break;
    }
  }
  if (!TheyWon) {
    printf("You lost! Not everyone can be a winner, specially you ;D\n");
    printf("The word was %s!\n",
           my_string_c_str((MY_STRING)*generic_vector_at(hNewWordFamily, 0)));
    TheyWon = FALSE;
  }

  /* Clean up */
  generic_vector_destroy(&hNewWordFamily);// takes care of max
  my_string_destroy(&guessedLetters);
  my_string_destroy(&hMyString);
  my_string_destroy(&hCurrentKey);
  return TheyWon;
}

GENERIC_VECTOR CheckIfGuessInWord(MY_STRING* phGuessList, GENERIC_VECTOR hVectorOfWordList, MY_STRING hCurrentKey, char currentGuess, Boolean showTotalRemaining){
  int i, guessListSize = 0;
  ASSOCIATIVE_ARR hArr = NULL;
  MY_STRING hCurrentWord = NULL, hNewKey = NULL, *pTemp = NULL, hMyString = NULL, hGuessList = *phGuessList;
  GENERIC_VECTOR hMaxVector = NULL;

  hNewKey = my_string_init_default();
  if (hNewKey == NULL) {
    printf("Failed to get item at my_string_init_default for hMyString.\n");
    exit(1);
  }

  hArr = associray_init_default();
  if (hArr == NULL) {
    printf("Failed to allocate space for associative array.\n");
    exit(1);
  }
  /* // adds all the words of same length under the same blank key */
  //Partitions all the current words
  for (i = 0; i < generic_vector_get_size(hVectorOfWordList); i++) {
    pTemp = (MY_STRING*) generic_vector_at(hVectorOfWordList, i);
    if (pTemp == NULL) {
      printf(
          "Failed at CheckIfGuessInWord while printing all partions of the current words came back null\n");
      exit(1);
    }
    hCurrentWord = *pTemp;
    get_word_key_value(hCurrentKey, hNewKey,(MY_STRING) *generic_vector_at(hVectorOfWordList, i), currentGuess);
    associray_insert(hArr, (MY_STRING) *generic_vector_at(hVectorOfWordList, i), hNewKey);
    while(!my_string_empty(hNewKey)){// clear the string
      my_string_pop_back(hNewKey);
    }
  }
  // Choose max size
  hMaxVector = associray_init_find_max(hArr, showTotalRemaining);
  if(hMaxVector == NULL){
    printf("Failed to find_max\n");
    exit(1);
  }

  generic_vector_destroy(&hVectorOfWordList);
  hVectorOfWordList = hMaxVector;
  while(!my_string_empty(hNewKey)){// clear the string
      my_string_pop_back(hNewKey);
    }
  get_word_key_value(hCurrentKey, hNewKey, (MY_STRING)*generic_vector_at(hVectorOfWordList, 0), currentGuess);
  if(my_string_compare(hCurrentKey, hNewKey) == 0){
    printf("\n\nIncorrect Guess. The word doesn't have any character %c in it \n", currentGuess);
  }else
    my_string_assignment(hCurrentKey, hNewKey);

  associray_destroy(&hArr);
  my_string_destroy(&hNewKey);
  return hVectorOfWordList;
}

char getCurrentGuess(MY_STRING guessList) { // change comparison to a my_string object
  int i;
  int noc = 0;
  Boolean HasBeenUsed = FALSE;
  char singleGuess;
  do{
    noc = 9;
    printf("Make a guess using a letter you havent used before:");
    noc = scanf(" %c", &singleGuess);
    ClearKeyboardBuffer();
    if (noc == 1 && isalpha(singleGuess)) {
      HasBeenUsed = HasItBeenUsed(guessList, singleGuess);
    } else {
      printf("You have guessed this letter already or invalid character, Try again!\n");
    }
  } while ((noc != 1 || !isalpha(singleGuess)) || HasBeenUsed == TRUE);
  return singleGuess;
}

int getWordLength(void){
  int wordLen = -1;
  do{

  printf("What word length would you like to play with? ");
  scanf("%d", &wordLen);
  ClearKeyboardBuffer();
  }while((wordLen < 2 || wordLen > 29) || wordLen == 23 || wordLen == 25 || wordLen == 26 || wordLen == 27);
  return wordLen;
}

int getGuessAmount(void){
  int amount = -1;
  do{

  printf("How many guesses you need? ");
  scanf("%d", &amount);
  ClearKeyboardBuffer();
  }while(amount < 0);
  return amount;
}

Boolean getCheatsChoice(void){
  int choice = -1;
  do{

  printf("Do you want to be a cheater and see remaining choices?\n Choose between yes (1) or no (0): ");
  scanf("%d", &choice);
  ClearKeyboardBuffer();
  }while(choice != 0 && choice != 1);
  return choice;
}

Boolean getReplay(void){
  int choice = -1;
  do{

  printf("Wanna play again?\n Choose between yes (1) or no (0): ");
  scanf("%d", &choice);
  ClearKeyboardBuffer();
  }while(choice != 0 && choice != 1);
  return choice;
}

void printHangman(void){
  printf("\n");
  printf(" .----------------.  .----------------.  .-----------------. .----------------.  .----------------.  .----------------.  .-----------------.\n");
  printf("| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n");
  printf("| |  ____  ____  | || |      __      | || | ____  _____  | || |    ______    | || | ____    ____ | || |      __      | || | ____  _____  | |\n");
  printf("| | |_   ||   _| | || |     /  \\     | || ||_   \\|_   _| | || |  .' ___  |   | || ||_   \\  /   _|| || |     /  \\     | || ||_   \\|_   _| | |\n");
  printf("| |   | |__| |   | || |    / /\\ \\    | || |  |   \\ | |   | || | / .'   \\_|   | || |  |   \\/   |  | || |    / /\\ \\    | || |  |   \\ | |   | |\n");
  printf("| |   |  __  |   | || |   / ____ \\   | || |  | |\\ \\| |   | || | | |    ____  | || |  | |\\  /| |  | || |   / ____ \\   | || |  | |\\ \\| |   | |\n");
  printf("| |  _| |  | |_  | || | _/ /    \\ \\_ | || | _| |_\\   |_  | || | \\ `.___]  _| | || | _| |_\\/_| |_ | || | _/ /    \\ \\_ | || | _| |_\\   |_  | |\n");
  printf("| | |____||____| | || ||____|  |____|| || ||_____|\\____| | || |  `._____.'   | || ||_____||_____|| || ||____|  |____|| || ||_____|\\____| | |\n");
  printf("| |              | || |              | || |              | || |              | || |              | || |              | || |              | |\n");
  printf("| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
  printf(" '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n");
  printf("\n");
}

void ClearKeyboardBuffer(void){
  char c = ' ';
  char noc= 10;
  noc = scanf("%c", &c);
  while(noc !=1 && c != '\n'){
    noc = scanf("%c", &c);
  }
}


#endif

#if Associate

#define WORD_LENGTH 3

int main(int argc, char *argv[]) {
  GENERIC_VECTOR hVector = NULL, hVectorResult = NULL;
  ASSOCIATIVE_ARR hArr = NULL;
  int i = 0, j, count = 0;
  FILE *fp;
  hArr = associray_init_default();
  if (hArr == NULL) {
    printf("Failed to allocate space for associray.\n");
    exit(1);
  }
  hVector = generic_vector_init_default(my_string_init_copy, my_string_destroy);
  if (hVector == NULL) {
    printf("Failed to allocate space for generic vector.\n");
    exit(1);
  }
  MY_STRING hMyString = my_string_init_default();
  if (hMyString == NULL) {
    printf("Failed to get item at my_string_init_default for hMyString.\n");
    exit(1);
  }
  fp = fopen("dictionary.txt", "r");
  if (fp == NULL) {
    printf("Failed to open dictionary.txt\n");
    exit(1);
  }

  while (my_string_extraction(hMyString, fp)) {
    j = my_string_get_size(hMyString);
    if (j == WORD_LENGTH){
      generic_vector_push_back(hVector, hMyString);
      count++;
    }
  }
  while(!my_string_empty(hMyString)){
    my_string_pop_back(hMyString);
  }
  for (i = 0; i < WORD_LENGTH; i++)
    my_string_push_back(hMyString, '-');
  for (j = 0; j < generic_vector_get_size(hVector); j++) {
    associray_insert(hArr, hVector,
                     hMyString);
  }
  printf("%s:%d\n", my_string_c_str(hMyString), count);
  associray_print(hArr);
  printf("\n");
  my_string_pop_back(hMyString);
  my_string_push_back(hMyString, 'l');
  for (j = 0; j < generic_vector_get_size(hVector); j++) {
    associray_insert(hArr, hVector,
                     hMyString);
  }

  hVectorResult = associray_search(hArr, hMyString);
  if(hVectorResult != NULL){
    printf("The first word on the vector is %s\n", my_string_c_str((MY_STRING)*generic_vector_at(hVectorResult, 0)));
  }
  else{
    printf("not found\n");
  }
  associray_inorder(hArr);
  associray_destroy(&hArr);
  generic_vector_destroy(&hVector);
  fclose(fp);
  my_string_destroy(&hMyString);
  return 0;
}
#endif

#if Checkpoint_lab_8
int main(int argc, char *argv[]) {
  int i;
  MY_STRING old_key[4] = {NULL}, word[4] = {NULL}, new_key[4] = {NULL};
  char guess[4];
  old_key[0] = my_string_init_c_string("---");
  word[0] = my_string_init_c_string("The");
  guess[0] = 'T';

  old_key[1] = my_string_init_c_string("-----");
  word[1] = my_string_init_c_string("Truck");
  guess[1] = 'r';

  old_key[2] = my_string_init_c_string("--ppy");
  word[2] = my_string_init_c_string("happy");
  guess[2] = 'h';

  old_key[3] = my_string_init_c_string("--e---e");
  word[3] = my_string_init_c_string("awesome");
  guess[3] = 'z';

  for(i = 0; i < 4; i++){
    new_key[i] = my_string_init_default();
    if(new_key[i] == NULL){
      printf("Failed to init default new keys at %d", i);
      exit(1);
    }
  }

  for (i = 0; i < 4; i++) {
    get_word_key_value(old_key[i], new_key[i], word[i], guess[i]);
    printf("old_key: %3s | word: %3s | guess: %3c | new_key: %3s \n", my_string_c_str(old_key[i]), my_string_c_str(word[i]), guess[i], my_string_c_str(new_key[i]));
    my_string_destroy(&old_key[i]);
    my_string_destroy(&new_key[i]);
    my_string_destroy(&word[i]);
  }
  return 0;
}
#endif


#if Whole_dictionary

#define MAX_LENGTH 30
GENERIC_VECTOR GetWholeDictionary(void) {
  GENERIC_VECTOR hVector[MAX_LENGTH] = {NULL};
  int i = 0, j;
  FILE *fp;
  for (i = 0; i < MAX_LENGTH; i++) {
    hVector[i] =
        generic_vector_init_default(my_string_init_copy, my_string_destroy);
    if (hVector[i] == NULL) {
      printf("Failed to allocate space for generic vector.\n");
      exit(1);
    }
  }
  MY_STRING hMyString = my_string_init_default();
  if (hMyString == NULL) {
    printf("Failed to get item at my_string_init_default for hMyString.\n");
    exit(1);
  }
  fp = fopen("dictionary.txt", "r");
  if (fp == NULL) {
    printf("Failed to open dictionary.txt\n");
    exit(1);
  }

  while (my_string_extraction(hMyString, fp)) {
    j = my_string_get_size(hMyString);
    if (j >= 0 && j < MAX_LENGTH)
      generic_vector_push_back(hVector[j - 1], hMyString);
  }
  for (i = 0; i < MAX_LENGTH; i++) {
    for (j = 0; j < generic_vector_get_size(hVector[i]); j++) {
      my_string_insertion((MY_STRING)(*generic_vector_at(hVector[i], j)),
                          stdout);
      printf("\n");
    }
  }
  for (i = 0; i < MAX_LENGTH; i++) {
    generic_vector_destroy(&hVector[i]);
  }
  fclose(fp);
  my_string_destroy(&hMyString);
  return ;
}
#endif
