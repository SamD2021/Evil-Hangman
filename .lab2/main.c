#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
int main(int argc, char* argv[])
{
    MY_STRING hMy_string = NULL, hMy_string2 = NULL;
    //char* word;
    //printf("enter the first word: ");
    //scanf("%s", word);
    hMy_string = my_string_init_c_string("app");
    //printf("enter the second word: ");
    //scanf("%s", word);
    hMy_string2 = my_string_init_c_string("apple");
    printf("the first string has capacity %d and size %d\n\n the second string has capacity %d, and size %d\n", my_string_get_capacity(hMy_string), my_string_get_size(hMy_string), my_string_get_capacity(hMy_string2), my_string_get_size(hMy_string2));
    int comp = my_string_compare(hMy_string, hMy_string2);
    if(comp < 0)
    {
        printf("right string is greater\n");
    }
    else if(comp > 0)
    {
        printf("left string is greater\n");
    }
    else
    {
        printf("strings are equal\n");
    }
    my_string_destroy(&hMy_string);
    my_string_destroy(&hMy_string2);

    return 0;
}
