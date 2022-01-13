//
// Created by mashusik on 08.01.2022.
//
#include "image.h"
#include <malloc.h>


struct image image_create(const uint64_t width, const uint64_t height){
    struct pixel * data = (struct pixel*)malloc(height*width*(sizeof(struct pixel)));
    struct image new_image = {.width = width, .height = height, .data = data};
    return new_image;
}


