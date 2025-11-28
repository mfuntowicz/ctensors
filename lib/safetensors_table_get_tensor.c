//
// Created by mfuntowicz on 11/27/25.
//

#include "safetensors_table_get_tensor.h"

#include <stdlib.h>
#include <string.h>


int find_tensor_by_name(const void* key, const void* name)
{
    const char* key_ = key;
    const char* name_ = name;
    return strcmp(key_, name_);
}


safetensors_tensor_t* safetensors_table_get_tensor(const safetensors_table_t* table, const char* name)
{
    if (table->num_tensors > 0)
    {
        const auto names = table->names;
        return bsearch(name, names, table->num_tensors, sizeof(char *), find_tensor_by_name);
    }

    return nullptr;
}