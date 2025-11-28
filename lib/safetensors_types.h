#ifndef SAFETENSORS_TYPES_H
#define SAFETENSORS_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define SAFETENSORS_STATUS_OK 0

///
typedef enum
{
    safetensors_skip_metadata = 1 << 1
} safetensors_flags_t;


///
typedef enum
{
    safetensors_with_mmap,
    safetensors_with_fd
} safetensors_content_kind_t;


///
typedef struct safetensors_content_t
{
    safetensors_content_kind_t kind;
    union
    {
        FILE* fd;
        char* mmap;
    } storage;
} safetensors_content_t;

/// Define all the supported Machine Learning Data Format
typedef enum
{
    safetensors_float32,
    safetensors_float16,
    safetensors_bfloat16,
    safetensors_unknown
} safetensors_dtype_t;

/// Parse the specified dtype string and return the associated safetensors_dtype_t if known
/// @param dtype The buffer string content
/// @param length The amount of character in the buffer string content
/// @return
safetensors_dtype_t safetensors_parse_dtype_from_str(const char* dtype, size_t length);

/// Retrieve a string representation of a dtype
/// @param dtype The dtype to retrieve string representation
/// @return
const char* safetensors_dtype_as_str(safetensors_dtype_t dtype);

///
typedef struct safetensors_tensor_t
{
    uint8_t rank;
    uint32_t* shape;
    safetensors_dtype_t dtype;
    uint64_t start;
    uint64_t end;
} safetensors_tensor_t;

/// Holds the tensor definitions table
typedef struct safetensors_table_t
{
    uint32_t num_tensors;
    char* const* names;
    safetensors_content_t content;
    safetensors_tensor_t* tensors;
} safetensors_table_t;


/// Indicate if the safetensors was opened through `mmap`
/// @param table The table holding the underlying content
/// @return `true` if not-null and opened through `mmap`, `false` otherwise
static inline bool safetensors_table_is_mmap(const safetensors_table_t* table)
{
    if (table) return table->content.kind == safetensors_with_mmap;
    return false;
}

/// Indicate if the safetensors was opened through `fopen`
/// @param table The table holding the underlying content
/// @return `true` if not-null and opened through `fopen`, `false` otherwise
static inline bool safetensors_table_is_fd(const safetensors_table_t* table)
{
    if (table) return table->content.kind == safetensors_with_fd;
    return false;
}

#endif // SAFETENSORS_TYPES_H
