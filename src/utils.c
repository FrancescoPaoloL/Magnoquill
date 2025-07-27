#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>


int create_directory(const char *name, mode_t mode) {
    int status = mkdir(name, mode);
    if (status == -1 && errno != EEXIST) {
        fprintf(stderr, "Failed to create directory '%s': ", name);
        perror("");
        return 0;
    }
    return 1;
}