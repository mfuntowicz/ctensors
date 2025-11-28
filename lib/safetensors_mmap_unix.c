#include "safetensors_mmap_unix.h"

#include <unistd.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "safetensors_mmap_table.h"

struct safetensors_status safetensors_mmap(
    const char *path, struct safetensors_table *table, const enum safetensors_flags flags)
{
    struct safetensors_status result = {0};
    const int fd = open(path, O_RDONLY);
    if (fd == -1) {
        result.what = SAFETENSORS_FILE_NOT_FOUND;
        result.message = path;
        return result;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        result.what = SAFETENSORS_FILE_NOT_FOUND;
        result.message = path;
        goto close_fd_and_return;
    }

    if (sb.st_size == 0) {
        result.what = SAFETENSORS_FILE_EMPTY;
        result.message = path;
        goto close_fd_and_return;
    }

    // 3. Map the file into memory
    // arguments: addr, length, prot, flags, fd, offset
    char *content = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (content == MAP_FAILED) {
        result.what = SAFETENSORS_FILE_MMAP_FAILED;
        result.message = path;
        goto close_fd_and_return;
    }

    table->content.kind = SAFETENSORS_WITH_MMAP;
    table->content.storage.mmap = content;

    return safetensors_mmap_table(table, flags);

close_fd_and_return:
    close(fd);
    return result;
}