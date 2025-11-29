//
// Created by mfuntowicz on 11/25/25.
//

#include "safetensors_header_parse.h"

#include <stdlib.h>
#include <string.h>
#include <yyjson.h>

#include "safetensors_errors.h"
#include "safetensors_types.h"

enum safetensors_status_code safetensors_header_parse_dtype(
    yyjson_val *dtype, struct safetensors_tensor *tensor, struct safetensors_status *status)
{
    if (dtype && yyjson_is_str(dtype)) {
        const char* dtype_str = yyjson_get_str(dtype);
        const size_t dtype_len = yyjson_get_len(dtype);
        tensor->dtype = safetensors_parse_dtype_from_str(dtype_str, dtype_len);
    }
    else {
        tensor->dtype = SAFETENSORS_UNKNOWN;
    }

    if (tensor->dtype == SAFETENSORS_UNKNOWN) {
        status->what = SAFETENSORS_UNKNOWN_DTYPE;
        status->message = "Unknown dtype";
    }

    return status->what;
}

enum safetensors_status_code safetensors_header_parse_offsets(
    yyjson_val *offsets, struct safetensors_tensor *tensor, struct safetensors_status *status)
{
    if (offsets && yyjson_is_arr(offsets)) {
        const size_t length = yyjson_arr_size(offsets);
        if (length >= 2) {
            yyjson_val* start_val = yyjson_arr_get(offsets, 0);
            yyjson_val* end_val = yyjson_arr_get(offsets, 1);

            if (yyjson_is_uint(start_val))
                tensor->start = yyjson_get_uint(start_val);

            if (yyjson_is_uint(end_val))
                tensor->end = yyjson_get_uint(end_val);

            return SAFETENSORS_SUCCESS;
        }

        status->what = SAFETENSORS_HEADER_INVALID;
        status->message = "Expected length 2 array (begin, end)";
    } else {
        status->what = SAFETENSORS_HEADER_INVALID;
        status->message = "Expected offsets to be represented as an array";
    }
    return status->what;
}

enum safetensors_status_code safetensors_header_parse_shape(
    yyjson_val *shape, struct safetensors_tensor *tensor, struct safetensors_status *status)
{
    if (shape && yyjson_is_arr(shape)) {
        const size_t rank = yyjson_arr_size(shape);
        tensor->rank = (uint8_t)rank;

        if (rank > 0) {
            //TODO : Add malloc checking
            if ((tensor->shape = calloc(rank, sizeof(uint32_t))) == nullptr) {
                status->what = SAFETENSORS_ALLOCATION_FAILED;
                status->message = "Failed to allocate memory to store tensor's shape";
            }

            size_t shape_idx = 0, shape_max = 0;
            yyjson_val* dim_val;
            yyjson_arr_foreach(shape, shape_idx, shape_max, dim_val) {
                if (yyjson_is_uint(dim_val))
                    tensor->shape[shape_idx] = (uint32_t)yyjson_get_uint(dim_val);
            }
            return SAFETENSORS_SUCCESS;
        } else {
            tensor->shape = nullptr;
            return SAFETENSORS_SUCCESS;
        }
    } else {
        status->what = SAFETENSORS_HEADER_INVALID;
        status->message = "Expected shape to be an array of integers";
        return SAFETENSORS_HEADER_INVALID;
    }
}

enum safetensors_status_code safetensors_header_parse_tensor(
    yyjson_val *specs, struct safetensors_tensor *tensor, struct safetensors_status *status)
{
    // Parse dtype
    yyjson_val* dtype_val = yyjson_obj_get(specs, "dtype");
    if (safetensors_header_parse_dtype(dtype_val, tensor, status) != SAFETENSORS_SUCCESS) return status->what;

    // Parse shape
    yyjson_val* shape_val = yyjson_obj_get(specs, "shape");
    if (safetensors_header_parse_shape(shape_val, tensor, status) != SAFETENSORS_SUCCESS) return status->what;

    // Parse offsets
    yyjson_val* data_offsets_val = yyjson_obj_get(specs, "data_offsets");
    return safetensors_header_parse_offsets(data_offsets_val, tensor, status);
}

struct safetensors_status safetensors_header_parse(
    struct safetensors_table *table, const char *header, const size_t hsize, const enum safetensors_flags flags)
{
    struct safetensors_status status = {0};

    // Parse JSON
    yyjson_read_err error;
    yyjson_doc *document = yyjson_read_opts(header, hsize, YYJSON_READ_NOFLAG, nullptr, &error);
    if (!document) {
        status.what = SAFETENSORS_HEADER_JSON_ERROR;
        status.message = error.msg;
        goto freeup_and_return;
    }

    yyjson_val *root = yyjson_doc_get_root(document);
    if (!yyjson_is_obj(root)) {
        status.what = SAFETENSORS_HEADER_JSON_ERROR;
        status.message = error.msg;
        goto freeup_and_return;
    }

    table->num_tensors = yyjson_obj_size(root);
    if ((table->names = calloc(table->num_tensors, sizeof(char*))) == nullptr) {
        status.what = SAFETENSORS_ALLOCATION_FAILED;
        status.message = "Failed to allocated memory to store tensor's names";
    }

    if ((table->tensors = calloc(table->num_tensors, sizeof(struct safetensors_tensor))) == nullptr) {
        status.what = SAFETENSORS_ALLOCATION_FAILED;
        status.message = "Failed to allocated memory to store tensor's descriptor";
    }

    size_t idx, max;
    yyjson_val *key, *val;
    yyjson_obj_foreach(root, idx, max, key, val) {

        const char *keyval = yyjson_get_str(key);
        const bool is_metadata = strcmp(keyval, "__metadata__") == 0;

        // Skip __metadata__ if the flag is set
        if (is_metadata)
            if (!(flags & safetensors_skip_metadata)) { /* TODO: Not implemented yet */ }

        // Create the final tensor name with a null-terminator string to allow usage of str functions like strncmp
        const size_t name_len = yyjson_get_len(key);
        if ((table->names[idx] = calloc(name_len + 1, sizeof(char))) == nullptr) {
            status.what = SAFETENSORS_ALLOCATION_FAILED;
            status.message = "Failed to allocated memory to store tensor's name";
            goto freeup_and_return;
        }

        // TODO: Shall we copy the string here? Or just keep track of the pointer?
        strncpy(table->names[idx], keyval, name_len);

        // Parse tensor object
        if (!is_metadata)
        {
            if (!yyjson_is_obj(val)) {
                status.what = SAFETENSORS_HEADER_INVALID;
                status.message = "Expected JSON object";
                goto freeup_and_return;
            }

            if (safetensors_header_parse_tensor(val, table->tensors + idx, &status) != SAFETENSORS_SUCCESS)
                goto freeup_and_return;


            const auto tensor = table->tensors[idx];
            printf(
                "Discovered tensor %s (%s) -> start: %lu, end: %lu\n",
                table->names[idx], safetensors_dtype_as_str(tensor.dtype), tensor.start, tensor.end
            );
        }
    }

    return SAFETENSORS_SUCCEEDED;

freeup_and_return:
    if (document != nullptr)
        yyjson_doc_free(document);

    if (table->tensors)
        free(table->tensors);

    if (table->names)
        for (size_t i = 0; i < table->num_tensors; ++i) free(table->names[i]);

    return status;
}
