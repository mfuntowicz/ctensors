#include <string.h>

#include "safetensors_mmap_table.h"
#include "safetensors_table_read.h"

struct safetensors_status safetensors_mmap_table(struct safetensors_table *table, const enum safetensors_flags flags)
{
    uint64_t hsize;
    memcpy(&hsize, table->content.storage.mmap, sizeof(uint64_t));
    return safetensors_table_read(table, table->content.storage.mmap + sizeof(uint64_t), hsize, flags);
}
