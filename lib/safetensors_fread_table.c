//
// Created by mfuntowicz on 11/25/25.
//

#include "safetensors_fread_table.h"

#include <stdlib.h>

#include "safetensors_header_parse.h"
#include "safetensors_table_read.h"


int64_t safetensors_fread_table(safetensors_table_t* table, const safetensors_flags_t flags)
{
    // Read the size of the header JSON string
    // TODO: Always Little-Ending, should we do something smarter here?
    uint64_t hsize;
    if (fread(&hsize, sizeof(uint64_t), 1, table->content.storage.fd) != 1)
    {
        // TODO: Error handling
        printf("Failed to read header size from stream");
    }

    // Append the NULL termination
    char* header_json_content = malloc(hsize);
    if (fread(header_json_content, 1, hsize, table->content.storage.fd) != hsize)
    {
        // TODO: Error handling
        printf("Failed to read header from stream");
    }

    // TODO: Better handling parsing error
    safetensors_table_read(table, header_json_content, hsize, flags);

    // Free the JSON header string, we don't need it from now on
    free(header_json_content);
    return table->num_tensors;
}
