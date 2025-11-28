//
// Created by mfuntowicz on 11/27/25.
//
#include "safetensors_fclose.h"

#include <stdio.h>
#include "safetensors_types.h"

void safetensors_fclose(const ctensors_table_t* table)
{
    if (table != nullptr)
    {
        if (table->content.kind == ctensors_with_fd && table->content.storage.fd)
            fclose(table->content.storage.fd);
    }
}