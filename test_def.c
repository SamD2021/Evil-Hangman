#include "status.h"
#include "unit_test.h"
#include <stdio.h>
#include <stdlib.h>

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
    MY_STRING hString = NULL;
    hString = my_string_init_default();
    if (hString == NULL)
    {
        strncpy(buffer, "test_init_default_returns_nonNULL\n"
                        "my_string_init_default returns NULL",
                length);
        return FAILURE;
    }
    else
    {
        my_string_destroy(&hString);
        strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
        return SUCCESS;
    }
}

Status test_get_size_on_init_default_returns_0(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;
    hString = my_string_init_default();
    if (my_string_get_size(hString) != 0)
    {
        status = FAILURE;
        printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
        strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
                        "Did not receive 0 from get_size after init_default\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
    }
    my_string_destroy(&hString);
    return status;
}

Status test_sdasilva_get_capacity_on_init_default_returns_7(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;
    hString = my_string_init_default();
    if (my_string_get_capacity(hString) != 7)
    {
        status = FAILURE;
        printf("Expected a capacity of 7 but got %d\n", my_string_get_capacity(hString));
        strncpy(buffer, "test_sdasilva_get_capacity_on_init_default_returns_7\n"
                        "Did not receive 7 from get_capacity after init_default\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_get_capacity_on_init_default_returns_7\n",length);
    }
    my_string_destroy(&hString);
    return status;
}

// Destroy function
Status test_sdasilva_handle_in_my_string_destroy_is_NULL_when_done(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;
    hString = my_string_init_default();

    my_string_destroy(&hString);
    if (hString != NULL) {
      status = FAILURE;
      printf("Expected hString to be NULL but got %p\n",
             hString);
      strncpy(buffer,
              "test_sdasilva_handle_in_my_string_destroy_is_NULL_when_done\n"
              "The handle hString is not set to NULL after the function is called\n",
              length);
    } else {
      status = SUCCESS;
      strncpy(buffer, "test_sdasilva_handle_in_my_string_destroy_is_NULL_when_done\n",
              length);
    }
    return status;
}
// C_string
Status test_sdasilva_init_c_string_has_one_plus_capacity(char *buffer, int length)
{
    MY_STRING hString = NULL;
    Status status;
    hString = my_string_init_c_string("Banana");
    if (my_string_get_capacity(hString) != sizeof("Banana"))
    {
        status = FAILURE;
        printf("Expected a capacity of 7 but got %d\n", my_string_get_capacity(hString));
        strncpy(buffer, "test_sdasilva_init_c_string_has_one_plus_capacity\n"
                        "Did not receive 7 from get_capacity after initializing hString with banana\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_init_c_string_has_one_plus_capacity\n",length);
    }
    my_string_destroy(&hString);
    return status;
}
// compare function
Status test_sdasilva_compare_app_is_less_than_apple(char *buffer, int length){
    MY_STRING hStringA = NULL, hStringB = NULL;
    Status status;
    hStringA = my_string_init_c_string("app");
    hStringB = my_string_init_c_string("apple");
    if (my_string_compare(hStringA, hStringB) >= 0)
    {
        status = FAILURE;
        printf("Expected result to be less than 0 but got %d\n", my_string_compare(hStringA, hStringB));
        strncpy(buffer, "test_sdasilva_compare_app_is_less_than_apple\n"
                        "Did not receive less than 0 from string compare after initializing hStringA with app and hStringB with apple\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_compare_app_is_less_than_apple\n",length);
    }
    my_string_destroy(&hStringA);
    my_string_destroy(&hStringB);
    return status;
}

Status test_sdasilva_compare_same_string_returns_0(char *buffer, int length){
    MY_STRING hStringA = NULL, hStringB = NULL;
    Status status;
    hStringA = my_string_init_c_string("banana");
    hStringB = my_string_init_c_string("banana");
    if (my_string_compare(hStringA, hStringB) != 0)
    {
        status = FAILURE;
        printf("Expected result to be 0 but got %d\n", my_string_compare(hStringA, hStringB));
        strncpy(buffer, "test_sdasilva_compare_same_string_returns_0\n"
                        "Did not receive 0 from string compare after initializing hStringA and hStringB with banana\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_compare_same_string_returns_0\n",length);
    }
    my_string_destroy(&hStringA);
    my_string_destroy(&hStringB);
    return status;
}

