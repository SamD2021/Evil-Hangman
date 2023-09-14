#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
int main(int argc, char* argv[])
{
    MY_STRING hMy_string = my_string_init_default();
    FILE* fp;
    int n = 5;
    fp = fopen("dictionary.txt", "r");
    if(fp == NULL)
    {
        printf("failed to open dictionary.txt ---exiting\n");
        exit(1);
    }
    while (my_string_extraction(hMy_string,fp))
    {
        if(my_string_get_size(hMy_string) == n)
        {
            my_string_insertion(hMy_string,stdout);
            printf("\n");
        }
    }
    my_string_destroy(&hMy_string);
    fclose(fp);
    return 0;
}
