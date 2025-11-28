#ifndef SAFETENSORS_TABLE_READ_H
#define SAFETENSORS_TABLE_READ_H
#include <stddef.h>

#include "safetensors_types.h"

struct safetensors_status safetensors_table_read(
    struct safetensors_table *table, const char *header, size_t size, enum safetensors_flags flags);

#endif // SAFETENSORS_TABLE_READ_H
