

#include "safetensors_types.h"

#include <string.h>

enum safetensors_dtype safetensors_parse_dtype_from_str(const char *dtype, const size_t length)
{
    if (strncmp(dtype, "BF16", length) == 0) return SAFETENSORS_BFLOAT16;
    if (strncmp(dtype, "FP32", length) == 0) return SAFETENSORS_FLOAT32;
    if (strncmp(dtype, "FP16", length) == 0) return SAFETENSORS_FLOAT16;

    return SAFETENSORS_UNKNOWN;
}

const char *safetensors_dtype_as_str(const enum safetensors_dtype dtype)
{
    switch (dtype)
    {
    case SAFETENSORS_BFLOAT16: return "bfloat16";
    case SAFETENSORS_FLOAT16: return "float16";
    case SAFETENSORS_FLOAT32: return "float32";
    default: return "unknown";
    }

}