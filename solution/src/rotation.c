//
// Created by mashusik on 08.01.2022.
//

#include "rotation.h"
#include <stdint.h>

void rotate(struct image * old_image, struct image new_image) {
    for ( uint64_t i = 0; i < old_image->height; i++) {
        for (uint64_t j = 0; j < old_image->width; j++) {
            new_image.data[j * new_image.width + (new_image.width - i -1)] = old_image->data[i * old_image->width + j];
        }
    }

}