Status test_sdasilva_compare_larger_string_returns_greater_than_0(char *buffer, int length){
    MY_STRING hStringA = NULL, hStringB = NULL;
    Status status;
    hStringA = my_string_init_c_string("bananal");
    hStringB = my_string_init_c_string("banana");
    if (my_string_compare(hStringA, hStringB) <= 0)
    {
        status = FAILURE;
        printf("Expected result to be greater than 0 but got %d\n", my_string_compare(hStringA, hStringB));
        strncpy(buffer, "test_sdasilva_compare_larger_string_returns_greater_than_0\n"
                        "Did not receive greater than 0 from string compare after initializing hStringA with bananal and hStringB with banana\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_compare_larger_string_returns_greater_than_0\n",length);
    }
    my_string_destroy(&hStringA);
    my_string_destroy(&hStringB);
    return status;
}

Status test_sdasilva_extraction_ignores_leading_whitespace(char *buffer, int length){
    MY_STRING hStringA = NULL, hStringB = NULL;
    Status status;
    /* char tstring[ ]; */
    FILE* fp = NULL;
    fp = fopen("extraction_case_1.txt", "w");
    if(fp == NULL) {
        status = FAILURE;
        printf("Expected result to be some address but got %p\n",
               fp);
        strncpy(buffer,
                "test_sdasilva_extraction_ignores_leading_whitespace\n"
                "fp is NULL after fopen",
                length);
        return status;
    }
    /* fputc(' ', fp); */
    /* fputc('w', fp); */
    /* fputc('a', fp); */
    /* fputc('t', fp); */
    /* fputc('e', fp); */
    /* fputc('r', fp); */
    fprintf(fp, " water");
    fclose(fp);
    fp = fopen("extraction_case_1.txt", "r");
    hStringA = my_string_init_default();
    hStringB = my_string_init_default();
    my_string_push_back(hStringB, 'w');
    my_string_push_back(hStringB, 'a');
    my_string_push_back(hStringB, 't');
    my_string_push_back(hStringB, 'e');
    my_string_push_back(hStringB, 'r');
    my_string_extraction(hStringA, fp);
    /*     printf("Success\n"); */
    /* else { */
    /*     printf("Failed\n"); */
    /* } */

    /* if(my_string_insertion(hStringA, stdout)) */
    /*     printf("Success\n"); */
    /* else { */
    /*     printf("Failed\n"); */
    /* } */
    if (my_string_compare(hStringA, hStringB) != 0)
    {
        status = FAILURE;
        printf("Expected result to be 0 but got %d\n", my_string_compare(hStringA, hStringB));
        strncpy(buffer, "test_sdasilva_extraction_ignores_leading_whitespace\n"
                        "Did not receive 0 from string compare after initializing fp with ' water' then extracting it to hStringA and hStringB with 'water'\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_extraction_ignores_leading_whitespace\n",length);
    }
    fclose(fp);
    remove("extraction_case_1.txt");
    my_string_destroy(&hStringA);
    my_string_destroy(&hStringB);
    return status;
}

Status test_sdasilva_extraction_stops_after_whitespace_after_non_whitespace(char *buffer, int length){
    MY_STRING hStringA = NULL, hStringB = NULL;
    Status status;
    /* char tstring[ ]; */
    FILE* fp = NULL;
    fp = fopen("extraction_case_1.txt", "w");
    if(fp == NULL) {
        status = FAILURE;
        printf("Expected result to be some address but got %p\n",
               fp);
        strncpy(buffer,
                "test_sdasilva_extraction_ignores_leading_whitespace\n"
                "fp is NULL after fopen",
                length);
        return status;
    }
    /* fputc(' ', fp); */
    /* fputc('w', fp); */
    /* fputc('a', fp); */
    /* fputc('t', fp); */
    /* fputc('e', fp); */
    /* fputc('r', fp); */
    fprintf(fp, "water dog");
    fclose(fp);
    fp = fopen("extraction_case_1.txt", "r");
    hStringA = my_string_init_default();
    hStringB = my_string_init_default();
    my_string_push_back(hStringB, 'w');
    my_string_push_back(hStringB, 'a');
    my_string_push_back(hStringB, 't');
    my_string_push_back(hStringB, 'e');
    my_string_push_back(hStringB, 'r');
    my_string_extraction(hStringA, fp);
    /*     printf("Success\n"); */
    /* else { */
    /*     printf("Failed\n"); */
    /* } */

    /* if(my_string_insertion(hStringA, stdout)) */
    /*     printf("Success\n"); */
    /* else { */
    /*     printf("Failed\n"); */
    /* } */
    if (my_string_compare(hStringA, hStringB) != 0)
    {
        status = FAILURE;
        printf("Expected result to be 0 but got %d\n", my_string_compare(hStringA, hStringB));
        strncpy(buffer, "test_sdasilva_extraction_stops_after_whitespace_after_non_whitespace\n"
                        "Did not receive 0 from string compare after initializing fp with 'water dog' and extracting it to hStringA and hStringB with 'water'\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_extraction_stops_after_whitespace_after_non_whitespace\n",length);
    }
    fclose(fp);
    remove("extraction_case_1.txt");
    my_string_destroy(&hStringA);
    my_string_destroy(&hStringB);
    return status;
}

