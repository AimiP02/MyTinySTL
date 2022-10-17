/*
 *
 * Creadted by i3roNy@ on 2022/10/17
 *
 */

#ifndef Bronya_STL_STL_CONSTRUCT_H
#define Bronya_STL_STL_CONSTRUCT_H

#include <new>
#include "stl_config.h"
#include "type_traits.h"
#include "stl_iterator_base.h"

__STL_BEGIN_NAMESPACE

    /* 构造对象 */
    template<class _T1>
    inline void _Construct(_T1 *__p) {
        new((void *)__p) _T1();
    }

    template<class _T1, class _T2>
    inline void _Constuct(_T1 *__p, const _T2 &__value) {
        new((void *) __p) _T1(__value);
    }

    /* 析构对象 */
    template<class _T>
    void __Destroy_one(_T *, __true_type) {}

    template<class _T>
    void __Destroy_one(_T *pointer, __false_type) {
        if(pointer != nullptr) {
            pointer->~TP();
        }
    }

    template<class _T>
    inline void _Destroy(_T *pointer) {
        typedef typename __type_traits<_T>::has_trivial_destructor _Trivial_destructor;
        __Destroy_one(pointer, _Trivial_destructor());
    }

    template<class _ForwardIterator>
    void __Destroy_aux_one(_ForwardIterator , _ForwardIterator , __true_type) {}

    template<class _ForwardIterator>
    void __Destroy_aux_one(_ForwardIterator __first, _ForwardIterator __last, __false_type) {
        for( ; __first != __last; ++__first) {
            _Destroy(&*__first);
        }
    }

    template<class _ForwardIterator, class _T>
    inline void __Destroy(_ForwardIterator __first, _ForwardIterator __last, _T *) {
        typedef typename __type_traits<_T>::has_trivial_destructor _Trivial_destructor;
        __Destroy_aux_one(__first, __last, _Trivial_destructor());
    }

    template<class _ForwardIterator>
    inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last) {
        __Destroy(__first, __last, __value_type(__first));
    }

    inline void _Destroy(char *, char *) {}
    inline void _Destroy(int *, int *) {}
    inline void _Destroy(float *, float *) {}
    inline void _Destroy(long *, long *) {}
    inline void _Destroy(double *, double *) {}

    template<class _T1, class _T2>
    inline void construct(_T1 *__p, _T2 &__value) {
        _Construct(__p, __value);
    }

    template<class _T>
    inline void construct(_T *__p) {
        _Construct(__p);
    }

    template<class _T>
    inline void destroy(_T *__p) {
        _Destroy(__p);
    }

    template<class _ForwardIterator>
    inline void destroy(_ForwardIterator __first, _ForwardIterator __last) {
        _Destroy(__first, __last);
    }

__STL_END_NAMESPACE

#endif