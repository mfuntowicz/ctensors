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


const struct safetensors_tensor *safetensors_table_get_tensor(const struct safetensors_table *table, const char* name)
{
    if (table->num_tensors > 0)
    {
        const auto names = table->names;
        for (auto i = 0; i < table->num_tensors; ++i)
        {
            if (strcmp(names[i], name) == 0)
                return table->tensors + i;
        }
    }

    return nullptr;
}