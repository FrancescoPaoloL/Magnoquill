#include "magnoquill.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include "utils.h"

int main() {
    if (!create_directory("frames", 0755)) {
        free(g_image);
        return 1;
    }

    if (!create_directory("video", 0755)) {
        free(g_image);
        return 1;
    }

    g_image = malloc(IMAGE_SIZE);
    if (!g_image) {
        fprintf(stderr, "Failed to allocate image buffer\n");
        return 1;
    }
    
    // WIP

    free(g_image);
    return 0;
}