#include "serialization.h"
#include <stdbool.h>


int main(int argc, char* const argv []) {
    (void) argc;
    struct image image = {0};
    bool status = read_pic(argv[1], &image);

    if (!status){
        exit(-1);
    }

    bool new_status = create_pic(argv[2], &image);
    if(!new_status) {
        exit(-1);
    }
    return 0;
}
