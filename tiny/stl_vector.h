/*
 *
 * Creadted by i3roNy@ on 2022/10/19
 *
 * stl_vector.h是一个序列容器，vector与array相似，但vector是一个动态空间，随着元素的加入，
 * 内部机制会自动扩充空间以容纳新元素
 * 
 * 提供了以下的接口：
 * 
 * 
 */

#ifndef BRONYA_STL_VECTOR_H
#define BRONYA_STL_VECTOR_H

#include "stl_config.h"
#include "stl_allocator.h"
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

        _Vector_Base(const _Alloc &) : _b_begin(0), _b_end(0), _b_cap(0) {}
        _Vector_Base(size_t __n, const _Alloc &) : _b_begin(0), _b_end(0), _b_cap(0) {
            _b_begin = _b_allocate(__n);
            _b_end   = _b_begin;
            _b_cap   = _b_begin + __n;
        }
    protected:
        _T *_b_begin; // 表示目前使用空间的头部
        _T *_b_end;   // 表示目前使用空间的尾部
        _T *_b_cap;   // 表示目前储存空间的尾部

        typedef simple_alloc<_T, _Alloc> _b_data_allocateor;

        _T *_b_allocate(size_t __n) {
            return _b_data_allocateor::allocate(__n);
        }

        _T *_b_deallocate(_T *__p, size_t __n) {
            _b_data_allocateor::deallocate(__p, __n);
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
        using _Base::__allocate;
        using _Base::__deallocate;
    protected:
        void _b_insert_aux(iterator __position);
        void _b_insert_aux(iterator __position, const _T &__x);
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
        size_type    size()       const  { return size_type(end() - begin()); }
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
        




    };

__STL_END_NAMESPACE

#endif