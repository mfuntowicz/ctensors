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
const struct safetensors_tensor *safetensors_table_get_tensor(const struct safetensors_table *table, const char *name);

#endif //SAFETENSORS_GET_TENSOR_H