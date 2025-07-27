#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int create_directory(const char *name, mode_t mode) {
    int status = mkdir(name, mode);
    if (status == -1 && errno != EEXIST) {
        fprintf(stderr, "Failed to create directory '%s': %s (errno %d)\n", 
                name, strerror(errno), errno);
        return 1;
    }
    return 0;
}
