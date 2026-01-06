#pragma once

#include "core/error/error_list.h"
#include <iostream>

extern void error_func_print_failed(const char* cond, const char* file, const char* line);
extern void error_func_print_out_of_memory(const char* cond, const char* file, const char* line);
extern void error_func_print_source_is_not_released(const char* cond, const char* file, const char* line);
extern void error_func_print_memory_is_leaked_out(const char* cond, const char* file, const char* line);