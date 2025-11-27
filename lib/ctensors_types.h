#ifndef CTENSORS_TYPES_H
#define CTENSORS_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CTENSORS_STATUS_OK 0

///
typedef enum
{
    ctensors_skip_metadata = 1 << 1
} ctensors_flags_t;


///
typedef enum
{
    ctensors_with_mmap,
    ctensors_with_fd
} ctensors_content_kind_t;


///
typedef struct ctensors_content_t
{
    ctensors_content_kind_t kind;
    union
    {
        FILE* fd;
        char* mmap;
    } storage;
} ctensors_content_t;

/// Define all the supported Machine Learning Data Format
typedef enum
{
    ctensors_float32,
    ctensors_float16,
    ctensors_bfloat16,
    ctensors_unknown
} ctensors_dtype_t;

/// Parse the specified dtype string and return the associated ctensors_dtype_t if known
/// @param dtype The buffer string content
/// @param length The amount of character in the buffer string content
/// @return
ctensors_dtype_t ctensors_parse_dtype_from_str(const char* dtype, size_t length);

/// Retrieve a string representation of a dtype
/// @param dtype The dtype to retrieve string representation
/// @return
const char* ctensors_dtype_as_str(ctensors_dtype_t dtype);

/**
 *
 */
typedef struct ctensors_tensor_t
{
    char* name;
    uint8_t rank;
    uint32_t* shape;
    ctensors_dtype_t dtype;
    uint64_t start;
    uint64_t end;
} ctensors_tensor_t;


static inline int32_t ctensors_compare_tensor_by_name(const void* lhs, const void* rhs)
{
    const auto lhs_ = (const ctensors_tensor_t*) lhs;
    const auto rhs_ = (const ctensors_tensor_t*) rhs;

    return strcmp(lhs_->name, rhs_->name);
}



/// Holds the tensor definitions table
typedef struct ctensors_table_t
{
    uint32_t num_tensors;
    ctensors_content_t content;
    ctensors_tensor_t* tensors;
} ctensors_table_t;


/// Indicate if the ctensors was opened through `mmap`
/// @param table The table holding the underlying content
/// @return `true` if not-null and opened through `mmap`, `false` otherwise
static inline bool ctensors_table_is_mmap(const ctensors_table_t* table)
{
    if (table) return table->content.kind == ctensors_with_mmap;
    return false;
}

/// Indicate if the ctensors was opened through `fopen`
/// @param table The table holding the underlying content
/// @return `true` if not-null and opened through `fopen`, `false` otherwise
static inline bool ctensors_table_is_fd(const ctensors_table_t* table)
{
    if (table) return table->content.kind == ctensors_with_fd;
    return false;
}

#endif // CTENSORS_TYPES_H
