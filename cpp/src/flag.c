#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb_image_write.h"

#define OLIVEC_IMPLEMENTATION
#include "../lib/olive.c"

#define WIDTH 900
#define HEIGHT 600

/* unsigned int_32: RGBA 0xRRGGBBAA  */
uint32_t pixels[WIDTH * HEIGHT];

int main(){
    Olivec_Canvas oc =  olivec_canvas(pixels, WIDTH, HEIGHT, WIDTH);
    olivec_fill( oc, 0xFFFFFFFF );
    olivec_circle( oc, WIDTH/2, HEIGHT/2, 150,  0xFF0000FF );
    const char* png_path = "jp_flag.png";
    stbi_write_png(png_path, WIDTH, HEIGHT, 4, oc.pixels, WIDTH*4);    
    return 0;
}
