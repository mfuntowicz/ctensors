#include "safetensors_header_parse.h"
#include "safetensors_table_read.h"

#include <stdlib.h>

int compare_strings (const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}


int32_t safetensors_table_read(safetensors_table_t* table, const char* header, const size_t size, const safetensors_flags_t flags)
{
    // Allocate the final table holding tensor definitions
    const auto num_tensors = safetensors_header_parse(table, header, size, flags);

    // Sort table keys
    qsort(table->tensors, table->num_tensors, sizeof(safetensors_tensor_t), compare_strings);
    return num_tensors;
}
