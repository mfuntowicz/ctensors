//
// Created by mfuntowicz on 11/25/25.
//

#ifndef CTENSORS_CTENSORS_FREAD_HEADER_H
#define CTENSORS_CTENSORS_FREAD_HEADER_H

#include <stddef.h>

#include "ctensors_types.h"

typedef enum
{
    ctensors_header_invalid_starting_char = -1,
    ctensors_header_invalid_ending_char = -2,
    ctensors_headers_alloc_failed = -3,
    ctensors_headers_number_parsing_failed = -4
} ctensors_fread_header_error_t;

/// Parse the JSON header, handling the definition of all the tensors within the safetensors
/// @param table The table to populate with the tensor definitions
/// @param header The JSON header to parse
/// @param hsize The number of chars in the header
/// @param flags Flags to control the actual reading
/// @return Number of tensors discovered or error if < 0
int32_t ctensors_header_parse(ctensors_table_t* table, const char* header, size_t hsize, ctensors_flags_t flags);

#endif //CTENSORS_CTENSORS_FREAD_HEADER_H