Status test_sdasilva_extraction_adds_all_characters_until_a_stop_case(char *buffer, int length){
    MY_STRING hStringA = NULL, hStringB = NULL;
    Status status;
    /* char tstring[ ]; */
    FILE* fp = NULL;
    fp = fopen("extraction_case_1.txt", "w");
    if(fp == NULL) {
        status = FAILURE;
        printf("Expected result to be some address but got %p\n",
               fp);
        strncpy(buffer,
                "test_sdasilva_extraction_adds_all_characters_until_a_stop_case\n"
                "fp is NULL after fopen",
                length);
        return status;
    }
    /* fputc(' ', fp); */
    /* fputc('w', fp); */
    /* fputc('a', fp); */
    /* fputc('t', fp); */
    /* fputc('e', fp); */
    /* fputc('r', fp); */
    fprintf(fp, "water");
    fclose(fp);
    fp = fopen("extraction_case_1.txt", "r");
    hStringA = my_string_init_default();
    hStringB = my_string_init_default();
    my_string_push_back(hStringB, 'w');
    my_string_push_back(hStringB, 'a');
    my_string_push_back(hStringB, 't');
    my_string_push_back(hStringB, 'e');
    my_string_push_back(hStringB, 'r');
    my_string_extraction(hStringA, fp);
    /*     printf("Success\n"); */
    /* else { */
    /*     printf("Failed\n"); */
    /* } */

    /* if(my_string_insertion(hStringA, stdout)) */
    /*     printf("Success\n"); */
    /* else { */
    /*     printf("Failed\n"); */
    /* } */
    if (my_string_compare(hStringA, hStringB) != 0)
    {
        status = FAILURE;
        printf("Expected result to be 0 but got %d\n", my_string_compare(hStringA, hStringB));
        strncpy(buffer, "test_sdasilva_extraction_adds_all_characters_until_a_stop_case\n"
                        "Did not receive 0 from string compare after initializing fp with 'water\0' and extracting it to hStringA and hStringB with 'water'\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_extraction_adds_all_characters_until_a_stop_case\n",length);
    }
    fclose(fp);
    remove("extraction_case_1.txt");
    my_string_destroy(&hStringA);
    my_string_destroy(&hStringB);
    return status;
}

Status test_sdasilva_extraction_stops_with_EOF(char *buffer, int length){
    MY_STRING hStringA = NULL, hStringB = NULL;
    Status status;
    /* char tstring[ ]; */
    FILE* fp = NULL;
    fp = fopen("extraction_case_1.txt", "w");
    if(fp == NULL) {
        status = FAILURE;
        printf("Expected result to be some address but got %p\n",
               fp);
        strncpy(buffer,
                "test_sdasilva_extraction_stops_with_EOF\n"
                "fp is NULL after fopen",
                length);
        return status;
    }
    /* fputc(' ', fp); */
    fputc('w', fp);
    fputc('a', fp);
    fputc('t', fp);
    fputc('e', fp);
    fputc('r', fp);
    /* fprintf(fp, "water"); */
    fclose(fp);
    fp = fopen("extraction_case_1.txt", "r");
    hStringA = my_string_init_default();
    hStringB = my_string_init_default();
    my_string_push_back(hStringB, 'w');
    my_string_push_back(hStringB, 'a');
    my_string_push_back(hStringB, 't');
    my_string_push_back(hStringB, 'e');
    my_string_push_back(hStringB, 'r');
    my_string_extraction(hStringA, fp);
    /*     printf("Success\n"); */
    /* else { */
    /*     printf("Failed\n"); */
    /* } */

    /* if(my_string_insertion(hStringA, stdout)) */
    /*     printf("Success\n"); */
    /* else { */
    /*     printf("Failed\n"); */
    /* } */
    if (my_string_compare(hStringA, hStringB) != 0)
    {
        status = FAILURE;
        printf("Expected result to be 0 but got %d\n", my_string_compare(hStringA, hStringB));
        strncpy(buffer, "test_sdasilva_extraction_stops_with_EOF\n"
                        "Did not receive 0 from string compare after initializing fp with 'water' characters individually and extracting it to hStringA and hStringB with 'water'\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_extraction_stops_with_EOF\n",length);
    }
    fclose(fp);
    remove("extraction_case_1.txt");
    my_string_destroy(&hStringA);
    my_string_destroy(&hStringB);
    return status;
}

