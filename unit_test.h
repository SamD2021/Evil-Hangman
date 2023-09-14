#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"
Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_sdasilva_get_capacity_on_init_default_returns_7(char *buffer, int length);
Status test_sdasilva_handle_in_my_string_destroy_is_NULL_when_done(char *buffer, int length);
Status test_sdasilva_init_c_string_has_one_plus_capacity(char *buffer, int length);
Status test_sdasilva_compare_app_is_less_than_apple(char *buffer, int length);
Status test_sdasilva_compare_same_string_returns_0(char *buffer, int length);
Status test_sdasilva_compare_larger_string_returns_greater_than_0(char *buffer, int length);
Status test_sdasilva_extraction_ignores_leading_whitespace(char *buffer, int length);
Status test_sdasilva_extraction_stops_after_whitespace_after_non_whitespace(char *buffer, int length);
Status test_sdasilva_extraction_adds_all_characters_until_a_stop_case(char *buffer, int length);
Status test_sdasilva_extraction_stops_with_EOF(char *buffer, int length);
Status test_sdasilva_insertion_writes_characters_from_hMy_string_to_file_stream(char *buffer, int length);
Status test_sdasilva_push_back_returns_SUCCESS(char *buffer, int length);
Status test_sdasilva_push_back_returns_new_capacity_from_resize(char *buffer, int length);
Status test_sdasilva_pop_back_returns_failure_when_string_empty(char *buffer, int length);
Status test_sdasilva_pop_back_returns_success_when_size_is_decremented(char *buffer, int length);
Status test_sdasilva_pop_back_removes_last_character(char *buffer, int length);
Status test_sdasilva_string_at_returns_NULL_if_out_of_bounds(char *buffer, int length);
Status test_sdasilva_string_at_returns_address_of_character_at_index(char *buffer, int length);
Status test_sdasilva_c_str_returns_address_of_string_object_as_c_string(char *buffer, int length);
Status test_sdasilva_c_str_size_excludes_NULL_terminator(char *buffer, int length);
Status test_sdasilva_concat_returns_success_on_success(char *buffer, int length);
/* Status test_sdasilva_concat_returns_failure_if_unable_to_accomodate_characters(char *buffer, int length); */
Status test_sdasilva_empty_returns_true_if_string_empty(char *buffer, int length);
Status test_sdasilva_empty_returns_false_if_string_not_empty(char *buffer, int length);
#endif
