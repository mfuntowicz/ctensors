#ifndef CTENSORS_FOPEN_H
#define CTENSORS_FOPEN_H

#include "ctensors_types.h"

/// Open the specified file for reading
int64_t ctensors_fopen(const char* path, ctensors_table_t* table, ctensors_flags_t flags);

#endif // CTENSORS_FOPEN_H
