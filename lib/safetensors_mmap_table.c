#include <string.h>

#include "safetensors_mmap_table.h"
#include "safetensors_table_read.h"

int64_t safetensors_mmap_table(safetensors_table_t* table, const safetensors_flags_t flags)
{
    uint64_t hsize;
    memcpy(&hsize, table->content.storage.mmap, sizeof(uint64_t));
    return safetensors_table_read(table, table->content.storage.mmap + sizeof(uint64_t), hsize, flags);
}
