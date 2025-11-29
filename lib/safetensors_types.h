#ifndef SAFETENSORS_TYPES_H
#define SAFETENSORS_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define SAFETENSORS_STATUS_OK 0

/**
 *
 */
enum safetensors_status_code
{
    SAFETENSORS_SUCCESS = 0,
    SAFETENSORS_ALLOCATION_FAILED = 1,
    SAFETENSORS_FILE_NOT_FOUND = 10,
    SAFETENSORS_FILE_EMPTY = 11,
    SAFETENSORS_FILE_MMAP_FAILED = 12,
    SAFETENSORS_HEADER_INVALID = 20,
    SAFETENSORS_HEADER_TOO_LARGE = 21,
    SAFETENSORS_HEADER_INVALID_START_CHAR = 22,
    SAFETENSORS_HEADER_JSON_ERROR = 23,
    SAFETENSORS_TENSOR_NOT_FOUND = 30,
    SAFETENSORS_UNKNOWN_DTYPE = 31,
};

/**
 * @struct safetensors_status
 *
 * Represents an error structure containing information about
 * errors encountered during safetensors operations.
 *
 * This structure holds the kind of error and an accompanying
 * error message describing the issue.
 *
 * @var kind
 * The type of error that occurred, represented by
 * safetensors_error_kind_t enumeration.
 *
 * @var message
 * A pointer to a character array containing a descriptive
 * error message. Called must manage this memory appropriately.
 *
 * @var length
 * Amount of character stored in the `message` one can read safely.
 */
struct safetensors_status
{
    enum safetensors_status_code what;
    const char* message;
};

static struct safetensors_status SAFETENSORS_SUCCEEDED = {SAFETENSORS_SUCCESS};


///
enum safetensors_flags
{
    safetensors_skip_metadata = 1 << 1
} ;


///
enum safetensors_access_kind
{
    SAFETENSORS_WITH_MMAP,
    SAFETENSORS_WITH_FD
};


///
struct safetensors_content
{
    union
    {
        FILE* fd;
        char* mmap;
    } storage;
    enum safetensors_access_kind kind;
} ;

/// Define all the supported Machine Learning Data Format
enum safetensors_dtype
{
    SAFETENSORS_FLOAT32,
    SAFETENSORS_FLOAT16,
    SAFETENSORS_BFLOAT16,
    SAFETENSORS_UNKNOWN
};

/// Parse the specified dtype string and return the associated safetensors_dtype_t if known
/// @param dtype The buffer string content
/// @param length The amount of character in the buffer string content
/// @return
enum safetensors_dtype safetensors_parse_dtype_from_str(const char* dtype, size_t length);

/// Retrieve a string representation of a dtype
/// @param dtype The dtype to retrieve string representation
/// @return
const char* safetensors_dtype_as_str(enum safetensors_dtype dtype);

///
struct safetensors_tensor
{
    enum safetensors_dtype dtype;
    uint8_t rank;
    uint32_t *shape;
    size_t start;
    size_t end;
};

/// Holds the tensor definitions table
struct safetensors_table
{
    uint32_t num_tensors;
    char **names;
    struct safetensors_content content;
    struct safetensors_tensor *tensors;
};


/// Indicate if the safetensors was opened through `mmap`
/// @param table The table holding the underlying content
/// @return `true` if not-null and opened through `mmap`, `false` otherwise
static inline bool safetensors_table_is_mmap(const struct safetensors_table *table)
{
    if (table) return table->content.kind == SAFETENSORS_WITH_MMAP;
    return false;
}

/// Indicate if the safetensors was opened through `fopen`
/// @param table The table holding the underlying content
/// @return `true` if not-null and opened through `fopen`, `false` otherwise
static inline bool safetensors_table_is_fd(const struct safetensors_table *table)
{
    if (table) return table->content.kind == SAFETENSORS_WITH_FD;
    return false;
}

#endif // SAFETENSORS_TYPES_H
