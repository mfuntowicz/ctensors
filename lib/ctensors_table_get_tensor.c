//
// Created by mfuntowicz on 11/27/25.
//

#include "ctensors_table_get_tensor.h"

#include <stdlib.h>
#include <string.h>


int find_tenor_by_name(const void* key, const void* tensor)
{
    const char* key_ = key;
    const ctensors_tensor_t* tensor_ = tensor;
    return strcmp(key_, tensor_->name);
}


ctensors_tensor_t* ctensors_table_get_tensor(const ctensors_table_t* table, const char* name)
{
    if (table->num_tensors > 0)
    {
        const auto tensors = table->tensors;
        return bsearch(name, tensors, table->num_tensors, sizeof(ctensors_tensor_t), find_tenor_by_name);
    }

    return nullptr;
}