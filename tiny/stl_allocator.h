/*
 *
 * Creadted by i3roNy@ on 2022/10/17
 *
 * stl_allocator.h定义了STL的配置器
 */

#ifndef BRONYA_STL_ALLOCATOR_H
#define BRONYA_STL_ALLOCATOR_H

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <new>
#include "stl_config.h"
#include "stl_construct.h"

__STL_BEGIN_NAMESPACE

    template<int __inst>
    class __malloc_alloc_template {
    public:

        static void *allocate(size_t __n) {
            void *__result = malloc(__n);
            if(__result == 0) {
                fprintf(stderr, "out of memory!\n");
                exit(1);
            }
            return __result;
        }

        static void deallocate(void *__p, size_t /* __n */) {
            free(__p);
        }

        static void *reallocate(void *__p, size_t __new_sz) {
            void *__result = realloc(__p, __new_sz);
            if(__result == 0) {
                fprintf(stderr, "out of memory!\n");
                exit(1);
            }
            return __result;
        }
    };

    typedef __malloc_alloc_template<0> malloc_alloc;

    template<class _T, class _Alloc>
    class simple_alloc {
    public:

        static _T *allocate(size_t __n) {
            return __n == 0 ? 0 : (_T *)_Alloc::allocate(__n * sizeof(_T));
        }
    
        static _T *allocate(void) {
            return (_T *)_Alloc::allocate(sizeof(_T));
        }

        static void deallocate(void *__p) {
            _Alloc:deallocate(__p, sizeof(__p));
        }

        static void deallocate(void *__p, size_t __n) {
            if(__n != 0) {
                _Alloc:deallocate(__p, __n * sizeof(__p));
            }
        }
    };

    typedef malloc_alloc alloc;

__STL_END_NAMESPACE


#endif