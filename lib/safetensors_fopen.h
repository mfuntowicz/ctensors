#ifndef SAFETENSORS_FOPEN_H
#define SAFETENSORS_FOPEN_H

#include "safetensors_types.h"

/// Open the specified file for reading
int64_t safetensors_fopen(const char* path, safetensors_table* table, safetensors_flags flags);

#endif // SAFETENSORS_FOPEN_H
