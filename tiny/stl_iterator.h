/*
 *
 * Creadted by i3roNy@ on 2022/10/17
 *
 * stl_iterator.h定义了STL里的迭代器模板，重载了迭代器相关的运算符
 */

#ifndef BRONYA_STL_ITERATOR_H
#define BRONYA_STL_ITERATOR_H

#include "stl_config.h"
#include "stl_iterator_base.h"

__STL_BEGIN_NAMESPACE

    /* 尾迭代器 */
    template<class _Container>
    class back_insert_iterator {
    protected:
        _Container *container;
    public:
        typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        explicit back_insert_iterator(_Container &__x) : container(&__x) {}

        back_insert_iterator<_Container> &operator=(const typename _Container::value_type &__value) {
            container->push_back(__value);
            return *this;
        }

        back_insert_iterator<_Container> &operator*() {
            return *this;
        }

        back_insert_iterator<_Container> &operator++() {
            return *this;
        }

        back_insert_iterator<_Container> &operator++(int) {
            return *this;
        }
    };

    template<class _Container>
    inline back_insert_iterator<_Container> back_insert(_Container &__x) {
        return back_insert_iterator<_Container>(__x);
    }

    /* 首迭代器 */
    template<class _Container>
    class front_insert_iterator {
    protected:
        _Container *container;
    public:
        typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        explicit front_insert_iterator(_Container &__x) : container(&__x) {}

        front_insert_iterator<_Container> &operator=(const typename _Container::value_type &__value) {
            container->push_front(__value);
            return *this;
        }

        front_insert_iterator<_Container> &operator*() {
            return *this;
        }

        front_insert_iterator<_Container> &operator++() {
            return *this;
        }

        front_insert_iterator<_Container> &operator++(int) {
            return *this;
        }
    };

    template<class _Container>
    inline front_insert_iterator<_Container> front_insert(_Container &__x) {
        return front_insert_iterator<_Container>(__x);
    }

    /* 中间迭代器 */
    template<class _Container>
    class insert_iterator {
    protected:
        _Container *container;
        typename _Container::iterator iter;
    public:
        typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        insert_iterator(_Container &__x, typename _Container::iterator __i) : container(&__x), iter(__i) {}

        insert_iterator<_Container> &operator=(const typename _Container::value_type &__value) {
            iter = container->insert(iter, __value);
            ++iter;
            return *this;
        }

        insert_iterator<_Container> &operator*() {
            return *this;
        }

        insert_iterator<_Container> &operator++() {
            return *this;
        }

        insert_iterator<_Container> &operator++(int) {
            return *this;
        }
    };

    template<class _Container, class _Iterator>
    inline insert_iterator<_Container> insert(_Container &__x, _Iterator &__i) {
        typedef typename insert_iterator<_Container>::iterator __iter;
        return insert_iterator<_Container>(__x, __iter(__i));
    }

    /* 反向迭代器 */
    template<class _Iterator>
    class reverse_iterator {
    protected:
        _Iterator cur;
    public:
        typedef typename iterator_traits<_Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<_Iterator>::value_type value_type;
        typedef typename iterator_traits<_Iterator>::difference_type difference_type;
        typedef typename iterator_traits<_Iterator>::pointer pointer;
        typedef typename iterator_traits<_Iterator>::reference reference;

        typedef reverse_iterator<_Iterator> _Self;
    public:
        reverse_iterator() {}
        
        explicit reverse_iterator(_Iterator __x) : cur(__x) {}

        reverse_iterator(const _Self &__x) : cur(__x.cur) {}

        template<class _Iter>
        reverse_iterator(const reverse_iterator<_Iter> &__other) : cur(__other.base()) {}

        _Iterator base() const {
            return cur;
        }

        reference operator*() const {
            _Iterator __tmp = cur;
            return *--__tmp;
        }

        pointer operator->() const {
            return &(operator*());
        }

        _Self &operator++() {
            --cur;
            return *this;
        }

        _Self operator++(int) {
            _Self __tmp = *this;
            --cur;
            return __tmp;
        }

        _Self &operator--() {
            ++cur;
            return *this;
        }

        _Self operator--(int) {
            _Self __tmp = *this;
            ++cur;
            return __tmp;
        }

        _Self operator+(difference_type __n) const {
            return _Self(cur - __n);
        }

        _Self operator-(difference_type __n) const {
            return _Self(cur + __n);
        }

        _Self &operator+=(difference_type __n) const {
            cur -= __n;
            return *this;
        }

        _Self &operator-=(difference_type __n) const {
            cur += __n;
            return *this;
        }

        reference operator[](difference_type __n) const {
            return *(*this + __n);
        }
    };

    template<class _Iterator>
    typename reverse_iterator<_Iterator>::difference_type
    operator-(const reverse_iterator<_Iterator> &__lhs, const reverse_iterator<_Iterator> &__rhs) {
        return (__rhs.base() - __lhs.base());
    }

    template<class _Iterator>
    typename reverse_iterator<_Iterator>::difference_type
    operator+(typename reverse_iterator<_Iterator>::difference_type __n, const reverse_iterator<_Iterator> &__x) {
        return reverse_iterator<_Iterator>(__x.base() - __n);
    }

    template<class _Iterator>
    inline bool operator==(const reverse_iterator<_Iterator> &__lhs, const reverse_iterator<_Iterator> &__rhs) {
        return (__lhs.base() == __rhs.base());
    }

    template<class _Iterator>
    inline bool operator!=(const reverse_iterator<_Iterator> &__lhs, const reverse_iterator<_Iterator> &__rhs) {
        return !(__lhs == __rhs);
    }

    template<class _Iterator>
    inline bool operator<(const reverse_iterator<_Iterator> &__lhs, const reverse_iterator<_Iterator> &__rhs) {
        return (__rhs.base() < __lhs.base());
    }

    template<class _Iterator>
    inline bool operator>(const reverse_iterator<_Iterator> &__lhs, const reverse_iterator<_Iterator> &__rhs) {
        return (__rhs < __lhs);
    }

    template<class _Iterator>
    inline bool operator<=(const reverse_iterator<_Iterator> &__lhs, const reverse_iterator<_Iterator> &__rhs) {
        return !(__rhs < __lhs);
    }

    template<class _Iterator>
    inline bool operator>=(const reverse_iterator<_Iterator> &__lhs, const reverse_iterator<_Iterator> &__rhs) {
        return !(__rhs > __lhs);
    }

__STL_END_NAMESPACE

#endif