#ifndef SAFETENSORS_ERRORS_H
#define SAFETENSORS_ERRORS_H

#include "safetensors_types.h"

bool safetensors_is_ok(struct safetensors_status result);
const char* safetensors_status_code_as_str(enum safetensors_status_code code);
const char* safetensors_status_as_str(struct safetensors_status status);

#endif // SAFETENSORS_ERRORS_H
