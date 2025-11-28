//
// Created by mfuntowicz on 11/27/25.
//

#ifndef SAFETENSORS_GET_TENSOR_H
#define SAFETENSORS_GET_TENSOR_H

#include "safetensors_types.h"

/// Attempt to retrieve the tensor definition through its name
/// @param table Table holding all the tensors
/// @param name Null-terminated tensor's name to look for
/// @return
safetensors_tensor_t* safetensors_table_get_tensor(const safetensors_table_t* table, const char *name);

#endif //SAFETENSORS_GET_TENSOR_H