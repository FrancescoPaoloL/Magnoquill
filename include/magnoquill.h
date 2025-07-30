/* Image dimensions in pixels */ 
#define WIDTH  1024
#define HEIGHT 768

/* Plotting area within the image (rectangle boundaries) */
#define PLOT_MIN_X 70    // Left boundary of plot area
#define PLOT_MAX_X 330   // Right boundary of plot area
#define PLOT_MIN_Y 30    // Top boundary of plot area
#define PLOT_MAX_Y 350   // Bottom boundary of plot area

/* Number of frames to generate (for animation) */
#define NUM_FRAMES 300

/* Maximum iteration or value limit (purpose depends on algorithm) */
#define MAX_I 9999

/* Computed width and height of the plot area */
#define PLOT_WIDTH  (PLOT_MAX_X - PLOT_MIN_X)    // Width of the plotting region
#define PLOT_HEIGHT (PLOT_MAX_Y - PLOT_MIN_Y)    // Height of the plotting region

/* Precomputed inverses to optimize calculations (avoid repeated division) */
#define INV_PLOT_WIDTH  (1.0 / PLOT_WIDTH)
#define INV_PLOT_HEIGHT (1.0 / PLOT_HEIGHT)

/* Floating point versions of image dimensions */
#define WIDTH_F  ((double)WIDTH)
#define HEIGHT_F ((double)HEIGHT)

/* Total image size in bytes (3 bytes per pixel for RGB) because 
   we uses 3 bytes (one byte each for Red, Green, and Blue)
*/
#define IMAGE_SIZE (WIDTH * HEIGHT * 3)

/* Mathematical constant 2π for trigonometric calculations */
#define TWO_PI (2.0 * 3.14159265358979323846)

/* Inverse of the number of frames (used for normalized timing) 
    Multiplication is faster than division!
*/
#define INV_NUM_FRAMES (1.0 / NUM_FRAMES)

/* Global pointer to the image pixel data */
extern unsigned char *g_image;

/* Function to generate a single frame at time t and frame index frame_number */
void generate_frame(double t, int frame_number);

/* Declarations (prototypes) */
void fill_bg(void);
void plot_coordinates(double x, double y);

