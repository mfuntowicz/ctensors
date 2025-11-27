//
// Created by mfuntowicz on 11/25/25.
//

#ifndef CTENSORS_CTENSORS_READ_TABLE_H
#define CTENSORS_CTENSORS_READ_TABLE_H


#include <stdio.h>
#include "ctensors_types.h"

/// Read the tensor table definition from the specified stream
/// @param flags
/// @return
int64_t ctensors_fread_table(ctensors_table_t* table, ctensors_flags_t flags);

#endif //CTENSORS_CTENSORS_READ_TABLE_H