#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#else
assert(false && "Windows is not supported yet.")
#endif

#include "ctensors_fopen.h"

#include "ctensors_fread_table.h"

int64_t ctensors_fopen(const char* path, ctensors_table_t* table, ctensors_flags_t flags)
{
    FILE* fs;
    if ((fs = fopen(path, "rb")) == NULL)
    {
        // TODO : Error handling
    }

    // Read the header table from the stream
    // Return the table
    table->content.kind = ctensors_with_fd;
    table->content.storage.fd = fs;
    return ctensors_fread_table(table, flags);
}