// insertion
Status test_sdasilva_insertion_writes_characters_from_hMy_string_to_file_stream(char *buffer, int length){
    MY_STRING hStringA = NULL, hStringB = NULL;
    Status status;
    FILE* fp = NULL;
    fp = fopen("insertion_case_1.txt", "w");
    if(fp == NULL) {
        status = FAILURE;
        printf("Expected result to be some address but got %p\n",
               fp);
        strncpy(buffer,
                "test_sdasilva_insertion_writes_characters_from_hMy_string_to_file_stream\n"
                "fp is NULL after fopen",
                length);
        return status;
    }
    hStringA = my_string_init_default();
    hStringB = my_string_init_default();
    my_string_push_back(hStringB, 'w');
    my_string_push_back(hStringB, 'a');
    my_string_push_back(hStringB, 't');
    my_string_push_back(hStringB, 'e');
    my_string_push_back(hStringB, 'r');
    my_string_insertion(hStringB, fp);
    fclose(fp);
    fp = fopen("insertion_case_1.txt", "r");
    if (fp == NULL) {
        status = FAILURE;
        printf("Expected result to be some address but got %p\n", fp);
        strncpy(buffer,
                "test_sdasilva_insertion_writes_characters_from_hMy_string_to_file_stream\n"
                "fp is NULL after fopen",
                length);
        return status;
    }
    my_string_extraction(hStringA, fp);
    if (my_string_compare(hStringA, hStringB) != 0)
    {
        status = FAILURE;
        printf("Expected result to be 0 but got %d\n", my_string_compare(hStringA, hStringB));
        strncpy(buffer, "test_sdasilva_insertion_writes_characters_from_hMy_string_to_file_stream\n"
                        "Did not receive 0 from string compare after initializing fp with 'water' characters from insertion from hStringB with 'water'\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_insertion_writes_characters_from_hMy_string_to_file_stream\n",length);
    }
    fclose(fp);
    remove("insertion_case_1.txt");
    my_string_destroy(&hStringA);
    my_string_destroy(&hStringB);
    return status;
}

// push_back

Status test_sdasilva_push_back_returns_SUCCESS(char *buffer, int length){
    MY_STRING hStringA = NULL, hStringB = NULL;
    Status status;
    hStringA = my_string_init_default();
    if (!my_string_push_back(hStringA, 'w'))
    {
        status = FAILURE;
        printf("Expected result to be SUCCESS but got FAILURE\n");
        strncpy(buffer, "test_sdasilva_insertion_writes_characters_from_hMy_string_to_file_stream\n"
                        "Did not receive 0 from string compare after initializing fp with 'water' characters from insertion from hStringB with 'water'\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_insertion_writes_characters_from_hMy_string_to_file_stream\n",length);
    }
    my_string_destroy(&hStringA);
    return status;
}

Status test_sdasilva_push_back_returns_new_capacity_from_resize(char *buffer, int length){
    MY_STRING hStringA = NULL;
    int before;
    Status status;
    hStringA = my_string_init_default();
    before = my_string_get_capacity(hStringA);
    for(int i = 0; i < 10; i++){
        my_string_push_back(hStringA, 'w');
    }
    if (my_string_get_capacity(hStringA) == before)
    {
        status = FAILURE;
        printf("Expected capacity to be different than before but got the same\n");
        strncpy(buffer, "test_sdasilva_push_back_returns_new_capacity_from_resize\n"
                        "Did not receive diffrent capacity after 10 push backs\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_push_back_returns_new_capacity_from_resize\n",length);
    }
    my_string_destroy(&hStringA);
    return status;
}
//pop_back
Status test_sdasilva_pop_back_returns_failure_when_string_empty(char *buffer, int length){
    MY_STRING hStringA = NULL, hStringB = NULL;
    int before, after;
    Status status;
    hStringA = my_string_init_default();
    if (my_string_pop_back(hStringA))
    {
        status = FAILURE;
        printf("Expected pop back to fail when empty but returned success\n");
        strncpy(buffer, "test_sdasilva_pop_back_returns_failure_when_string_empty\n"
                        "Did not receive failure when hString was assigned my_string_init_default that has size 0\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_pop_back_returns_failure_when_string_empty\n",length);
    }
    my_string_destroy(&hStringA);
    return status;
}

