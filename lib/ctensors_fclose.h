#ifndef CTENSORS_FCLOSE_H
#define CTENSORS_FCLOSE_H

#include "ctensors_types.h"

/// Close the specified table through the opened file descriptor
/// @param table
void ctensors_fclose(const ctensors_table_t* table);

#endif // CTENSORS_FCLOSE_H
