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

    bool new_status = create_pic(argv[2], &image);
    if(!new_status) {
        exit(EXIT_FAILURE);
    }
    return 0;
}
