#ifndef SAFETENSORS_FCLOSE_H
#define SAFETENSORS_FCLOSE_H

#include "safetensors_types.h"

/// Close the specified table through the opened file descriptor
/// @param table
void safetensors_fclose(const safetensors_table_t* table);

#endif // SAFETENSORS_FCLOSE_H
