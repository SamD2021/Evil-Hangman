#include <stdio.h>
#include "unit_test.h"
int main(int argc, char *argv[])
{
    Status (*tests[])(char *, int) = {
            test_init_default_returns_nonNULL,
            test_get_size_on_init_default_returns_0,
            test_sdasilva_get_capacity_on_init_default_returns_7,
            test_sdasilva_handle_in_my_string_destroy_is_NULL_when_done,
            test_sdasilva_init_c_string_has_one_plus_capacity,
            test_sdasilva_compare_app_is_less_than_apple,
            test_sdasilva_compare_same_string_returns_0,
            test_sdasilva_compare_larger_string_returns_greater_than_0,
            test_sdasilva_extraction_ignores_leading_whitespace,
            test_sdasilva_extraction_stops_after_whitespace_after_non_whitespace,
            test_sdasilva_extraction_adds_all_characters_until_a_stop_case,
            test_sdasilva_extraction_stops_with_EOF,
            test_sdasilva_insertion_writes_characters_from_hMy_string_to_file_stream,
            test_sdasilva_push_back_returns_SUCCESS,
            test_sdasilva_push_back_returns_new_capacity_from_resize,
            test_sdasilva_pop_back_returns_failure_when_string_empty,
            test_sdasilva_pop_back_returns_success_when_size_is_decremented,
            test_sdasilva_pop_back_removes_last_character,
            test_sdasilva_string_at_returns_NULL_if_out_of_bounds,
            test_sdasilva_string_at_returns_address_of_character_at_index,
            test_sdasilva_c_str_returns_address_of_string_object_as_c_string,
            test_sdasilva_c_str_size_excludes_NULL_terminator,
            test_sdasilva_concat_returns_success_on_success,
            /* test_sdasilva_concat_returns_failure_if_unable_to_accomodate_characters, */
            test_sdasilva_empty_returns_true_if_string_empty,
            test_sdasilva_empty_returns_false_if_string_not_empty
};
    int number_of_functions = sizeof(tests) / sizeof(tests[0]);
    int i;
    char buffer[500];
    int success_count = 0;
    int failure_count = 0;
    for (i = 0; i < number_of_functions; i++)
    {
        if (tests[i](buffer, 500) == FAILURE)
        {
            printf("FAILED: Test %d failed miserably\n", i);
            printf("\t%s\n", buffer);
            failure_count++;
        }
        else
        {
            // printf("PASS: Test %d passed\n", i);
            // printf("\t%s\n", buffer);
            success_count++;
        }
    }
    printf("Total number of tests: %d\n", number_of_functions);
    printf("%d/%d Pass, %d/%d Failure\n", success_count,
           number_of_functions, failure_count, number_of_functions);
    return 0;
}
