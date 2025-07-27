#include "magnoquill.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include "utils.h"

int main() {
    // Allocate memory for the global image buffer 
    // to store pixel data
    g_image = malloc(IMAGE_SIZE);
    if (!g_image) {
        fprintf(stderr, "Failed to allocate image buffer\n");
        return 1;
    }

    // Create directories for output files
    const char *dirs[] = {"frames", "video"};
    for (int i = 0; i < 2; i++) {
        if (create_directory(dirs[i], 0755)) {
            free(g_image);
            return 1;
        }
    }

    // Generate frames for the animation
    printf("Generating %d frames...\n", NUM_FRAMES);
    for (int frame = 0; frame < NUM_FRAMES; ++frame) {
        double t = TWO_PI * frame * INV_NUM_FRAMES;
        generate_frame(t, frame);

        if ((frame + 1) % 10 == 0 || frame == NUM_FRAMES - 1) {
            printf("Generated frame %d/%d (%.1f%%)\n",
                frame + 1, NUM_FRAMES,
                100.0 * (frame + 1) / NUM_FRAMES);
        }
    }
    printf("Saving frames to 'frames/' directory...\n");

    //WIP



    free(g_image);
    return 0;
}