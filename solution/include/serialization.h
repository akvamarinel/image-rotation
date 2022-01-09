//
// Created by mashusik on 08.01.2022.
//

#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <stdbool.h>
#include "bmp.h"
#include "image.h"
#include "find_error.h"

enum open_status {
    OPEN_OK = 0,
    OPEN_ERROR
};

bool read_pic (char*, struct image *);
bool create_pic(char*, struct image *);

#endif //UNTITLED7_SERIALIZATION_H
