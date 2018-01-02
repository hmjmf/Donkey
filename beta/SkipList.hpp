/*
 *  SkipList
 *  My Website           http://zhangqixiang.cn
 *  My Github            https://github.com/hmjmf
 *  Email                zqx5449@gmail.com
 *
 *  Created by 启翔 张 (QiXiang Zhang) on 2018/1/2.
 *  Copyright (c) 2018 . All rights reserved.
 */

#ifndef PROJECT_SKIPLIST_HPP
#define PROJECT_SKIPLIST_HPP


#include <iosfwd> // for forward declaration of vector
#include <type_traits>
#include <climits>
#include <limits>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include "../include/donkey/comment.hpp"





namespace Donkey{

template <class Tp, class Allocator >
class DONKEY_TEMPLATE_VIS base_filter_{
protected:
    typedef Tp                                          value_type;
    typedef Allocator                                   allocator_type;
    typedef std::allocator_traits<allocator_type>       allocator_traits_;
    typedef value_type&                                 reference;
    typedef const value_type&                           const_reference;
    typedef typename allocator_traits_::size_type       size_type;
    typedef typename allocator_traits_::difference_type difference_type;
    typedef typename allocator_traits_::pointer         pointer;
    typedef typename allocator_traits_::const_pointer   const_pointer;

    typedef pointer                                     iterator;
    typedef const_pointer                               const_iterator;

    pointer                                             begin_;
    pointer                                             end_;
    std::__compressed_pair<pointer, allocator_type>     end_cap_;

    DONKEY_INLINE_VISIBILITY allocator_type& alloc_() _NOEXCEPT{
        return end_cap_.second();
    }
public:
    virtual ~base_filter_();
    virtual void insert(const Tp& key) = 0;
    virtual bool contains(const Tp& key) const = 0;
};


template <class Tp, class Allocator=std::allocator<Tp>>
class DONKEY_TEMPLATE_VIS SkipList: public base_filter_<Tp, Allocator>{
private:
    typedef base_filter_<Tp, Allocator>             base_;
    typedef std::allocator<Tp>                      default_allocator_type_;
public:
    typedef SkipList                                self;
    typedef Tp                                      value_type;
    typedef Allocator                               allocator_type;
    typedef typename base_::allocator_traits_       alloc_traits;
    typedef typename base_::reference               reference;
    typedef typename base_::const_reference         const_reference;
    typedef typename base_::size_type               size_type;
    typedef typename base_::difference_type         difference_type;
    typedef typename base_::pointer                 pointer;
    typedef typename base_::const_pointer           const_pointer;
    typedef std::__wrap_iter<pointer>               iterator;
    typedef std::__wrap_iter<const_pointer>         const_iterator;
    typedef std::reverse_iterator<iterator>         reverse_iterator;
    typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;

    static_assert((std::is_same<typename allocator_type::value_type, value_type>::value),
                  "Allocator::value_type must be same type as value_type");


    SkipList() _NOEXCEPT(std::is_nothrow_default_constructible<allocator_type>::value);

};


}
#endif //PROJECT_SKIPLIST_HPP
