#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
int main(int argc, char* argv[])
{
    MY_STRING hMy_string = my_string_init_default();
    FILE* fp;
    fp = fopen("simple.txt", "r");
    if(fp == NULL)
    {
        printf("failed to open file ---exiting\n");
        exit(1);
    }
    while (my_string_extraction(hMy_string,fp))
    {
        my_string_insertion(hMy_string,stdout);
        printf("\n");
        if(fgetc(fp) == ' ')
            printf("Found a space after the string\n");
    }
    my_string_destroy(&hMy_string);
    fclose(fp);
    return 0;
}
