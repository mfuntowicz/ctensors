#ifndef SAFETENSORS_MMAP_TABLE_H
#define SAFETENSORS_MMAP_TABLE_H

#include <stdint.h>

#include "safetensors_types.h"

struct safetensors_status safetensors_mmap_table(struct safetensors_table* table, enum safetensors_flags flags);

#endif // SAFETENSORS_MMAP_TABLE_H
