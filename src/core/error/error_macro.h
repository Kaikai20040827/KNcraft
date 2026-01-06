#pragma once
#include "core/error/error_list.h"
#include "core/error/error_func.h"

#ifdef DEBUG
#define ERROR_PRINT_FAILED(cond, ret)                       \
    do                                                      \
    {                                                       \
        error_func_print_failed(#cond, __FILE__, __LINE__); \
        return ret;                                         \
    } while (0)
#define ERROR_PRINT_ERR_OUT_OF_MEMORY(cond, ret)                   \
    do                                                             \
    {                                                              \
        error_func_print_out_of_memory(#cond, __FILE__, __LINE__); \
        return ret;                                                \
    } while (0)
#define ERROR_PRINT_ERR_SOURCE_NOT_RELEASED(cond, ret)                      \
    do                                                                      \
    {                                                                       \
        error_func_print_source_is_not_released(#cond, __FILE__, __LINE__); \
        return ret;                                                         \
    } while (0)
#define ERROR_PRINT_ERR_MEMORY_LEAKED_OUT(cond, ret)                      \
    do                                                                    \
    {                                                                     \
        error_func_print_memory_is_leaked_out(#cond, __FILE__, __LINE__); \
        return ret;                                                       \
    } while (0)

#else
#define ERROR_PRINT_FAILED(cond, ret)
#define ERROR_PRINT_ERR_OUT_OF_MEMORY(cond, ret)
#define ERROR_PRINT_ERR_SOURCE_NOT_RELEASED(cond, ret)
#define ERROR_PRINT_ERR_MEMORY_LEAKED_OUT(cond, ret)

#endif