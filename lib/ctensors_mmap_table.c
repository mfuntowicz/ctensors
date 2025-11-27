#include <string.h>

#include "ctensors_mmap_table.h"
#include "ctensors_table_read.h"

int64_t ctensors_mmap_table(ctensors_table_t* table, const ctensors_flags_t flags)
{
    uint64_t hsize;
    memcpy(&hsize, table->content.storage.mmap, sizeof(uint64_t));
    return ctensors_table_read(table, table->content.storage.mmap + sizeof(uint64_t), hsize, flags);
}
