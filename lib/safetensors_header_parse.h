//
// Created by mfuntowicz on 11/25/25.
//

#ifndef SAFETENSORS_FREAD_HEADER_H
#define SAFETENSORS_FREAD_HEADER_H

#include <stddef.h>

#include "safetensors_types.h"

typedef enum
{
    safetensors_header_invalid_starting_char = -1,
    safetensors_header_invalid_ending_char = -2,
    safetensors_headers_alloc_failed = -3,
    safetensors_headers_number_parsing_failed = -4
} safetensors_fread_header_error_t;

/// Parse the JSON header, handling the definition of all the tensors within the safetensors
/// @param table The table to populate with the tensor definitions
/// @param header The JSON header to parse
/// @param hsize The number of chars in the header
/// @param flags Flags to control the actual reading
/// @return Number of tensors discovered or error if < 0
struct safetensors_status safetensors_header_parse(
    struct safetensors_table* table, const char* header, size_t hsize, enum safetensors_flags flags);

#endif //SAFETENSORS_FREAD_HEADER_H