#include "safetensors_header_parse.h"

#include <stdlib.h>
#include <string.h>

#include "safetensors_errors.h"
#include "safetensors_table_read.h"

int compare_strings (const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

struct safetensors_status safetensors_table_read(
    struct safetensors_table *table, const char *header, const size_t size, const enum safetensors_flags flags)
{
    // Allocate the final table holding tensor definitions
    const struct safetensors_status status = safetensors_header_parse(table, header, size, flags);
    if (!safetensors_is_ok(status))
        return status;

    // Sort table keys
    qsort(table->tensors, table->num_tensors, sizeof(struct safetensors_tensor), compare_strings);
    return SAFETENSORS_SUCCEEDED;
}
