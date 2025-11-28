

#include "safetensors_types.h"

#include <string.h>

safetensors_dtype_t safetensors_parse_dtype_from_str(const char* dtype, const size_t length)
{
    if (strncmp(dtype, "BF16", length) == 0) return safetensors_bfloat16;
    if (strncmp(dtype, "FP32", length) == 0) return safetensors_float32;
    if (strncmp(dtype, "FP16", length) == 0) return safetensors_float16;

    return safetensors_unknown;
}

const char* safetensors_dtype_as_str(const safetensors_dtype_t dtype)
{
    switch (dtype)
    {
    case safetensors_bfloat16: return "bfloat16";
    case safetensors_float16: return "float16";
    case safetensors_float32: return "float32";
    default: return "unknown";
    }

}