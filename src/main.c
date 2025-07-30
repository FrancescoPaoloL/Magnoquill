#include "magnoquill.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    //check if ffmpeg is installed
    printf("Checking for ffmpeg installation...\n");
    int ffmpeg_check = system("ffmpeg -version > /dev/null 2>&1");
    
    if (ffmpeg_check != 0) {
        printf("ERROR: ffmpeg is not installed or not found in PATH!\n");
        printf("Please refer here: https://command-not-found.com/ffmpeg\n");
        free(g_image);
        return 1;
    }

    //ok ffmpeg is installed, proceed to create the MP4 animation
    printf("\nCreating MP4 animation...\n");
    int ffmpeg_result = system("ffmpeg -framerate 30 -i frames/frame_%04d.ppm -c:v libx264 -pix_fmt yuv420p video/out.mp4 -y");

    if (ffmpeg_result == 0) {
        printf("Animation created successfully: video/out.mp4\n");
        printf("Cleaning up frame files...\n");
        
        char filepath[256];
        for (int i = 0; i < NUM_FRAMES; i++) {
            sprintf(filepath, "frames/frame_%04d.ppm", i);
            if (remove(filepath) != 0) {
                fprintf(stderr, "Error deleting file %s: %s\n", filepath, strerror(errno));
            }
        }

        rmdir("frames");
        printf("Temporary frame files deleted.\n");
    } else {
        printf("Error creating animation. Frame files preserved in 'frames/' folder.\n");
        printf("You can manually run:\n");
        printf("ffmpeg -framerate 30 -i frames/frame_%%04d.ppm -c:v libx264 -pix_fmt yuv420p video/out.mp4\n");
    }
    
    // Free the allocated image buffer
    free(g_image);
    return 0;
}
