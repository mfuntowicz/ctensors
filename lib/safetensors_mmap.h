#ifndef SAFETENSORS_MMAP_H
#define SAFETENSORS_MMAP_H
#include <stdint.h>

#include "safetensors_types.h"

int64_t safetensors_mmap(const char* path, safetensors_table_t* table, safetensors_flags_t flags);

#endif // SAFETENSORS_MMAP_H
