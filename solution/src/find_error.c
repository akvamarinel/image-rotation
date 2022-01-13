//
// Created by mashusik on 09.01.2022.
//
#include "bmp.h"
#include "find_error.h"
#include "serialization.h"
#include <stdio.h>

void print_error(const char* str) {
    fputs(str, stderr);
}

