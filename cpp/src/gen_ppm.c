#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pixel{
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
} __attribute__((packed)) Pixel;


int main() {
    size_t width = 8000;
    size_t height = 8000;
    Pixel *buffer = malloc( width * height * sizeof(Pixel) );
    if(!buffer) return -1;

    memset(buffer, 0, width * height * sizeof(Pixel));
    for(size_t y = 0; y < height; ++y) {
        for(size_t x = 0; x < width; ++x) {
            double temp = 0.0;
            for(int k = 0; k < 200; k++) {
                temp += (float)x * (float)y;
            }
            buffer[x + width * y].Red = (unsigned char)((float)x * 255 / width);
            buffer[x + width * y].Green = (unsigned char)((float)y * 255 / height);
            buffer[x + width * y].Blue = 128;
        }
    }

    FILE *fp = fopen("mini_image.ppm", "wb");
    if(fp)
    {
        fprintf(fp, "P6\n%d %d\n255\n", width, height);
        fwrite(buffer, sizeof(Pixel), width * height, fp);
        fclose(fp);
    }
    
    free(buffer);
    printf("Generate mini_image.ppm\n");
    return 0;
}
