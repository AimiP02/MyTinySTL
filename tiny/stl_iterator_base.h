/*
 *
 * Creadted by i3roNy@ on 2022/10/17
 *
 * stl_iterator_base.h定义了STL里iterator的基础模板，包括特性提取和移动等
 */

#ifndef BRONYA_STL_STL_ITERATOR_BASE_H
#define BRONYA_STL_STL_ITERATOR_BASE_H

#include <cstddef>
#include "stl_config.h"
#include "type_traits.h"

__STL_BEGIN_NAMESPACE
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_iterator_tag : public input_iterator_tag{};
    struct bidirectional_iterator_tag : public forward_iterator_tag{};
    struct random_access_iterator_tag : public bidirectional_iterator_tag{};

    template<class _T, class _Distance>
    struct input_iterator {
        typedef input_iterator_tag  iterator_category;
        typedef _T                  value_type;
        typedef _Distance           difference_type;
        typedef _T                  *pointer;
        typedef _T                  &reference;
    };
    struct output_iterator {
        typedef output_iterator_tag     iterator_category;
        typedef void                    value_type;
        typedef void                    difference_type;
        typedef void                    pointer;
        typedef void                    reference;
    };
    template<class _T, class _Distance>
    struct forward_iterator {
        typedef forward_iterator_tag    iterator_category;
        typedef _T                      value_type;
        typedef _Distance               difference_type;
        typedef _T                      *pointer;
        typedef _T                      &reference;
    };
    template<class _T, class _Distance>
    struct bidirectional_iterator {
        typedef bidirectional_iterator_tag  iterator_category;
        typedef _T                          value_type;
        typedef _Distance                   difference_type;
        typedef _T                          *pointer;
        typedef _T                          &reference;
    };
    template<class _T, class _Distance>
    struct random_access_iterator {
        typedef random_access_iterator_tag  iterator_category;
        typedef _T                          value_type;
        typedef _Distance                   difference_type;
        typedef _T                          *pointer;
        typedef _T                          &reference;
    };
    template<class _Category, class _T, class _Distance = ptrdiff_t, class _Pointer = _T *, class _Reference = _T &>
    struct iterator {
        typedef _Category   iterator_category;
        typedef _T          value_type;
        typedef _Distance   difference_type;
        typedef _Pointer    pointer;
        typedef _Reference  reference;
    };
    template<class _Iterator>
    struct iterator_traits {
        typedef typename _Iterator::iterator_category   iterator_category;
        typedef typename _Iterator::value_type          value_type; 
        typedef typename _Iterator::difference_type     difference_type;
        typedef typename _Iterator::pointer             pointer;
        typedef typename _Iterator::reference           reference;
    };

    /* 指针类型的偏特化 */
    template<class _T>
    struct iterator_traits<_T *> {
        typedef random_access_iterator_tag  iterator_category;
        typedef _T                          value_type;
        typedef ptrdiff_t                   difference_type;
        typedef _T                          *pointer;
        typedef _T                          &reference;
    };

    template<class _T>
    struct iterator_traits<const _T *> {
        typedef random_access_iterator_tag  iterator_category;
        typedef _T                          value_type;
        typedef ptrdiff_t                   difference_type;
        typedef _T                          *pointer;
        typedef _T                          &reference;
    };

    template<class _Iter>
    inline typename iterator_traits<_Iter>::iterator_category __iterator_category(const _Iter &) {
        typedef typename iterator_traits<_Iter>::iterator_category _Category;
        return _Category();
    }

    template<class _Iter>
    inline typename iterator_traits<_Iter>::iterator_category iterator_category(const _Iter &__i) {
        return __iterator_category(__i);
    }

    template<class _Iter>
    inline typename iterator_traits<_Iter>::difference_type *__difference_type(const _Iter &) {
        return static_cast< typename iterator_traits<_Iter>::difference_type * >(0);
    }

    template<class _Iter>
    inline typename iterator_traits<_Iter>::difference_type *difference_type(const _Iter &__i) {
        return __difference_type(__i);
    }

    template<class _Iter>
    inline typename iterator_traits<_Iter>::value_type *__value_type(const _Iter &) {
        return static_cast< typename iterator_traits<_Iter>::value_type * >(0);
    }

    template<class _Iter>
    inline typename iterator_traits<_Iter>::value_type *value_type(const _Iter &__i) {
        return __value_type(__i);
    }

    template<class _InputIterator, class _Distance>
    inline void __distance(_InputIterator __first, _InputIterator __last, _Distance &__n, input_iterator_tag) {
        while(__first != __last) {
            ++__first;
            ++__n;
        }
    }

    template<class _RandomAccessIterator, class _Distance>
    inline void __distance(_RandomAccessIterator __first, _RandomAccessIterator __last, _Distance &__n, random_access_iterator_tag) {
        __n += __last - __first;
    }

    template<class _InputIterator, class _Distance>
    inline void distance(_InputIterator __first, _InputIterator __last, _Distance &__n) {
        __distance(__first, __last, __n, iterator_category(__first));
    }

// #define __STL_CLASS_PARTIAL_SPECIALIZATION
#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION

    template<class _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type 
    __distance(_InputIterator __first, _InputIterator __last, input_iterator_tag) {
        typename iterator_traits<_InputIterator>::difference_type __n = 0;
        while(__first != __last) {
            ++__first;
            ++__n;
        }
        return __n;
    }

    template<class _RandomAccessIterator>
    inline typename iterator_traits<_RandomAccessIterator>::difference_type 
    __distance(_RandomAccessIterator __first, _RandomAccessIterator __last, random_access_iterator_tag) {
        return (__last - __first);
    }

    template<class _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type
    distance(_InputIterator __first, _InputIterator __last) {
        typedef typename iterator_traits<_InputIterator>::iterator_catego _Category;
        __distance(__first, __last, _Category());
    }
#endif

    template<class _InputIterator, class _Distance>
    inline void __advance(_InputIterator &__i, _Distance __n, input_iterator_tag) {
        while(__n--) {
            ++__i;
        }
    }

    template<class _BidirectionalIterator, class _Distance>
    inline void __advance(_BidirectionalIterator &__i, _Distance __n, bidirectional_iterator_tag) {
        if(__n > 0) {
            while(__n--) {
                ++__i;
            }
        }
        else {
            while(__n++) {
                --__i;
            }
        }
    }

    template<class _RandomAccessIterator, class _Distance>
    inline void __advance(_RandomAccessIterator &__i, _Distance __n, random_access_iterator_tag) {
        __i += __n;
    }

    template<class _InputIterator, class _Distance>
    inline void advance(_InputIterator &__i, _Distance __n) {
        __advance(__i, __n, __iterator_category(__i));
    }

__STL_END_NAMESPACE

#endif