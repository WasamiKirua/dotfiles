#include "config.h"

#include "block.h"
#include "util.h"

Block blocks[] = {
    {"sb-music",   0,    2 },
    {"sb-disk",    1800, 3 },
    {"sb-memory",  10,   4 },
    {"sb-loadavg", 5,    5 },
    {"sb-volume",  0,    8 },
    {"sb-date",    1,    10},
};

const unsigned short blockCount = LEN(blocks);
