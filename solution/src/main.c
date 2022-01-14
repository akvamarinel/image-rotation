#include "errors_types.h"
#include "find_error.h"
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
    struct image new_image = image_create(image.height, image.width);

    if(!new_image.data){
        free(image.data);
        print_error(open_msg[READ_ALLOC_ERROR]);
        exit(EXIT_FAILURE);
    }
    rotate(&image, new_image);
    bool new_status = create_pic(argv[2], &image, &new_image);

    if(!new_status) {
        exit(EXIT_FAILURE);
    }
    return 0;
}
