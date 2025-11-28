//
// Created by mfuntowicz on 11/25/25.
//

#ifndef SAFETENSORS_FREAD_TABLE_H
#define SAFETENSORS_FREAD_TABLE_H


#include <stdio.h>
#include "safetensors_types.h"

/// Read the tensor table definition from the specified stream
/// @param flags
/// @return
int64_t safetensors_fread_table(safetensors_table_t* table, safetensors_flags_t flags);

#endif //SAFETENSORS_FREAD_TABLE_H