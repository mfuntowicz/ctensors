//
// Created by mfuntowicz on 11/27/25.
//

#ifndef CTENSORS_CTENSORS_GET_TENSOR_H
#define CTENSORS_CTENSORS_GET_TENSOR_H

#include "ctensors_types.h"

/// Attempt to retrieve the tensor definition through its name
/// @param table Table holding all the tensors
/// @param name Null-terminated tensor's name to look for
/// @return
ctensors_tensor_t* ctensors_table_get_tensor(const ctensors_table_t* table, const char *name);

#endif //CTENSORS_CTENSORS_GET_TENSOR_H