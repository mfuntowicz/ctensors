//
// Created by mfuntowicz on 11/25/25.
//

#include "safetensors_header_parse.h"

#include <stdlib.h>
#include <string.h>
#include <yyjson.h>

int32_t safetensors_header_parse(safetensors_table_t* table, const char* header, const size_t hsize, const safetensors_flags_t flags)
{
    int32_t num_tensors = 0;
    int32_t num_allocated_tensors = 2048;
    table->names = malloc(num_allocated_tensors * sizeof(table->names));
    table->tensors = malloc(num_allocated_tensors * sizeof(table->tensors));

    if (!table->tensors) {
        return safetensors_headers_alloc_failed;
    }

    // Parse JSON
    yyjson_doc* document = yyjson_read(header, hsize, YYJSON_READ_NOFLAG);
    if (!document) {
        free(table->tensors);
        return safetensors_header_invalid_starting_char;
    }

    yyjson_val* root = yyjson_doc_get_root(document);
    if (!yyjson_is_obj(root)) {
        yyjson_doc_free(document);
        free(table->tensors);
        return safetensors_header_invalid_starting_char;
    }

    size_t idx, max;
    yyjson_val *key, *val;
    yyjson_obj_foreach(root, idx, max, key, val) {
        const char* tensor_name = yyjson_get_str(key);

        // Skip __metadata__ if the flag is set
        if (strcmp(tensor_name, "__metadata__") == 0) {
            if (flags & safetensors_skip_metadata) {
                continue;
            }
            // TODO: not impl yet ;
        }

        // Check if we need to resize the tensor array
        if (num_tensors >= num_allocated_tensors) {
            num_allocated_tensors *= 2;
            safetensors_tensor_t* new_tensors = realloc(table->tensors, num_allocated_tensors * sizeof(safetensors_tensor_t));
            if (!new_tensors) {
                // Cleanup on failure
                for (int32_t i = 0; i < num_tensors; i++) {
                    free(table->tensors[i].shape);
                }
                free(table->tensors);
                yyjson_doc_free(document);
                return safetensors_headers_alloc_failed;
            }
            table->tensors = new_tensors;
        }

        char* name = table->names[num_tensors];
        safetensors_tensor_t* tensor = &table->tensors[num_tensors];

        // Create the finale tensor name with a null-terminator string to allow usage of str functions like strncmp
        const size_t name_len = yyjson_get_len(key);

        // TODO: check calloc returns
        name = calloc(name_len + 1, sizeof(char));
        if (!name) {
            for (int32_t i = 0; i < num_tensors; i++) {
                free(table->tensors[i].shape);
            }
            free(table->tensors);
            yyjson_doc_free(document);
            return safetensors_headers_alloc_failed;
        }
        strncpy(name, tensor_name, name_len);

        // Parse tensor object
        if (!yyjson_is_obj(val)) {
            free(name);
            continue;
        }

        yyjson_val* dtype_val = yyjson_obj_get(val, "dtype");
        yyjson_val* data_offsets_val = yyjson_obj_get(val, "data_offsets");
        yyjson_val* shape_val = yyjson_obj_get(val, "shape");

        // Parse dtype
        if (dtype_val && yyjson_is_str(dtype_val)) {
            const char* dtype_str = yyjson_get_str(dtype_val);
            const size_t dtype_len = yyjson_get_len(dtype_val);
            tensor->dtype = safetensors_parse_dtype_from_str(dtype_str, dtype_len);
        } else {
            tensor->dtype = safetensors_unknown;
        }

        // Parse data_offsets [start, end]
        if (data_offsets_val && yyjson_is_arr(data_offsets_val)) {
            const size_t length = yyjson_arr_size(data_offsets_val);
            if (length >= 2) {
                yyjson_val* start_val = yyjson_arr_get(data_offsets_val, 0);
                yyjson_val* end_val = yyjson_arr_get(data_offsets_val, 1);

                if (yyjson_is_uint(start_val)) {
                    tensor->start = yyjson_get_uint(start_val);
                }
                if (yyjson_is_uint(end_val)) {
                    tensor->end = yyjson_get_uint(end_val);
                }
            }
        }

        // Parse shape
        if (shape_val && yyjson_is_arr(shape_val)) {
            const size_t rank = yyjson_arr_size(shape_val);
            tensor->rank = (uint8_t)rank;

            if (rank > 0) {
                //TODO : Add malloc checking
                tensor->shape = calloc(rank, sizeof(uint32_t));
                if (!tensor->shape) {
                    free(name);
                    for (int32_t i = 0; i < num_tensors; i++) {
                        free(table->tensors[i].shape);
                    }
                    free(table->tensors);
                    yyjson_doc_free(document);
                    return safetensors_headers_alloc_failed;
                }

                size_t shape_idx = 0, shape_max = 0;
                yyjson_val* dim_val;
                yyjson_arr_foreach(shape_val, shape_idx, shape_max, dim_val) {
                    if (yyjson_is_uint(dim_val)) {
                        tensor->shape[shape_idx] = (uint32_t)yyjson_get_uint(dim_val);
                    }
                }
            } else {
                tensor->shape = nullptr;
            }
        } else {
            tensor->rank = 0;
            tensor->shape = nullptr;
        }

        num_tensors++;
    }

    yyjson_doc_free(document);

    // Resize to the exact size if we over-allocated
    if (num_tensors < num_allocated_tensors && num_tensors > 0) {
        safetensors_tensor_t* final_tensors = realloc(table->tensors, num_tensors * sizeof(safetensors_tensor_t));
        char** names = realloc(table->names, num_tensors * sizeof(char*));

        if (final_tensors) table->tensors = final_tensors;
        if (names) table->names = names;
        // TODO: If realloc fails,
    }

    table->num_tensors = num_tensors;
    return num_tensors;
}