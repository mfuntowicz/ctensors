#ifndef SAFETENSORS_MMAP_H
#define SAFETENSORS_MMAP_H

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include "safetensors_mmap_unix.h"
#else
#error("Windows is not supported yet.")
#endif


#endif // SAFETENSORS_MMAP_H
