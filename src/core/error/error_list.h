#pragma once

#include <string>

enum class Error{
    FAILED,
    ERR_OUT_OF_MEMORY,
    ERR_SOURCE_NOT_RELEASED,
    ERR_MEMORY_LEAKED_OUT,
};


extern const char* error_msgs[];

