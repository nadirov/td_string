#include <stdio.h>
#include <stddef.h>

#include "td_string.h"

int main(int argc, char **argv)
{
    td_string message =
        td_string_create_with_string("hello, world");

    printf("The message is '%s'.\n", message);

    size_t message_length =
        td_string_get_length(message);

    printf("The length of the message is %zu.\n", message_length);

    td_string another_message =
        td_string_create_with_string(". bye.");

    td_string combined_messages =
        td_string_combine(message, another_message);

    td_string_delete(message);
    td_string_delete(another_message);

    printf("The final message is '%s'.\n", combined_messages);

    size_t combined_message_length =
        td_string_get_length(combined_messages);

    printf("The length of the final message is %zu.\n", combined_message_length);

    td_string_delete(combined_messages);

    return 0;
}

