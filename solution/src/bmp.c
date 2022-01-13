//
// Created by mashusik on 26.12.2021.
//

#include "bmp.h"
#include "find_error.h"
#include "rotation.h"
#include <malloc.h>
#include <stdbool.h>

static uint8_t get_padding(const uint64_t width){
    return (4 - (width * sizeof (struct pixel)) % 4) % 4;
}

static struct bmp_header create_header(const struct image * image){

    const uint8_t padding = get_padding(image->width);
    const size_t size = (image->height * ((image->width) + padding)) * sizeof(struct pixel);
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

static enum read_status check (const struct bmp_header* header){
    if (header->bfType != SIG_FORM) {
        return READ_INVALID_SIGNATURE;
    }
    else if(header->biBitCount != BITS_COUNT || header->biPlanes != PLANES || header->biCompression != COMPRESSION || header->biSize != HEADER_SIZE) {
        return READ_INVALID_HEADER;
    }
    return READ_OK;
}

static bool get_pixels (FILE * file, struct image * image, const uint64_t width, const uint64_t height, const uint8_t padding){
    for(size_t i = 0; i < height; i++ ) {
        if(fread(&image->data[i*width], sizeof(struct pixel), width, file) < width) {
            return false;
        }
        if(fseek(file, padding, SEEK_CUR) != 0) {
            return false;
        }
    }
    return true;
}


static bool write_pixels(FILE* file,struct image* image, const uint64_t width, const uint64_t height, const uint8_t padding) {
    const uint8_t buf_pad [4] = {0};
    for (size_t i = 0; i < height; ++i) {
       if (fwrite(&(image->data[i * width]), sizeof(struct pixel), width, file) < image->width) {
           return false;
       }
        if (fwrite(&buf_pad, 1, padding, file) < padding){
            return false;
        }
    }
    return true;
}
static void make_free(struct image * old_image, struct image * new_image){
    free(old_image->data);
    free(new_image->data);
}


enum read_status from_bmp(FILE * file, struct image * image) {
    struct bmp_header header = {0};
    if(fread(&header, 1,  sizeof(struct bmp_header), file) != sizeof(struct bmp_header)){
        return READ_INVALID_HEADER;
    }

    enum read_status check_status = check(&header);
    if(check_status != READ_OK) {
        return check_status;
    }
    *image = image_create(header.biWidth, header.biHeight);
    if(!image->data) {
        return READ_ALLOC_ERROR;
    }

    const uint8_t padding = get_padding(image->width);
    if(fseek(file, header.bOffBits, SEEK_SET) != 0) { //
       return READ_INVALID_BITS;
    }
    if(!get_pixels(file, image, image->width, image->height, padding)){
        return READ_INVALID_BITS;
    }
    return READ_OK;
}


enum write_status to_bmp(FILE * file, struct image * old_image, struct image * new_image) {
    struct bmp_header header = create_header(new_image);
    if(fwrite(&header, 1, sizeof(struct bmp_header), file) != sizeof(struct bmp_header)) {
       return WRITE_ERROR;
    }
    const uint8_t padding = get_padding(new_image->width);
    if(!write_pixels(file, new_image, new_image->width, new_image->height, padding)){
        return WRITE_ERROR;
    }

    make_free(old_image, new_image);
    return WRITE_OK;
}












