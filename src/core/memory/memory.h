#pragma once

#ifdef DEBUG
#define memnew(type) type
#define memdelete(ptr) ptr

#else
#define memnew(type) type
#define memdelete(ptr) ptr

#endif

namespace k_memory {
    void* 
}

