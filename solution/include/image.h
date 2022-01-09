//
// Created by mashusik on 08.01.2022.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <stdint.h>
struct pixel {
    uint8_t b, g, r;
};

struct image {
    uint64_t width, height;
    struct pixel* data;
};



struct image create_image(const uint64_t width, const uint64_t height);

#endif
