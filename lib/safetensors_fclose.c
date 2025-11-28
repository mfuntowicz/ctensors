//
// Created by mfuntowicz on 11/27/25.
//
#include "safetensors_fclose.h"

#include <stdio.h>
#include "safetensors_types.h"

void safetensors_fclose(const safetensors_table* table)
{
    if (table != nullptr)
    {
        if (table->content.kind == safetensors_with_fd && table->content.storage.fd)
            fclose(table->content.storage.fd);
    }
}