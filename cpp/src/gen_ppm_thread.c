#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define THREADS_NUMBER 8 
#define PPM_COLOR_MAXVAL 255 
#define RGB_BLUE 0x0f
typedef struct Pixel{
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
} __attribute__((packed)) Pixel;

// int pthread_create(pthread_t *thread, const pthread_util_t *attr, 
//                 void *(*start_routine)(void *), void *arg);  

typedef struct {
    int start_line;
    int end_line;
    int width;
    int height;
    Pixel *buffer;
} thread_args;

void* render(void* arg) {
    thread_args* data = (thread_args*)arg;
   if(!data)   return NULL;
   for(size_t y = data->start_line; y < data->end_line; ++y) {
       for(size_t x = 0; x < data->width; ++x) {
           int index = x + data->width * y;
           double temp = 0.0;
           for(int k = 0; k < 200; k++) {
               temp += (float)x * (float)y;
           }
           data->buffer[index].Red = (unsigned char)((float)x * PPM_COLOR_MAXVAL / data->width);
           data->buffer[index].Green = (unsigned char)((float)y * PPM_COLOR_MAXVAL / data->height);
           data->buffer[index].Blue = RGB_BLUE;
       }
   }
   return NULL;
}



int main() {

    size_t width = 8000;
    size_t height = 8 * 1000;
    Pixel *buffer = malloc( width * height * sizeof(Pixel) );
    int step = height / THREADS_NUMBER;


    pthread_t threads[THREADS_NUMBER];
    thread_args args[THREADS_NUMBER];
    for(size_t i = 0; i < THREADS_NUMBER; ++i) {
        args[i].buffer = buffer;
        args[i].width = width;
        args[i].height = height;
        args[i].start_line = i * step; 
        args[i].end_line = (i + 1) * step;
        pthread_create(&threads[i], NULL, render, &args[i]);
    }


    for(size_t i = 0; i < THREADS_NUMBER; ++i) {
        pthread_join(threads[i], NULL);
    }
        
    FILE *fp = fopen("mini_image_thread.ppm", "wb");
    if(fp)
    {
        fprintf(fp, "P6\n%zu %zu\nPPM_COLOR_MAXVAL\n", width, height);
        fwrite(buffer, sizeof(Pixel), width * height, fp);
        fclose(fp);
    }
    
    free(buffer);
    printf("Generate mini_image_thread.ppm\n");
    return 0;
}
