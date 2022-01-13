//
// Created by mashusik on 26.12.2021.
//

#include "bmp.h"
#include "find_error.h"
#include "rotation.h"
#include <malloc.h>
#include <stdbool.h>

uint8_t get_padding(uint64_t width){
    return(4 - (width * sizeof (struct pixel)) % 4) % 4;
}

struct bmp_header create_header(struct image * image){

    uint8_t padding = get_padding(image->width);
            //(4 - (image->width * sizeof (struct pixel)) % 4) % 4;
    size_t size = (image->height * ((image->width) + padding)) * sizeof(struct pixel);
    struct bmp_header new_header = {
            .bfType = SIG_FORM,
            .biHeight = image->height,
            .biWidth = image->width,
            .bOffBits = sizeof (struct bmp_header),
            .biSize = HEADER_SIZE,
            .biPlanes = PLANES,
            .bfileSize = sizeof(struct bmp_header)+ size,
            .biCompression = COMPRESSION,
            .bfReserved = 0,
            .biBitCount = BITS_COUNT,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrUsed = 0,
            .biClrImportant = 0,
            .biSizeImage = size
    };
    return new_header;
}

enum read_status check (struct bmp_header* header){
    if (header->bfType != SIG_FORM) {
        print_read_error(READ_INVALID_SIGNATURE);
        return READ_INVALID_SIGNATURE;
    }
    else if(header->biBitCount != BITS_COUNT || header->biPlanes != PLANES || header->biCompression != COMPRESSION || header->biSize != HEADER_SIZE) {
        print_read_error(READ_INVALID_HEADER);
        return READ_INVALID_HEADER;
    }
    return READ_OK;
}

void get_pixels (FILE * file, struct image * image, uint64_t width, uint64_t height, uint8_t padding){
    for(size_t i = 0; i < height; i++ ) {
        fread(&image->data[i*width], sizeof(struct pixel), width, file);
        fseek(file, padding, SEEK_CUR);
    }
}


void write_pixels(FILE* file,struct image* image, uint64_t width, uint64_t height, uint8_t padding) {
    uint8_t buf_pad [4] = {0};
    for (size_t i = 0; i < height; ++i) {
        fwrite(&(image->data[i * width]), sizeof(struct pixel), width, file);
        fwrite(&buf_pad, 1, padding, file);
    }
}
void make_free(struct image * old_image, struct image * new_image){
    free(old_image->data);
    free(new_image->data);
}


enum read_status from_bmp(FILE * file, struct image * image) {
    struct bmp_header header = {0};
    if(fread(&header, 1,  sizeof(struct bmp_header), file) != sizeof(struct bmp_header)){
        print_read_error(READ_INVALID_HEADER);
        return READ_INVALID_HEADER;
    }

    enum read_status check_status = check(&header);
    if(check_status != READ_OK) {
        print_read_error(check_status);
        return check_status;
    }
    *image = create_image(header.biWidth, header.biHeight);


    uint8_t padding = get_padding(image->width);
            //(4 - (image->width * sizeof (struct pixel)) % 4) % 4;
    if(fseek(file, header.bOffBits, SEEK_SET) != 0) { //
       print_read_error(READ_INVALID_BITS);
       return READ_INVALID_BITS;
    }
    get_pixels(file, image, image->width, image->height, padding);
    return READ_OK;
}


enum write_status to_bmp_and_rotate(FILE * file, struct image * old_image) {

    struct image new_image = create_image(old_image->height, old_image->width);

    //new_image.data = old_image->data;
    struct bmp_header header = create_header(&new_image);
    rotate(old_image, new_image);
    if( fwrite(&header, 1, sizeof(struct bmp_header), file) != sizeof(struct bmp_header)) {
       print_write_error(WRITE_ERROR);
       return WRITE_ERROR;
    }
    uint8_t padding = get_padding(new_image.width);
    write_pixels(file, &new_image, new_image.width, new_image.height, padding);

    make_free(old_image, &new_image);
    return WRITE_OK;
}












