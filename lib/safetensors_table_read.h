#ifndef SAFETENSORS_TABLE_READ_H
#define SAFETENSORS_TABLE_READ_H
#include <stddef.h>

#include "safetensors_types.h"

int32_t safetensors_table_read(safetensors_table_t* table, const char* header, size_t size, safetensors_flags_t flags);

#endif // SAFETENSORS_TABLE_READ_H
