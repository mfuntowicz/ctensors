#ifndef SAFETENSORS_MMAP_TABLE_H
#define SAFETENSORS_MMAP_TABLE_H

#include <stdint.h>

#include "safetensors_types.h"

int64_t safetensors_mmap_table(safetensors_table_t* table, safetensors_flags_t flags);

#endif // SAFETENSORS_MMAP_TABLE_H
