//
// Created by mashusik on 08.01.2022.
//
#include "image.h"
#include <malloc.h>


struct image create_image(uint64_t width, uint64_t height){
    struct pixel * data = (struct pixel*)malloc(height*width*(sizeof(struct pixel)));
    struct image new_image = {.width = width, .height = height, .data = data};
    return new_image;
}


