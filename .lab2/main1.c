#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
int main(int argc, char* argv[])
{
 MY_STRING hMy_string = NULL;
 hMy_string = my_string_init_default();
 my_string_destroy(&hMy_string);
 return 0;
}
