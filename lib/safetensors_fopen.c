#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#else
assert(false && "Windows is not supported yet.")
#endif

#include "safetensors_fopen.h"

#include "safetensors_fread_table.h"

int64_t safetensors_fopen(const char* path, safetensors_table* table, safetensors_flags flags)
{
    FILE* fs;
    if ((fs = fopen(path, "rb")) == NULL)
    {
        // TODO : Error handling
    }

    // Read the header table from the stream
    // Return the table
    table->content.kind = safetensors_with_fd;
    table->content.storage.fd = fs;
    return safetensors_fread_table(table, flags);
}
