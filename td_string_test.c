#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "td_string.h"

void test_td_string_create()
{
    puts("Test we can create an empty string");

    td_string string =
        td_string_create();

    assert(string);
    assert(*string == '\0');

    td_string_delete(string);
}

void test_td_string_create_with_string()
{
    static const char *test_cstring =
        "hello, world";

    puts("Test we can create a string from a C string");

    td_string string =
        td_string_create_with_string(test_cstring);

    assert(string);
    assert(strcmp(string, test_cstring) == 0);

    puts("Test we can create a string from another td_string");

    td_string another_string =
        td_string_create_with_string(string);

    assert(another_string);
    assert(another_string != string);
    assert(strcmp(another_string, string) == 0);

    td_string_delete(string);
    td_string_delete(another_string);
}

void test_td_string_delete()
{
    puts("Test we can deallocate a string");

    td_string string =
        td_string_create();

    assert(string);

    td_string_delete(string);
}

void test_td_string_get_length()
{
    static const char *test_cstring =
        "This is a test string.";
    static const size_t long_cstring_length =
        1024 * 1024 * 128;

    puts("Test we can get the length of an empty string");

    td_string string =
        td_string_create();

    assert(string);

    size_t length =
        td_string_get_length(string);

    assert(length == 0);

    td_string_delete(string);

    puts("Test we can get the length of a string");

    string =
        td_string_create_with_string(test_cstring);

    assert(string);

    length =
        td_string_get_length(string);

    assert(length == strlen(test_cstring));

    td_string_delete(string);

    puts("Test we can get the length of a long string");

    char *long_cstring =
        (char *) malloc(long_cstring_length + 1);

    assert(long_cstring);

    for (size_t i = 0; i < long_cstring_length; ++i) {
        long_cstring[i] =
            'a';
    }
    long_cstring[long_cstring_length] =
        '\0';

    string =
        td_string_create_with_string(long_cstring);

    assert(string);
    assert(string != long_cstring);

    length =
        td_string_get_length(string);

    assert(length == long_cstring_length);

    td_string_delete(string);

    free(long_cstring);
}

void test_td_string_combine()
{
    static const char *test_cstring =
        "hello";
    static const char *tail_cstring =
        ", world";
    static const char *combined_cstring =
        "hello, world";
    static const char *another_tail_cstring =
        " and goodbye";
    static const char *final_combined_cstring =
        "hello and goodbye";

    puts("Test we can concatanate with a C string");

    td_string first_string =
        td_string_create_with_string(test_cstring);

    assert(first_string);
    assert(strcmp(first_string, test_cstring) == 0);

    td_string combined_string =
        td_string_combine(first_string, tail_cstring);

    assert(combined_string);
    assert(strcmp(combined_string, combined_cstring) == 0);

    td_string_delete(combined_string);

    puts("Test we can concatanate with a td_string");

    td_string second_string =
        td_string_create_with_string(another_tail_cstring);

    assert(second_string);
    assert(strcmp(second_string, another_tail_cstring) == 0);

    combined_string =
        td_string_combine(first_string, second_string);

    assert(combined_string);
    assert(strcmp(combined_string, final_combined_cstring) == 0);

    td_string_delete(first_string);
    td_string_delete(second_string);
    td_string_delete(combined_string);
}

void test_td_string()
{
    test_td_string_create();
    test_td_string_create_with_string();
    test_td_string_delete();
    test_td_string_get_length();
    test_td_string_combine();
}

int main(int argc, char **argv)
{
    test_td_string();

    return 0;
}

