#include "magnoquill.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void generate_frame(double t, int frame_number) {
    /*Create sequential filenames 
        PPM stands for Portable Pixmap Format, and we want to save each animation frame as a picture.
    */
    char filename[128];
    snprintf(filename, sizeof(filename), "frames/frame_%04d.ppm", frame_number);

    FILE *f = fopen(filename, "wb");
    if (!f) {
        perror("Failed to open file");
        exit(1);
    }

    /*Write PPM header
        P6 means the file stores binary RGB data (that is it writes the raw RGB bytes for every pixel).
    */
    fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);

    // Fill background (dark gray color in this case)
    fill_bg();

    /*
        Algorithm summary (see: https://x.com/yuruyurau/status/1942231466446057727)

        a = (x, y, d = mag(
                k = (4 + sin(x / 11 + t * 8)) * cos(x / 14), 
                e = y / 8 - 19
            ) + sin(y / 9 + t * 2)) =>

            point(
                (q = 2 * sin(k * 2) + sin(y / 17) * k * (9 + 2 * sin(y - d * 3)))
                + 50 * cos(c = d * d / 49 - t) + 200,
                q * sin(c) + d * 39 - 440
            );

        t = 0;

        draw = $ => {
            // Initialize canvas once
            if (!t) createCanvas(w = 400, w);

            // Set background and stroke color/opacity
            background(9);
            stroke(w, 96);

            // Increment time for animation progression
            t += PI / 240;

            // Plot 10,000 points per frame
            for (i = 10000; i--; )
                a(i, i / 235);
        };
    */

    double t8 = 8.0 * t;                                                            // correspond to the 8*t
    double t2 = 2.0 * t;                                                            // correspond to the 2*t
                                                                                    //
    double cos_c_factor = 50.0;                                                     // these because of cos/sin multiplication
    double sin_c_factor = 39.0;

    for (int i = MAX_I; i >= 0; --i) {
        double x = (double)i;
        double y = x / 235.0;

        double sin_term = sin(x / 11.0 + t8);
        double cos_term = cos(x / 14.0);
        double k = (4.0 + sin_term) * cos_term;

        double e = y / 8.0 - 19.0;
        double d = sqrt(k * k + e * e) + sin(y / 9.0 + t2);

        double sin_2k = sin(2.0 * k);
        double sin_y17 = sin(y / 17.0);
        double sin_y_3d = sin(y - 3.0 * d);
        double q = 2.0 * sin_2k + sin_y17 * k * (9.0 + 2.0 * sin_y_3d);

        double c = d * d / 49.0 - t;
        double cos_c = cos(c);
        double sin_c = sin(c);

        double xp = q + cos_c_factor * cos_c + 200.0;
        double yp = q * sin_c + d * sin_c_factor - 440.0;

        double fx = xp;
        double fy = 400.0 - yp;

        plot_coordinates(fx, fy);
    }

    fwrite(g_image, 1, IMAGE_SIZE, f);
    fclose(f);
}