Status test_sdasilva_pop_back_returns_success_when_size_is_decremented(char *buffer, int length){
    MY_STRING hString = NULL;
    int before, after;
    Status status, result;
    hString = my_string_init_default();
    my_string_push_back(hString, 'w');
    before = my_string_get_size(hString);
    result = my_string_pop_back(hString);
    after = my_string_get_size(hString);
    if (!result || after != before-1)
    {
        status = FAILURE;
        printf("Expected pop back to return success when size is decremented but returned failure when size was decremented or didnt decrement one from size\n");
        strncpy(buffer, "test_sdasilva_pop_back_returns_success_when_size_is_decremented\n"
                        "Did not receive failure when hString was assigned my_string_init_default that has size 0\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_pop_back_returns_success_when_size_is_decremented\n",length);
    }
    my_string_destroy(&hString);
    return status;
}

Status test_sdasilva_pop_back_removes_last_character(char *buffer, int length){
    MY_STRING hString = NULL, hString2 = NULL;
    int before, after;
    Status status, result;
    hString = my_string_init_c_string("foo");
    hString2 = my_string_init_c_string("foo");
    my_string_pop_back(hString2);
    if (!my_string_compare(hString, hString2))
    {
        status = FAILURE;
        printf("Expected pop back to remove last character but when compared returned it was the same as before\n");
        strncpy(buffer, "test_sdasilva_pop_back_removes_last_character\n"
                        "Did not remove last character after pop back when two strings are init_c_string with 'foo' then pop back is called\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_pop_back_removes_last_character\n",length);
    }
    my_string_destroy(&hString);
    my_string_destroy(&hString2);
    return status;
}

Status test_sdasilva_string_at_returns_NULL_if_out_of_bounds(char *buffer, int length){
    MY_STRING hString = NULL;
    int before, after;
    Status status;
    hString = my_string_init_c_string("foo");

    if (my_string_at(hString, 4) != NULL)
    {
        status = FAILURE;
        printf("Expected string_at to return NULL when index is out of bounds but returned otherwise\n");
        strncpy(buffer, "test_sdasilva_string_at_returns_NULL_if_out_of_bounds\n"
                        "Did not receive NULL when hString was assigned my_string_init_c_string with 'foo' when index was 4\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_string_at_returns_NULL_if_out_of_bounds\n",length);
    }
    my_string_destroy(&hString);
    return status;
}

