#ifndef TD_STRING
#define TD_STRING

#include <stddef.h>

typedef const char* td_string;

td_string td_string_create();

td_string td_string_create_with_string(td_string string);

void td_string_delete(td_string string);

size_t td_string_get_length(td_string string);

td_string td_string_combine(td_string string, td_string another_string);

#endif

