#include "safetensors_errors.h"

#include <stdlib.h>

#include "string.h"

bool safetensors_is_ok(const struct safetensors_status status)
{
    return status.what == SAFETENSORS_SUCCESS;
}

const char *safetensors_status_code_as_str(const enum safetensors_status_code status)
{
    switch (status)
    {
    case SAFETENSORS_ALLOCATION_FAILED:
        return "Allocation failed";
    case SAFETENSORS_FILE_NOT_FOUND:
        return "File not found";
    case SAFETENSORS_FILE_EMPTY:
        return "File is empty";
    case SAFETENSORS_FILE_MMAP_FAILED:
        return "Failed to mmap the file";
    case SAFETENSORS_HEADER_INVALID:
        return "Invalid header";
    case SAFETENSORS_HEADER_TOO_LARGE:
        return "Header too large";
    case SAFETENSORS_HEADER_INVALID_START_CHAR:
        return "Invalid header starting character";
    case SAFETENSORS_HEADER_JSON_ERROR:
        return "Error while parsing JSON header";
    case SAFETENSORS_TENSOR_NOT_FOUND:
        return "Tensor not found";
    case SAFETENSORS_UNKNOWN_DTYPE:
        return "Unknown data type";
    default:
        return nullptr;
    }
}


const char *safetensors_status_as_str(const struct safetensors_status status)
{
    // auto* what = safetensors_status_code_as_str(status.what);
    // char* reason = malloc((sizeof(kind) + strlen()) * sizeof(char));
    // strcpy(reason, kind);

    return nullptr;
}