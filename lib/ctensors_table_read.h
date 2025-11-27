#ifndef CTENSORS_TABLE_READ_H
#define CTENSORS_TABLE_READ_H
#include <stddef.h>

#include "ctensors_types.h"

int32_t ctensors_table_read(ctensors_table_t* table, const char* header, size_t size, ctensors_flags_t flags);

#endif // CTENSORS_TABLE_READ_H
