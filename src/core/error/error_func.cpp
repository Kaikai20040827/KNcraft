#include "core/error/error_func.h"

// error_msgs 0, failed
void error_func_print_failed(const char *cond, const char *file, const char *line)
{
    std::cout << "[error] " << cond << " " << error_msgs[0] << " at " << file << ':' << line << '\n';
}

// error_msgs 1, out of memory
void error_func_print_out_of_memory(const char *cond, const char *file, const char *line)
{
    std::cout << "[error] " << cond << " " << error_msgs[1] << " at " << file << ':' << line << '\n';
}

// error_msgs 2, source is not released
void error_func_print_source_is_not_released(const char *cond, const char *file, const char *line)
{
    std::cout << "[error] " << cond << " " << error_msgs[2] << " at " << file << ':' << line << '\n';
}

// error_msgs 3, memory is leaked out
void error_func_print_memory_is_leaked_out(const char *cond, const char *file, const char *line)
{
    std::cout << "[error] " << cond << " " << error_msgs[3] << " at " << file << ':' << line << '\n';
}
