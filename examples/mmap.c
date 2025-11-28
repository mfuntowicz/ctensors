//
// Created by mfuntowicz on 11/25/25.
//


#include <stdio.h>
#include <time.h>
#include "safetensors.h"

// Benchmark macro - wraps a code block with timing
// Uses standard C clock() function for portability
#define BENCHMARK(name, code) do { \
    clock_t _bench_start = clock(); \
    code \
    clock_t _bench_end = clock(); \
    double _bench_elapsed_ms = ((double)(_bench_end - _bench_start) * 1000.0) / CLOCKS_PER_SEC; \
    printf("%s: %.3f ms\n", name, _bench_elapsed_ms); \
} while(0)

int main(const int argc, const char** argv)
{
    if (argc < 2)
    {
        printf("No file specified for reading.");
        return 1;
    }

    // Open the target safetensors file
    const auto table = safetensors_table_init();

    // Benchmark ctensors_fopen
    BENCHMARK("ctensors_mmap", {
        const auto status = safetensors_mmap(argv[1], table, safetensors_skip_metadata);
    });

    if (table->num_tensors > 0)
    {
        printf("\t-> loaded %d tensors\n", table->num_tensors);

        const auto lastname = table->names[table->num_tensors - 1];
        const struct safetensors_tensor* t;

        // Benchmark ctensors_table_get_tensor
        BENCHMARK("ctensors_table_get_tensor", {
            t = safetensors_table_get_tensor(table, lastname);
        });

        if (t) printf("\t-> tensor %s: dtype=%s, rank=%d, start=%lu, end=%lu\n", lastname, safetensors_dtype_as_str(t->dtype), t->rank, t->start, t->end);
        else printf("\t-> {%s} was not found\n", lastname);

        safetensors_table_free(table);
        return 0;
    }

    printf("Failed to read safetensors %s\n", argv[1]);
    safetensors_table_free(table);
    return -1;
}