#ifndef SAFETENSORS_H
#define SAFETENSORS_H

#include <stdlib.h>

#include "safetensors_types.h"
#include "safetensors_fopen.h"
#include "safetensors_fclose.h"
#include "safetensors_mmap.h"
#include "safetensors_table_get_tensor.h"

/// Initialize an empty safetensors metadata table
/// @return
static inline safetensors_table_t* safetensors_table_init() { return malloc(sizeof(safetensors_table_t)); }

/// Free a previously head-allocated safetensors metadata table
/// @param table
static inline void safetensors_table_free(safetensors_table_t* table)
{
    // TODO: Handle all the free
    if (table)
    {
        if (table->num_tensors > 0) free(table->tensors);
        if (safetensors_table_is_fd(table)) safetensors_fclose(table);
        free(table);
    }

}

#endif // SAFETENSORS_H