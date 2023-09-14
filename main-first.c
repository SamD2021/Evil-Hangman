#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
int main(int argc, char* argv[])
{
    MY_STRING hMy_string = my_string_init_default(), hMy_string2 = NULL;

    printf("string1 is (%s), its size is %d and capacity is %d\n", my_string_c_str(hMy_string), my_string_get_size(hMy_string), my_string_get_capacity(hMy_string));
    /* my_string_insertion(hMy_string,stdout); */
    for(int i = 0; i<2; i++)
    {
        my_string_push_back(hMy_string, 'L');
        my_string_push_back(hMy_string, 'O');
        my_string_push_back(hMy_string, 'L');
    }
    printf("String1 %s, its size is %d and capacity is %d\n", my_string_c_str(hMy_string), my_string_get_size(hMy_string), my_string_get_capacity(hMy_string));
    /* my_string_pop_back(hMy_string); */
    /* printf("%s, its size is %d and capacity is %d\n", my_string_c_str(hMy_string), my_string_get_size(hMy_string), my_string_get_capacity(hMy_string)); */
    hMy_string2 = my_string_init_copy(hMy_string);
    printf("String2 is %s, its size is %d and capacity is %d\n", my_string_c_str(hMy_string2), my_string_get_size(hMy_string2), my_string_get_capacity(hMy_string2));
    /* for(int i = 0; i<4; i++) */
    /* { */
        my_string_push_back(hMy_string2, 'H');
        my_string_push_back(hMy_string2, 'E');
    /* } */
    printf("String2 is %s, its size is %d and capacity is %d\n", my_string_c_str(hMy_string2), my_string_get_size(hMy_string2), my_string_get_capacity(hMy_string2));
    my_string_concat(hMy_string,hMy_string2);
    /* if(my_string_assignment(hMy_string, hMy_string2)) */
    /*     printf("Assingment Successful\n"); */
    /* else */
    /*     printf("Assignment Failed\n"); */
    printf("String1 is %s, its size is %d and capacity is %d\n", my_string_c_str(hMy_string), my_string_get_size(hMy_string), my_string_get_capacity(hMy_string));
    printf("String2 is %s, its size is %d and capacity is %d\n", my_string_c_str(hMy_string2), my_string_get_size(hMy_string2), my_string_get_capacity(hMy_string2));
    my_string_swap(hMy_string, hMy_string2);
    printf("\nswapped\n");
    printf("String1 is %s, its size is %d and capacity is %d\n", my_string_c_str(hMy_string), my_string_get_size(hMy_string), my_string_get_capacity(hMy_string));
    printf("String2 is %s, its size is %d and capacity is %d\n", my_string_c_str(hMy_string2), my_string_get_size(hMy_string2), my_string_get_capacity(hMy_string2));
    /* printf("\n"); */
    my_string_destroy(&hMy_string);

    my_string_destroy(&hMy_string2);
    //fclose(fp);
    return 0;
}