Status test_sdasilva_string_at_returns_address_of_character_at_index(char *buffer, int length){
    MY_STRING hString = NULL;
    int before, after;
    Status status;
    hString = my_string_init_c_string("foo");
    char* pC = my_string_at(hString, 2);
    if (pC == NULL)
    {
        status = FAILURE;
        printf("Expected pop back to return an address of a character at index but received NULL\n");
        strncpy(buffer, "test_sdasilva_string_at_returns_address_of_character_at_index\n"
                        "Did not receive an address of a character at index when hString was assigned my_string_init_c_string with 'foo' when index was 2\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_string_at_returns_address_of_character_at_index\n",length);
    }
    my_string_destroy(&hString);
    return status;
}
/*C_STR*/
Status test_sdasilva_c_str_returns_address_of_string_object_as_c_string(char *buffer, int length) {
  MY_STRING hString = NULL;
  char *s;
  Status status;
  Boolean result;
  hString = my_string_init_c_string("foo");
  s = my_string_c_str(hString);
  if (s != NULL && s[my_string_get_size(hString)] == '\0')
    result = TRUE;
  else
    result = FALSE;
  if (result == FALSE) {
    status = FAILURE;
    printf("Expected c_str to return an address of a c string but "
           "didn't have a null terminator\n");
    strncpy(
        buffer,
        "test_sdasilva_c_str_returns_address_of_string_object_as_c_string\n"
        "Did not receive an address of a null terminated character after hString was "
        "assigned my_string_init_c_string with 'foo' and passed to c_str\n",
        length);
  } else {
    status = SUCCESS;
    strncpy(
        buffer,
        "test_sdasilva_c_str_returns_address_of_string_object_as_c_string\n",
        length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_sdasilva_c_str_size_excludes_NULL_terminator(char *buffer, int length){
    MY_STRING hString = NULL;
    int before, after;
    char* s;
    Status status;
    hString = my_string_init_c_string("foo");
    before = my_string_get_size(hString);
    s = my_string_c_str(hString);
    after = my_string_get_size(hString);
    if (before != after)
    {
        status = FAILURE;
        printf("Expected c_str to retain its size of %d but received %d\n", before, after);
        strncpy(buffer, "test_sdasilva_c_str_size_excludes_NULL_terminator\n"
                        "Did not the exclude null terminator from size when hString was assigned my_string_init_c_string with 'foo' and passed to c_str since before != after\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_c_str_size_excludes_NULL_terminator\n",length);
    }
    my_string_destroy(&hString);
    return status;
}

/*concat*/
Status test_sdasilva_concat_returns_success_on_success(char *buffer, int length){
    MY_STRING hString = NULL, hString2 = NULL;
    int before, after;
    Status status;
    hString = my_string_init_c_string("foo");
    hString2 = my_string_init_c_string("!");
    if (my_string_concat(hString, hString2) == FAILURE)
    {
        status = FAILURE;
        printf("Expected concat to return SUCCESS but received FAILURE\n");
        strncpy(buffer, "test_sdasilva_concat_returns_success_on_success\n"
                        "Did not receive SUCESS when concat was called after hString was assigned my_string_init_c_string with 'foo' and hString2 with '!'\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_concat_returns_success_on_success\n",length);
    }
    my_string_destroy(&hString);
    my_string_destroy(&hString2);
    return status;
}
/* // TODO */
/* Status test_sdasilva_concat_returns_failure_if_unable_to_accomodate_characters(char *buffer, int length){ */
/*     MY_STRING hString = NULL, hString2 = NULL; */
/*     int before, after; */
/*     Status status; */
/*     hString = my_string_init_c_string("foo"); */
/*     hString2 = my_string_init_default(); */

/*     if (my_string_concat(hString, hString2) != FAILURE) */
/*     { */
/*         status = FAILURE; */
/*         printf("Expected pop back to return an address of a character at index but received NULL\n"); */
/*         strncpy(buffer, "test_sdasilva_string_at_returns_address_of_character_at_index\n" */
/*                         "Did not receive an address of a character at index when hString was assigned my_string_init_c_string with 'foo' when index was 2\n", */
/*                 length); */
/*     } */
/*     else */
/*     { */
/*         status = SUCCESS; */
/*         strncpy(buffer, "test_sdasilva_string_at_returns_address_of_character_at_index\n",length); */
/*     } */
/*     my_string_destroy(&hString); */
/*     return status; */
/* } */
/*string empty*/
Status test_sdasilva_empty_returns_true_if_string_empty(char *buffer, int length){
    MY_STRING hString = NULL;
    int before, after;
    Status status;
    hString = my_string_init_default();
    if (my_string_empty(hString) == FALSE)
    {
        status = FAILURE;
        printf("Expected string_empty to return TRUE if string is empty but received FALSE\n");
        strncpy(buffer, "test_sdasilva_empty_returns_false_if_string_not_empty\n"
                        "Did not receive a TRUE from string_empty when hString was assigned my_string_init_default\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_empty_returns_false_if_string_not_empty\n",length);
    }
    my_string_destroy(&hString);
    return status;
}

Status test_sdasilva_empty_returns_false_if_string_not_empty(char *buffer, int length){
    MY_STRING hString = NULL;
    int before, after;
    Status status;
    hString = my_string_init_c_string("foo");

    if (my_string_empty(hString) == TRUE)
    {
        status = FAILURE;
        printf("Expected string_empty to return false if string not empty but received TRUE\n");
        strncpy(buffer, "test_sdasilva_empty_returns_false_if_string_not_empty\n"
                        "Did not receive a FALSE from string_empty when hString was assigned my_string_init_c_string with 'foo'\n",
                length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer, "test_sdasilva_empty_returns_false_if_string_not_empty\n",length);
    }
    my_string_destroy(&hString);
    return status;
}
