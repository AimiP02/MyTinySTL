/*
 *
 * Creadted by i3roNy@ on 2022/10/17
 *
 */

#ifndef BRONYA_STL_STL_ITERATOR_BASE_H
#define BRONYA_STL_STL_ITERATOR_BASE_H

#include <stddef.h>
#include "stl_config.h"
#include "type_traits.h"

__STL_BEGIN_NAMESPACE
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_iterator_tag : public input_iterator_tag{};
    struct bidirectional_iterator_tag : forward_iterator_tag{};
    struct random_access_iterator_tag : bidirectional_iterator_tag{};

    template<class _T, class _Distance>
    struct input_iterator {
        typedef input_iterator_tag iterator_category;
        typedef _T value_type;
        typedef _Distance difference_type;
        typedef _T *pointer;
        typedef _T &reference;
    };
    struct output_iterator {
        typedef input_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;
    };
    template<class _T, class _Distance>
    struct bidirectional_iterator {
        typedef input_iterator_tag iterator_category;
        typedef _T value_type;
        typedef _Distance difference_type;
        typedef _T *pointer;
        typedef _T &reference;
    };
    template<class _T, class _Distance>
    struct random_access_iterator {
        typedef input_iterator_tag iterator_category;
        typedef _T value_type;
        typedef _Distance difference_type;
        typedef _T *pointer;
        typedef _T &reference;
    };
    template<class _Category, class _T, class _Distance = ptrdiff_t, class _Pointer = _T *, class _Reference = _T &>
    struct iterator {
        typedef _Category iterator_category;
        typedef _T value_type;
        typedef _Distance difference_type;
        typedef _Pointer pointer;
        typedef _Reference reference;
    };
    template<class _Iterator>
    struct iterator_traits {
        typedef typename _Iterator::iterator_category iterator_category;
        typedef typename _Iterator::value_type value_type; 
        typedef typename _Iterator::difference_type difference_type;
        typedef typename _Iterator::pointer pointer;
        typedef typename _Iterator::reference reference;
    };

    /* 指针类型的偏特化 */
    template<class _T>
    struct iterator_traits<_T *> {
        
    };

__STL_END_NAMESPACE

#endif