/*
 *
 * Creadted by i3roNy@ on 2022/10/18
 *
 * stl_algobase.h定义一些修改已初始化的空间的函数
 * 包括有：
 * - min -> finished
 * - max -> finished
 * - swap -> finished
 * - copy -> finished
 * - copy_backward -> finished
 * - fill -> finished
 * - fill_n -> finished
 * 
 */

#ifndef BRONYA_STL_ALGOBASE_H
#define BRONYA_STL_ALGOBASE_H

#include <string.h>
#include "stl_config.h"
#include "stl_iterator.h"
#include "stl_iterator_base.h"
#include "type_traits.h"

__STL_BEGIN_NAMESPACE

    /* min: 返回较小值 */
    template<class _T>
    const _T &min(const _T &__lhs, const _T &__rhs) {
        return __lhs < __rhs ? __lhs : __rhs;
    }

    template<class _T, class _Compare>
    const _T &min(const _T &__lhs, const _T &__rhs, _Compare __comp) {
        return __comp(__lhs, __rhs) ? __lhs : __rhs;
    }

    /* max: 返回较大值 */
    template<class _T>
    inline const _T &max(const _T &__lhs, const _T &__rhs) {
        return __lhs > __rhs ? __lhs : __rhs;
    }

    template<class _T, class _Compare>
    inline const _T &max(const _T &__lhs, const _T &__rhs, _Compare __comp) {
        return __comp(__lhs, __rhs) ? __lhs : __rhs;
    }

    /*  swap: 交换两个迭代器 */
    template<class _ForwardIterator1, class _ForawrdIterator2, class _T>
    inline void __iter_swap(_ForwardIterator1 __x, _ForawrdIterator2 __y, _T *) {
        _T __tmp = *__x;
        *__x = *__y;
        *__y = __tmp;
    }

    template<class _ForwardIterator1, class _ForawrdIterator2, class _T>
    inline void iter_swap(_ForwardIterator1 __x, _ForawrdIterator2 __y) {
        __iter_swap(__x, __y, __value_type(__x));
    }

    template<class _T>
    inline void swap(_T &__x, _T &__y) {
        _T __tmp = __x;
        __x = __y;
        __y = __tmp;
    }

    /* copy: 将 [ __first, __last ) 区间内的元素复制到 [ __result, __result + (__last - __first) ) */
    template<class _InputIterator, class _OutputIterator, class _Distance>
    inline _OutputIterator __copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result,
                                  input_iterator_tag, _Distance *) {
        for( ; __first != __last; ++__first, ++__result) {
            *__result = *__first;
        }
        return __result;
    }

    template<class _T>
    inline _T *__copy_trivial(const _T *__first, const _T *__last, _T *__result) {
        memmove(__result, __first, (__last - __first) * sizeof(_T));
        return (__result + (__last - __first));
    }

    template<class _T>
    inline _T *__copy_aux2(const _T *__first, const _T *__last, _T *__result, __true_type) {
        return __copy_trivial(__first, __last, __result);
    }

    template<class _InputIterator, class _OutputIterator>
    inline _OutputIterator __copy_aux2(_InputIterator __first, _InputIterator __last, _OutputIterator __result, __true_type) {
        return __copy(__first, __last, __result, iterator_category(__first), distance(__first));
    }

    template<class _InputIterator, class _OutputIterator>
    inline _OutputIterator __copy_aux2(_InputIterator __first, _InputIterator __last, _OutputIterator __result, __false_type) {
        return __copy(__first, __last, __result, iterator_category(__first), distance(__first));
    }

    template<class _InputIterator, class _OutputIterator, class _T>
    inline _OutputIterator __copy_aux(_InputIterator __first, _InputIterator __last, _OutputIterator __result, _T *) {
        typedef typename __type_traits<_T>::has_trivial_assignment_operator _Trivial;
        return __copy_aux2(__first, __last, __result, _Trivial());
    }

    template<class _InputIterator, class _OutputIterator>
    inline _OutputIterator copy(_InputIterator __first, _InputIterator __last, _OutputIterator __result) {
        return __copy_aux(__first, __last, __result, value_type(__first));
    }

    /* copy_backward: 将 [ __first, __last ) 区间内的元素复制到 [ __result - (__first - __last)m __result ) */
    template<class _InputBidirectionalIterator, class _OutputBidirectionalIterator, class _Distance>
    inline _OutputBidirectionalIterator __copy_backward(_InputBidirectionalIterator __first, _InputBidirectionalIterator __last,
                                                        _OutputBidirectionalIterator __result, bidirectional_iterator_tag,
                                                        _Distance *) {
        for( ; __first != __last; --__last, --__result) {
            *__result = *__last;
        }
        return __result;
    }

    template<class _InputBidirectionalIterator, class _OutputBidirectionalIterator, class _Distance>
    inline _OutputBidirectionalIterator __copy_backward(_InputBidirectionalIterator __first, _InputBidirectionalIterator __last,
                                                        _OutputBidirectionalIterator __result, random_access_iterator_tag,
                                                        _Distance *) {
        for(_Distance __n = __last - __first; __n > 0; --__n) {
            *--__result = *--__last;
        }
        return __result;
    }

    template<class _InputBidirectionalIterator, class _OutputBidirectionalIterator, class _BoolType>
    struct __copy_backward_dispatch {
        typedef typename iterator_traits<_InputBidirectionalIterator>::iterator_category _Category;
        typedef typename iterator_traits<_InputBidirectionalIterator>::difference_type _Distance;

        static _OutputBidirectionalIterator
        copy(_InputBidirectionalIterator __first, _InputBidirectionalIterator __last, _OutputBidirectionalIterator __result) {
            return __copy_backward(__first, __last, __result, _Category(), (_Distance *)0);
        }
    };

    template<class _T>
    struct __copy_backward_dispatch<_T *, _T *, __true_type> {
        static _T *copy(const _T *__first, const _T *__last, _T *__result) {
            const ptrdiff_t __num = __last - __first;
            memmove(__result - __num, __first, __num * sizeof(_T));
            return (__result - __num);
        }
    };

    template<class _T>
    struct __copy_backward_dispatch<const _T *, _T *, __true_type> {
        static _T *copy(const _T *__first, const _T *__last, _T *__result) {
            return __copy_backward_dispatch<_T *, _T *, __true_type>::copy(__first, __last, __result);
        }
    };

    template<class _InputBidirectionalIterator, class _OutputBidirectionalIterator>
    inline _OutputBidirectionalIterator copy_backward(_InputBidirectionalIterator __first, _InputBidirectionalIterator __last,
                                                      _OutputBidirectionalIterator __result) {
        typedef typename __type_traits<typename iterator_traits<_OutputBidirectionalIterator>::value_type>::has_trivial_assignment_operator _Trivial;
        return __copy_backward_dispatch<_InputBidirectionalIterator, _OutputBidirectionalIterator, _Trivial>::copy(__first, __last, __result);
    }

    /* fill: 将 [ __first, __last) 区间内的元素全部填充为 __value */
    template<class _ForwardIterator, class _T>
    void fill(_ForwardIterator __first, _ForwardIterator __last, const _T &__value) {
        for( ; __first != __last; ++__first) {
            *__first = __value;
        }
    }

    /* fill_n: 从 __first 之后填充n个值，并返回 __first + n */
    template<class _OutputIterator, class _Size, class _T>
    _OutputIterator fill_n(_OutputIterator __first, _Size __n, const _T &__value) {
        for( ; __n > 0; --__n, ++__first) {
            *__first = __value;
        }
        return __first;
    }

__STL_END_NAMESPACE

#endif