//
// Created by mashusik on 08.01.2022.
//
#include "errors_types.h"
#include "find_error.h"
#include "serialization.h"
#include <stdbool.h>


bool read_pic (char* path, struct image * image){ //fixme add argument (from_bmp)
    FILE * file = NULL;
    file = fopen(path, "rb");
    if (file == NULL) {
        print_error(open_msg[OPEN_ERROR]);

       // print_open_error(OPEN_ERROR);
        return false;
    }
    enum read_status status = from_bmp(file, image);
    if(status != READ_OK) {
        print_error(read_msg[status]);
        //print_read_error(status);
        fclose(file);
        return false;
    }
    fclose(file);
    return true;
}

bool create_pic(char* path, struct image * image, struct image * new_image ) {
    FILE * file = NULL;
    file = fopen(path, "wb");
    if(file == NULL) {
        return false;
    }
    enum write_status status = to_bmp(file, image, new_image);

    if(status != WRITE_OK){
        print_error(write_msg[status]);
        fclose(file);
        return false;
    }
    fclose(file);
    return true;
}

