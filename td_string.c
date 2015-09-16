#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "td_string.h"

static const int16_t Magic_Signature =
    0x5444;

typedef struct _td_string_wrapper
{
    size_t length;
    int16_t magic;
} td_string_wrapper;

td_string td_string_create()
{
    size_t allocation_size =
        sizeof(td_string_wrapper) + 1;

    td_string_wrapper *wrapped_string =
        (td_string_wrapper *) malloc(allocation_size);

    assert(wrapped_string);

    wrapped_string->length =
        0;
    wrapped_string->magic =
        Magic_Signature;

    char *string =
        (char *) (wrapped_string) + sizeof(*wrapped_string);
    *string =
        '\0';

    return (td_string) string;
}

td_string td_string_create_with_string(td_string string)
{
    assert(string);

    td_string_wrapper *wrapped_string =
        (td_string_wrapper *) (string - sizeof(*wrapped_string));

    assert(wrapped_string);

    size_t length;
    if (wrapped_string->magic ==
            Magic_Signature) {
        length =
            wrapped_string->length;
    } else {
        length =
            strlen(string);
    }

    size_t allocation_size =
        length + sizeof(td_string_wrapper) + 1;

    assert(allocation_size >= length);

    td_string_wrapper *new_wrapped_string =
        (td_string_wrapper *) malloc(allocation_size);

    assert(new_wrapped_string);

    new_wrapped_string->length =
        length;
    new_wrapped_string->magic =
        Magic_Signature;

    char *new_string =
        (char *) (new_wrapped_string) + sizeof(*new_wrapped_string);

    strncpy(new_string, string, length);
    new_string[length] =
        '\0';

    return (td_string) new_string;
}

void td_string_delete(td_string string)
{
    assert(string);

    td_string_wrapper *wrapped_string =
        (td_string_wrapper *) (string - sizeof(*wrapped_string));

    assert(wrapped_string);

    if (wrapped_string->magic ==
            Magic_Signature) {
        free(wrapped_string);
    }
}

size_t td_string_get_length(td_string string)
{
    assert(string);

    td_string_wrapper *wrapped_string =
        (td_string_wrapper *) (string - sizeof(*wrapped_string));

    assert(wrapped_string);

    size_t length;
    if (wrapped_string->magic ==
            Magic_Signature) {
        length =
            wrapped_string->length;
    } else {
        length =
            strlen(string);
    }

    return length;
}

td_string td_string_combine(td_string string, td_string another_string)
{
    assert(string);
    assert(another_string);

    td_string_wrapper *first_wrapped_string =
        (td_string_wrapper *)
            (string - sizeof(*first_wrapped_string));
    td_string_wrapper *second_wrapped_string =
        (td_string_wrapper *)
            (another_string - sizeof(*second_wrapped_string));

    assert(first_wrapped_string);
    assert(second_wrapped_string);

    size_t first_length;
    if (first_wrapped_string->magic ==
            Magic_Signature) {
        first_length =
            first_wrapped_string->length;
    } else {
        first_length =
            strlen(string);
    }

    size_t second_length;
    if (second_wrapped_string->magic ==
            Magic_Signature) {
        second_length =
            second_wrapped_string->length;
    } else {
        second_length =
            strlen(another_string);
    }

    size_t total_length =
        first_length + second_length;

    assert(total_length >= first_length);

    size_t allocation_size =
        total_length + sizeof(td_string_wrapper) + 1;

    assert(allocation_size >= total_length);

    td_string_wrapper *new_wrapped_string =
        (td_string_wrapper *) malloc(allocation_size);

    assert(new_wrapped_string);

    new_wrapped_string->length =
        total_length;
    new_wrapped_string->magic =
        Magic_Signature;

    char *new_string =
        (char *) (new_wrapped_string) + sizeof(*new_wrapped_string);

    strncpy(new_string, string, first_length);
    strncpy(new_string + first_length, another_string, second_length);

    new_string[total_length] =
        '\0';

    return (td_string) new_string;
}

