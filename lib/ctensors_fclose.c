//
// Created by mfuntowicz on 11/27/25.
//
#include "ctensors_fclose.h"

#include <stdio.h>
#include "ctensors_types.h"

void ctensors_fclose(const ctensors_table_t* table)
{
    if (table->content.kind == ctensors_with_fd && table->content.storage.fd)
        fclose(table->content.storage.fd);
}
