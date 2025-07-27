#include "magnoquill.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned char *g_image = NULL;

/* Convert plot coordinates (x,y) to pixel coordinates (px, py) on the image */
static inline void plot_to_pixel(double x, double y, int *px, int *py) {
    *px = (int)((x - PLOT_MIN_X) * INV_PLOT_WIDTH * WIDTH_F);
    *py = HEIGHT - (int)((y - PLOT_MIN_Y) * INV_PLOT_HEIGHT * HEIGHT_F);
}

static void fill_background(unsigned char *image) {
    //Sets the first pixel’s red, green, and blue values all to 9 --> It's very dark gray color
    image[0] = image[1] = image[2] = 9;

    // Fills the entire image with the first pixel's color
    for (int i = 1; i < WIDTH * HEIGHT; i++) {
        memcpy(&image[i * 3], &image[0], 3);
    }
}

/* Set one pixel (at px, py) to white (RGB = 255,255,255) */
static inline void plot_point(unsigned char *image, int px, int py) {
    // the pixel is within the image bounds?
    if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
        // Ok: make it white
        //Remember each pixel in an RGB image uses 3 bytes: 
        //  image[idx] → Red
        //  image[idx + 1] → Green 
        //  image[idx + 2] → Blue
        int idx = (py * WIDTH + px) * 3;
        image[idx] = image[idx + 1] = image[idx + 2] = 255;
    }
}

/*Fill with the background color*/
void fill_bg() {
    fill_background(g_image);
}

/* See comments about plot_point()*/
void plot_pixel(int px, int py) {
    plot_point(g_image, px, py);
}

/* Plot a point in the plot area defined by PLOT_MIN_X, PLOT_MAX_X, PLOT_MIN_Y, PLOT_MAX_Y */
void plot_coordinates(double fx, double fy) {
    // If given point (fx, fy) is inside the plot area...
    if (fx >= PLOT_MIN_X && fx <= PLOT_MAX_X &&
        fy >= PLOT_MIN_Y && fy <= PLOT_MAX_Y) {
        //...convert to pixels and draw it white
        int px, py;
        plot_to_pixel(fx, fy, &px, &py);
        plot_point(g_image, px, py);
    }
}
