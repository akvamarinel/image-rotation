//
// Created by mashusik on 08.01.2022.
//

#include "rotation.h"
#include <stdint.h>

static uint64_t get_x(uint64_t i, uint64_t j, uint64_t width){
    return j * width + (width - i - 1);
}
static uint64_t get_y (uint64_t i, uint64_t j, uint64_t width){
    return i * width + j;
}

void rotate(struct image * old_image, struct image new_image) {
    for ( uint64_t i = 0; i < old_image->height; i++) {
        for (uint64_t j = 0; j < old_image->width; j++) {
            new_image.data[get_x(i, j, new_image.width)] = old_image->data[get_y(i, j, old_image->width)];
        }
    }

}
