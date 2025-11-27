

#include "ctensors_types.h"

#include <string.h>

ctensors_dtype_t ctensors_parse_dtype_from_str(const char* dtype, const size_t length)
{
    if (strncmp(dtype, "BF16", length) == 0) return ctensors_bfloat16;
    if (strncmp(dtype, "FP32", length) == 0) return ctensors_float32;
    if (strncmp(dtype, "FP16", length) == 0) return ctensors_float16;

    return ctensors_unknown;
}

const char* ctensors_dtype_as_str(const ctensors_dtype_t dtype)
{
    switch (dtype)
    {
    case ctensors_bfloat16: return "bfloat16";
    case ctensors_float16: return "float16";
    case ctensors_float32: return "float32";
    default: return "unknown";
    }

}