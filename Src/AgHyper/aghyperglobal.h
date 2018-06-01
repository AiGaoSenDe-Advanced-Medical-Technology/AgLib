#ifndef AG_HYPER_AGHYPERGLOBAL_HPP
#define AG_HYPER_AGHYPERGLOBAL_HPP

#include "../agglobal.hpp"

#ifdef AGHYPER_LIBRARY
    #define AG_HYPER_SHARED AG_SHARED_EXPORT
#else
    #define AG_HYPER_SHARED AG_SHARED_IMPORT
#endif

#endif
