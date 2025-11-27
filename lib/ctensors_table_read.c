#include "ctensors_header_parse.h"
#include "ctensors_table_read.h"

#include <stdlib.h>


int32_t ctensors_table_read(ctensors_table_t* table, const char* header, const size_t size, const ctensors_flags_t flags)
{
    // Allocate the final table holding tensor definitions
    const auto num_tensors = ctensors_header_parse(table, header, size, flags);

    // Sort table keys
    qsort(table->tensors, table->num_tensors, sizeof(ctensors_tensor_t), ctensors_compare_tensor_by_name);
    return num_tensors;
}
