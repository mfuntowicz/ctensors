#ifndef SAFETENSORS_FOPEN_H
#define SAFETENSORS_FOPEN_H

#include "safetensors_types.h"

/// Open the specified file for reading
int64_t safetensors_fopen(const char* path, safetensors_table_t* table, safetensors_flags_t flags);

#endif // SAFETENSORS_FOPEN_H
