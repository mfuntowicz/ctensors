#ifndef CTENSORS_MMAP_H
#define CTENSORS_MMAP_H
#include <stdint.h>

#include "ctensors_types.h"

int64_t ctensors_mmap(const char* path, ctensors_table_t* table, ctensors_flags_t flags);

#endif // CTENSORS_MMAP_H
