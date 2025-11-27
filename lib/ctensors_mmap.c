#include "ctensors_mmap.h"
#include <stdio.h>

#include "ctensors_mmap_table.h"

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/stat.h>
#else
#error("Windows is not supported yet.")
#endif


int64_t ctensors_mmap(const char* path, ctensors_table_t* table, ctensors_flags_t flags)
{
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    const int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");

        // TODO: Better error handling
        return -1;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("Error getting file size");
        close(fd);

        // TODO: Better error handling
        return -1;
    }

    if (sb.st_size == 0) {
        fprintf(stderr, "File is empty\n");
        close(fd);

        // TODO: Better error handling
        return -1;
    }

    // 3. Map the file into memory
    // arguments: addr, length, prot, flags, fd, offset
    char *content = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (content == MAP_FAILED) {
        perror("Error mmapping the file");
        close(fd);

        // TODO: Better error handling
        return -1;
    }

    table->content.kind = ctensors_with_mmap;
    table->content.storage.mmap = content;

    return ctensors_mmap_table(table, flags);
#else
// Windows logic (using CreateFileMapping, etc.)
#error("Windows is not supported yet.")
#endif
}