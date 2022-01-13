#include "image.h"
#include "rotation.h"
#include "serialization.h"
#include <stdbool.h>
#include <stdlib.h>


int main(int argc, char* const argv []) {
    if(argc < 3) {
        fputs("please, write all arguments", stderr);
        exit(EXIT_FAILURE);
    }
    struct image image = {0};
    bool status = read_pic(argv[1], &image);

    if (!status){
        exit(EXIT_FAILURE);
    }
    struct image new_image = {0};
    new_image = image_create(image.height, image.width);
    rotate(&image, new_image);
    bool new_status = create_pic(argv[2], &image, &new_image);

    if(!new_status) {
        exit(EXIT_FAILURE);
    }
    return 0;
}
