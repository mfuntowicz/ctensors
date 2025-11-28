#ifndef SAFETENSORS_MMAP_LINUX_H
#define SAFETENSORS_MMAP_LINUX_H

#include "safetensors_types.h"

struct safetensors_status safetensors_mmap(
    const char* path, struct safetensors_table* table, enum safetensors_flags flags);

#endif // SAFETENSORS_MMAP_LINUX_H
