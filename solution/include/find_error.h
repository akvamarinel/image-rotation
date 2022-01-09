//
// Created by mashusik on 09.01.2022.
//

#ifndef FIND_ERROR_H
#define FIND_ERROR_H

#include <stdint.h>
void print_read_error (uint32_t status);
void print_write_error (uint32_t status);
void print_open_error (uint32_t status);

#endif
