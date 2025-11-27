#ifndef CTENSORS_H
#define CTENSORS_H

#include <stdlib.h>

#include "ctensors_types.h"
#include "ctensors_fopen.h"
#include "ctensors_mmap.h"
#include "ctensors_table_get_tensor.h"

static inline ctensors_table_t* ctensors_table_init() { return malloc(sizeof(ctensors_table_t)); }
static inline void ctensors_table_free(ctensors_table_t* table)
{
    // TODO: Handle all the free

    free(table);
}

#endif // CTENSORS_H