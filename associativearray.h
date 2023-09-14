#ifndef ASSOCIATIVEARRAY_H
#define ASSOCIATIVEARRAY_H
#include "generic_vector.h"
#include "status.h"
#include "my_string.h"

typedef void* ASSOCIATIVE_ARR;


ASSOCIATIVE_ARR associray_init_default(void);
void associray_insert(ASSOCIATIVE_ARR hArr, MY_STRING hWords, MY_STRING hKey);
void associray_destroy(ASSOCIATIVE_ARR* phArr);
void associray_print(ASSOCIATIVE_ARR hArr);
void associray_inorder(ASSOCIATIVE_ARR hArr);
Status associray_remove(ASSOCIATIVE_ARR hArr, MY_STRING hKey);
GENERIC_VECTOR associray_search(ASSOCIATIVE_ARR hArr, MY_STRING hKey);
GENERIC_VECTOR associray_init_find_max(ASSOCIATIVE_ARR hArr, Boolean ShowCheats);
#endif // ASSOCIATIVEARRAY_H
