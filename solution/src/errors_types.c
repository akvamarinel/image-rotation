#include "errors_types.h"

 const char* read_msg[] = {
        [READ_OK] = "read ok\n",
        [READ_ERROR] = "read error\n",
        [READ_INVALID_SIGNATURE] = "read invalid signature\n",
        [READ_INVALID_BITS] = "read invalid bits\n",
        [READ_INVALID_PLANES] = "read invalid planes\n",
        [READ_ALLOC_ERROR] = "allocation error\n",
        [READ_INVALID_HEADER] = "read invalid size if header\n",

};

 const char* write_msg[] = {
        [WRITE_OK] = "write ok\n",
        [WRITE_ERROR] = "write erros\n",
};

 const char* open_msg[] = {
        [OPEN_OK] = "open ok\n",
        [OPEN_ERROR] = "open error\n",
};
