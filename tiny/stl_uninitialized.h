/*
 *
 * Creadted by i3roNy@ on 2022/10/18
 *
 * stl_uninitialized.h定义一些修改未初始化空间的函数
 * 包括有：
 * uninitialized_copy
 * uninitialized_fill
 * uninitialized_fill_n
 * 
 */

#ifndef BRONYA_STL_UNINITIALIZED_H
#define BRONYA_STL_UNINITIALIZED_H

#include "stl_config.h"
#include "stl_construct.h"
#include "stl_iterator_base.h"
#include "type_traits"
#include "stl_algobase.h"

__STL_BEGIN_NAMESPACE

    /* uninitialized_copy: 将 [ __first, __last ) 区间内的元素复制到以 __result 为起始的内存空间，返回复制结束的位置 */
    template<class _InputIterator, class _ForwardIterator>
    inline _ForwardIterator __uninitialized_copy_aux(_InputIterator __first, _InputIterator __last, _ForwardIterator __result,
                                                     __true_type) {
        return copy(__first, __last, __result);
    }

    template<class _InputIterator, class _ForwardIterator>
    inline _ForwardIterator __uninitialized_copy_aux(_InputIterator __first, _InputIterator __last, _ForwardIterator __result,
                                                     __false_type) {
        _ForwardIterator __cur = __result;
        try {
            for( ; __first != __last; ++__first, ++__cur) {
                construct(&*__cur, *__first);
            }
            return __cur;
        }
        catch(...) {
            destroy(__result, __cur);
        }
    }

    template<class _InputIterator, class _ForwardIterator, class _T>
    inline _ForwardIterator __uninitialized_copy(_InputIterator __first, _InputIterator __last, _ForwardIterator __result, _T *) {
        typedef typename __type_traits<_T>::is_POD_type _Is_POD;
        return __uninitialized_copy_aux(__first, __last, __result, _Is_POD());
    }

    template<class _InputIterator, class _ForwardIterator>
    inline _ForwardIterator uninitialized_copy(_InputIterator __first, _InputIterator __last, _ForwardIterator __result) {
        return __uninitialized_copy(__first, __last, __result, value_type(__first));
    }

    /* uninitialized_fill: 在 [ __first, __last ) 区间内填充元素值 */
    template<class _ForwardIterator, class _T>
    inline void __uninitialized_fill_aux(_ForwardIterator __first, _ForwardIterator __last, const _T &__x,
                                         __true_type) {
        fill(__first, __last, __x);
    }

    template<class _ForwardIterator, class _T>
    inline void __uninitialized_fill_aux(_ForwardIterator __first, _ForwardIterator __last, const _T &__x,
                                         __false_type) {
        _ForwardIterator __cur = __first;
        try {
            for( ; __cur != __last; ++__cur) {
                construct(&*__cur, __x);
            }
        }
        catch(...) {
            destroy(__first, __cur);
        }
    }

    template<class _ForwardIterator, class _T1, class _T2>
    inline void __uninitialized_fill(_ForwardIterator __first, _ForwardIterator __last, const _T1 &__x,
                                     _T2 *) {
        typedef typename __type_traits<_T2>::is_POD_type _Is_POD;
        __uninitialized_fill_aux(__first, __last, __x, _Is_POD());
    }

    template<class _ForwardIterator, class _T>
    inline void uninitialized_fill(_ForwardIterator __first, _ForwardIterator __last, const _T &__x) {
        __uninitialized_fill(__first, __last, __x, value_type(__first));
    }

    /* uninitialized_fill_n: 从 __first 位置开始，填充n个元素值，返回填充的位置 */
    template<class _ForwardIterator, class _Size, class _T>
    inline _ForwardIterator __uninitialized_fill_n_aux(_ForwardIterator __first, _Size __n, const _T &__x,
                                                       __true_type) {
        return fill_n(__first, __n, __x);
    }

    template<class _ForwardIterator, class _Size, class _T>
    inline _ForwardIterator __uninitialized_fill_n_aux(_ForwardIterator __first, _Size __n, const _T &__x,
                                                       __false_type) {
        _ForwardIterator __cur = __first;
        try {
            for( ; __n > 0; --__n, ++__cur) {
                construct(&*__cur, __x);
            }
            return __cur;
        }
        catch(...) {
            destroy(__first, __cur);
        }
    }

    template<class _ForwardIterator, class _Size, class _T1, class _T2>
    inline _ForwardIterator __uninitialized_fill_n(_ForwardIterator __first, _Size __n, const _T1 &__x, _T2 *) {
        typedef typename __type_traits<_T2>::is_POD_type _Is_POD;
        return __uninitialized_fill_n_aux(__first, __n, __x, _Is_POD());
    }

    template<class _ForwardIterator, class _Size, class _T>
    inline _ForwardIterator uninitialized_fill_n(_ForwardIterator __first, _Size __n, const _T &__x) {
        return __uninitialized_fill_n(__first, __n, __x, value_type(__first));
    }

__STL_END_NAMESPACE

#endif