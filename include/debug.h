#ifndef DEBUG_H
#define DEBUG_H

#include <GL/glew.h>
#include <iostream>

#ifdef _DEBUG
#pragma message("DEBUG MODE")
#else
#pragma message("RELEASE MODE")
#endif

#if defined(_MSC_VER)
#define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
#define DEBUG_BREAK() __builtin_trap()
#else
#define DEBUG_BREAK()
#endif

#define ASSERT(x) \
    if (!(x))     \
    DEBUG_BREAK()

#ifdef _DEBUG
#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#else
#define GLCall(x) x
#endif

inline void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

inline bool GLLogCall(const char *function, const char *file, int line)
{
    bool hasError = false;
    while (GLenum error = glGetError())
    {
        std::cout
            << "[OpenGL Error] (" << error << ")\n"
            << "    Function: " << function << "\n"
            << "    Location: " 
            << file <<":"<< line << std::endl;
        hasError = true;
    }
    return !hasError;
}

// Log and Error
inline int __log_index = 0;
inline size_t __log_expected = 0;

#ifdef _DEBUG
#define LOG_PLAN(total)                                           \
    do                                                            \
    {                                                             \
        __log_expected = total;                                   \
        __log_index = 0;                                          \
        std::cout << "===== PLAN: " << total << " STEPS =====\n"; \
    } while (0)
#else 
#define LOG_PLAN(total)
#endif

#ifdef _DEBUG
#define LOG(x)                                                          \
    do                                                                  \
    {                                                                   \
        std::cout << "[LOG] ["                                          \
                  << ++__log_index << "/" << __log_expected << "] "      \
                  << x << " (" << __FILE__ << ":" << __LINE__ << ")\n"; \
    } while (0)

#define ERR(x) std::cerr << "[ERR] " << x << " (" << __FILE__ << ":" << __LINE__ << ")\n"
#else 
#define LOG(x)
#define ERR(x)
#endif

#endif
