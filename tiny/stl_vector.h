/*
 *
 * Creadted by i3roNy@ on 2022/10/19
 *
 * stl_vector.h是一个序列容器，vector与array相似，但vector是一个动态空间，随着元素的加入，内部机制会自动扩充空间以容纳新元素
 * 
 * 提供了以下的接口：
 * - 迭代器接口：
 *  - begin()
 *  - end()
 *  - r_begin()
 *  - r_end()
 *  - c_begin()
 *  - c_begin()
 * - 容量修改接口：
 *  - 
 * 
 */

#ifndef BRONYA_STL_VECTOR_H
#define BRONYA_STL_VECTOR_H

#include "stl_config.h"
#include "stl_allocator.h"
#include "stl_construct.h"
#include "stl_iterator.h"
#include "stl_uninitialized.h"

__STL_BEGIN_NAMESPACE

    template<class _T, class _Alloc>
    class _Vector_Base {
    public:
        typedef _Alloc allocator_type;

        allocator_type get_allocater() const {
            return allocator_type();
        }

        _Vector_Base(const _Alloc &) : __begin(0), __end(0), __cap(0) {}
        _Vector_Base(size_t __n, const _Alloc &) : __begin(0), __end(0), __cap(0) {
            __begin = _allocate(__n);
            __end   = __begin;
            __cap   = __begin + __n;
        }
        
        ~_Vector_Base() { _deallocate(__begin, __cap - __begin); }
    protected:
        _T *__begin; // 表示目前使用空间的头部
        _T *__end;   // 表示目前使用空间的尾部
        _T *__cap;   // 表示目前储存空间的尾部

        typedef simple_alloc<_T, _Alloc> _data_allocateor;

        _T *_allocate(size_t __n) {
            return _data_allocateor::allocate(__n);
        }

        void _deallocate(_T *__p, size_t __n) {
            _data_allocateor::deallocate(__p, __n);
        }
    };

    template<class _T, class _Alloc = alloc>
    class vector : protected _Vector_Base<_T, _Alloc> {
    private:
        typedef _Vector_Base<_T, _Alloc> _Base;
    public:
        /* vector 嵌套型别定义 */
        typedef _T value_type;

        typedef value_type                          *pointer;
        typedef value_type                          *iterator;
        typedef value_type                          &reference;
        typedef reverse_iterator<iterator>          __reverse_iterator;

        typedef const value_type                    *const_pointer;
        typedef const value_type                    *const_iterator;
        typedef const value_type                    &const_reference;
        typedef reverse_iterator<const_iterator>    __const_reverse_iterator;

        typedef size_t                              size_type;
        typedef ptrdiff_t                           difference_type;

        typedef typename _Base::allocator_type allocator_type;

        allocator_type get_allocater() const { return _Base::get_allocater(); }
    protected:
        using _Base::__begin;
        using _Base::__end;
        using _Base::__cap;

        using _Base::_allocate;
        using _Base::_deallocate;
    protected:
        void _insert_aux(iterator __position);
        void _insert_aux(iterator __position, const _T &__x);
    public:

        explicit vector(const allocator_type &__a = allocator_type()) : _Base(__a) {}
        vector(size_type __n, const _T &__value, const allocator_type &__a = allocator_type()) : _Base(__n, __a) {
            uninitialized_fill_n(__begin, __n, __value);
        }

        explicit vector(size_type __n) : _Base(__n, allocator_type()) {
            uninitialized_fill_n(__begin, __n, _T());
        }

        vector(const vector<_T, _Alloc> &__x) : _Base(__x.size(), __x.get_allocater()) {
            uninitialized_copy(__x.begin(), __x.__end(), __begin);
        }

        ~vector() { destroy(__begin, __end); }

    public:
        /* 迭代器相关操作 */
        iterator     begin()             { return __begin; }
        iterator     end()               { return __end; }
        iterator     r_begin()           { return __reverse_iterator(end()); }
        iterator     r_end()             { return __reverse_iterator(begin()); }

        const_iterator c_begin()  const  { return __begin; }
        const_iterator c_end()    const  { return __end; }
        const_iterator c_rbegin() const  { return __reverse_iterator(end()); }
        const_iterator c_rend()   const  { return __reverse_iterator(begin()); }

        /* 容量相关操作 */
        size_type    size()       const  { return size_type(c_end() - c_begin()); }
        size_type    max_size()   const  { return size_type(-1) / sizeof(_T); }
        size_type    capacity()   const  { return size_type(__cap - begin()); }
        bool         empty()      const  { return begin() == end(); }

        /* 访问元素相关操作 */
        void _Range_check(size_type __n) const {
            if(__n >= size()) {
                throw;
            }
        }

        reference operator[](size_type __n) {
            return *(begin() + __n);
        }

        reference front() {
            return *begin();
        }

        reference back() {
            return *(end() - 1);
        }

        reference at(size_type __n) {
            _Range_check(__n);
            return (*this)[__n];
        }

        const_reference operator[](size_type __n) const {
            return *(begin() + __n);
        }

        const_reference front() const {
            return *begin();
        }

        const_reference back() const {
            return *(end() - 1);
        }

        const_reference at(size_type __n) const {
            _Range_check(__n);
            return (*this)[__n];
        }

        /* 修改容器相关操作 */
        void push_back(const _T &__value) {
            if(__end != __cap) {
                construct(__end, __value);
                ++__end;
            }
            else {
                _insert_aux(end(), __value);    
            }
        }

        void push_back() {
            if(__end != __cap) {
                construct(__end);
                ++__end;
            }
            else {
                _insert_aux(end());
            }
        }

        void swap(vector<_T, _Alloc> &__x) {
            if(this != &__x) {
                bronya_stl::swap(__begin, __x.__begin);
                bronya_stl::swap(__end, __x.__end);
                bronya_stl::swap(__cap, __x.__cap);
            }
        }






    };

    template<class _T, class _Alloc>
    void vector<_T, _Alloc>::_insert_aux(iterator __position, const _T &__x) {
        if(__end != __cap) {
            construct(__end, *(__end - 1));
            ++__end;
            _T __x_copy = __x;
            copy_backward(__position, __end - 2, __end - 1);
            *__position = __x_copy;
        }
        else {
            const size_type __old_size = size();
            const size_type __len = __old_size != 0 ? 2 * __old_size : 1;
            iterator __new_begin = _allocate(__len);
            iterator __new_end = __new_begin;
            try {
                __new_end = uninitialized_copy(__begin, __position, __new_begin);
                construct(__new_end, __x);
                ++__new_end;
                __new_end = uninitialized_copy(__position, __end, __new_end);
            }
            catch(...) {
                destroy(__new_begin, __new_end);
                _deallocate(__new_begin, __len);
                throw;
            }
            destroy(begin(), end());
            _deallocate(__begin, __cap - __begin);
            __begin = __new_begin;
            __end   = __new_end;
            __cap   = __begin + __len;
        }
    }

    template<class _T, class _Alloc>
    void vector<_T, _Alloc>::_insert_aux(iterator __position) {
        if(__end != __cap) {
            construct(__end, *(__end - 1));
            ++__end;
            copy_backward(__position, __end - 2, __end - 1);
            *__position = _T();
        }
        else {
            const size_type __old_size = size();
            const size_type __len = __old_size != 0 ? 2 * __old_size : 1;
            iterator __new_begin = _allocate(__len);
            iterator __new_end = __new_begin;
            try {
                __new_end = uninitialized_copy(__begin, __position, __new_begin);
                construct(__new_end);
                ++__new_end;
                __new_end = uninitialized_copy(__position, __end, __new_end);
            }
            catch(...) {
                destroy(__new_begin, __new_end);
                _deallocate(__new_begin, __len);
                throw;
            }
            destroy(begin(), end());
            _deallocate(__begin, __cap - __begin);
            __begin = __new_begin;
            __end   = __new_end;
            __cap   = __begin + __len;
        }
    }

__STL_END_NAMESPACE

#endif