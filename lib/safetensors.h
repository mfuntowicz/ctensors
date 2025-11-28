#ifndef CTENSORS_H
#define CTENSORS_H

#include <stdlib.h>

#include "ctensors_types.h"
#include "ctensors_fopen.h"
#include "ctensors_fclose.h"
#include "ctensors_mmap.h"
#include "ctensors_table_get_tensor.h"

/// Initialize an empty safetensors metadata table
/// @return
static inline ctensors_table_t* ctensors_table_init() { return malloc(sizeof(ctensors_table_t)); }

/// Free a previously head-allocated safetensors metadata table
/// @param table
static inline void ctensors_table_free(ctensors_table_t* table)
{
    // TODO: Handle all the free
    if (table)
    {
        if (table->num_tensors > 0) free(table->tensors);
        if (ctensors_table_is_fd(table)) ctensors_fclose(table);
        free(table);
    }

}

#endif // CTENSORS_H