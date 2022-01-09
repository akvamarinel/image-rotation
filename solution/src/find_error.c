//
// Created by mashusik on 09.01.2022.
//
#include "bmp.h"
#include "find_error.h"
#include "serialization.h"
#include <stdio.h>
void print_read_error (uint32_t status){
    switch (status) {
        case READ_INVALID_HEADER:
            fputs("invalid header", stderr);
            break;
        case READ_INVALID_BITS:
            fputs("invalid bits", stderr);
            break;
        case READ_INVALID_SIGNATURE:
            fputs("invalid signature", stderr);
            break;
        default:
            break;
    }
}

void print_write_error (uint32_t status) {
     switch (status) {
         case WRITE_ERROR:
             fputs("write error", stderr);
             break;
     }
}
void print_open_error (uint32_t status){
    switch (status) {
        case OPEN_ERROR:
            fputs("open error", stderr);
            break;
        default:
            break;
    }
}