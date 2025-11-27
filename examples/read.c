//
// Created by mfuntowicz on 11/25/25.
//


#include <stdio.h>
#include <time.h>

#include "ctensors.h"

// Helper function to calculate the time-difference in nanoseconds
time_t timespec_diff_ns(const struct timespec* start, const struct timespec* end)
{
    const time_t seconds = (end->tv_sec - start->tv_sec);
    const time_t nanoseconds = (end->tv_nsec - start->tv_nsec);
    return (seconds * 1000000000) + nanoseconds;
}

// Benchmark macro - wraps a code block with timing
#define BENCHMARK(name, code) do { \
    struct timespec _bench_start, _bench_end; \
    clock_gettime(CLOCK_MONOTONIC, &_bench_start); \
    code \
    clock_gettime(CLOCK_MONOTONIC, &_bench_end); \
    time_t _bench_elapsed = timespec_diff_ns(&_bench_start, &_bench_end); \
    printf("%s: %lu ns\n", name, _bench_elapsed); \
} while(0)

int main(const int argc, const char** argv)
{
    if (argc < 2)
    {
        printf("No file specified for reading.");
        return 1;
    }

    // Open the target safetensors file
    const auto table = ctensors_table_init();
    int32_t num_tensors;

    // Benchmark ctensors_fopen
    BENCHMARK("ctensors_fopen", {
        num_tensors = ctensors_fopen(argv[1], table, ctensors_skip_metadata);
    });

    if (num_tensors > 0)
    {
        printf("\t-> loaded %d tensors\n", num_tensors);

        const auto lastname = table->tensors[num_tensors - 1].name;
        const ctensors_tensor_t* t;

        // Benchmark ctensors_table_get_tensor
        BENCHMARK("ctensors_table_get_tensor", {
            t = ctensors_table_get_tensor(table, lastname);
        });

        if (t) printf("\t-> Tensor %s: dtype=%s, rank=%d, start=%lu, end=%lu\n", lastname, ctensors_dtype_as_str(t->dtype), t->rank, t->start, t->end);
        else printf("\t-> {%s} was not found\n", lastname);

        ctensors_table_free(table);
        return 0;
    }

    printf("Failed to read safetensors %s\n", argv[1]);
    ctensors_table_free(table);
    return -1;
}