#include "core/error/error_list.h"

const char *error_msgs[] = {
    "failed",                 // FAILED
    "out of memory",          // ERR_OUT_OF_MEMORY
    "source is not released", // ERR_SOURCE_NOT_RELEASED
    "memory is leaked out",   // ERR_MEMORY_LEAKED_OUT
};
