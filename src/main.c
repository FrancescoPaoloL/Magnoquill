#include "magnoquill.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

int main() {
    g_image = malloc(IMAGE_SIZE);
    if (!g_image) {
        fprintf(stderr, "Failed to allocate image buffer\n");
        return 1;
    }

    int status = mkdir("frames", 0777);
    if (status == -1 && errno != EEXIST) {
        perror("Failed to create frames directory");
        free(g_image);
        return 1;
    }

    
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

    status = mkdir("video", 0755);
    if (status == -1 && errno != EEXIST) {
        perror("Failed to create video directory");
        free(g_image);
        return 1;
    }

    //ADD CONTROLS IF ffmpeg is not installed!
    printf("Saving frames to 'frames/' directory...\n");
    printf("\nCreating MP4 animation...\n");
    int ffmpeg_result = system("ffmpeg -framerate 30 -i frames/frame_%04d.ppm -c:v libx264 -pix_fmt yuv420p video/out.mp4 -y");

    if (ffmpeg_result == 0) {
        printf("Animation created successfully: out.mp4\n");
        printf("Cleaning up frame files...\n");
        system("rm -f frames/frame_*.ppm");
        system("rmdir frames");
        printf("Frame files deleted.\n");
    } else {
        printf("Error creating animation. Frame files preserved in 'frames/' folder.\n");
        printf("You can manually run:\n");
        printf("ffmpeg -framerate 30 -i frames/frame_%%04d.ppm -c:v libx264 -pix_fmt yuv420p out.mp4\n");
    }

    free(g_image);
    return 0;
}