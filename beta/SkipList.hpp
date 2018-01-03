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
#include "../include/donkey/util/random.hpp"





namespace Donkey{
/********************  skip_list_node_base  ***********************/
struct skip_list_node_base{
public:
    skip_list_node_base(uint height):KHeight(height){
        CHECK_GT(height, 0) << "height must > 0";
    };
    skip_list_node_base* next(uint level){
        CHECK_LT(level, KHeight) << "level must < height";
        return next_[level];
    }
    const uint KHeight;
    skip_list_node_base* next_[] = {nullptr};
};

/********************  skip_list_nod  ***********************/
template <typename Tp>
struct DONKEY_TEMPLATE_VIS skip_list_node : public skip_list_node_base{
    typedef Tp                      value_type;
    typedef value_type*             pointer;
    typedef const pointer           const_pointer;
    typedef value_type&             reference;
    typedef const reference         const_reference;

    skip_list_node() = delete;
    skip_list_node(const_reference data, uint height):
            data_(data),
            skip_list_node_base(height){}

    pointer valptr() noexcept {
        return &data_;
    }
    const_pointer valptr() const noexcept {
        return &data_;
    }
private:
    const_reference data_;
};

/********************  skip_list_iterator  ***********************/
template <typename Tp>
struct DONKEY_TEMPLATE_VIS skip_list_iterator{
    typedef Tp                                  value_type;
    typedef value_type*                         pointer;
    typedef value_type&                         reference;
    typedef const reference                     const_reference;

    typedef skip_list_node<Tp>                  node_type;
    typedef skip_list_iterator<Tp>              self_type;
    typedef std::forward_iterator_tag           iterator_category;

    skip_list_iterator() noexcept : node_() {}
    explicit skip_list_iterator(skip_list_node_base* n) noexcept :node_(n){}

    reference operator*() const noexcept {
        return *static_cast<node_type*>(this->node_)->valptr();
    }
    pointer operator->() const noexcept {
        return static_cast<node_type*>(this->node_)->valptr();
    }
    self_type& operator++() noexcept {
        node_ = node_ -> next(0);
        return *this;
    }
    self_type operator++(int) noexcept {
        self_type tmp(*this);
        node_ = node_->next(0);
        return tmp;
    }
    bool operator==(const self_type& rhs) const noexcept {
        return node_ == rhs.node_;
    }
    bool operator!=(const self_type& rhs) const noexcept {
        return node_ != rhs.node_;
    }
    self_type next_() const noexcept {
        if(node_){
            return skip_list_iterator(node_->next(0));
        } else {
            return skip_list_iterator(nullptr);
        }
    }
    skip_list_node_base* node_;
};


/********************  skip_list_const_iterator  ***********************/
template<typename Tp>
struct DONKEY_TEMPLATE_VIS skip_list_const_iterator{
    typedef Tp                                  value_type;
    typedef value_type*                         pointer;
    typedef value_type&                         reference;
    typedef const reference                     const_reference;
    typedef skip_list_iterator                  iterator;

    typedef skip_list_node<Tp>                  node_type;
    typedef skip_list_const_iterator<Tp>        self_type;
    typedef std::forward_iterator_tag           iterator_category;

    skip_list_const_iterator() noexcept : node_() {}
    explicit skip_list_const_iterator(skip_list_node_base* n) noexcept :node_(n){}
    skip_list_const_iterator(iterator iter) noexcept : node_(iter.node_){}

    reference operator*() const noexcept {
        return *static_cast<node_type*>(this->node_)->valptr();
    }
    pointer operator->() const noexcept {
        return static_cast<node_type*>(this->node_)->valptr();
    }
    self_type& operator++() noexcept {
        node_ = node_ -> next(0);
        return *this;
    }
    self_type operator++(int) noexcept {
        self_type tmp(*this);
        node_ = node_->next(0);
        return tmp;
    }
    bool operator==(const self_type& rhs) const noexcept {
        return node_ == rhs.node_;
    }
    bool operator!=(const self_type& rhs) const noexcept {
        return node_ != rhs.node_;
    }
    self_type next_() const noexcept {
        if(node_){
            return skip_list_const_iterator(node_->next(0));
        } else {
            return skip_list_const_iterator(nullptr);
        }
    }
    skip_list_node_base* node_;
};

template <typename Tp>
DONKEY_ALWAYS_INLINE inline bool operator==(const skip_list_iterator<Tp>& lhs,
                                            const skip_list_const_iterator<Tp>& rhs) noexcept {
    return lhs.node_ == rhs.node_;
}
template <typename Tp>
DONKEY_ALWAYS_INLINE inline bool operator!=(const skip_list_iterator<Tp>& lhs,
                                            const skip_list_const_iterator<Tp>& rhs) noexcept {
    return lhs.node_ != rhs.node_;
}

/********************  skip_list_base  ***********************/
template <class Tp, class Allocator>
struct DONKEY_TEMPLATE_VIS skip_list_base{
protected:
    typedef std::__allocator_traits_rebind<Allocator, Tp>                  Tp_allocator_type;
    typedef std::allocator_traits<Tp_allocator_type>                       alloc_traits;
    typedef std::__allocator_traits_rebind<Allocator, skip_list_node<Tp>>  node_allocator_type;
    typedef std::allocator_traits<node_allocator_type>                     node_allocator_traits;
    typedef node_allocator_traits::pointer                                 pointer;


    struct skip_list_impl : public node_allocator_type{
        skip_list_node_base head_;
        uint max_height_;

        skip_list_impl(uint height):node_allocator_type(), max_height_(height){}

        skip_list_impl(const node_allocator_type& a, uint height):
                node_allocator_type(a), max_height_(height){}

        skip_list_impl(node_allocator_type&& a, uint height):
                node_allocator_type(std::move(a)), max_height_(height){}
    };

    skip_list_impl impl_;

public:
    typedef skip_list_iterator<Tp>                      iterator;
    typedef skip_list_const_iterator<Tp>                const_iterator;
    typedef skip_list_node<Tp>                          node_type;

    node_allocator_type& get_node_allocator() noexcept {
        return this->impl_;
    }
    const node_allocator_type& get_node_allocator() const noexcept {
        return this->impl_;
    }

    skip_list_base(uint height) : impl_(height){}
    skip_list_base(skip_list_base&& sl, node_allocator_type&&a);
    skip_list_base(skip_list_base&& sl, uint height) : impl_(std::move(sl.get_node_allocator()), sl.impl_.head_.KHeight){
        CHECK_EQ(this->impl_.head_.KHeight, sl.impl_.head_.KHeight) << "different height";
        for (int i = 0; i < sl.impl_.head_.KHeight; i++){
            this->impl_.head_.next_[i] = sl.impl_.head_.next_[i];
            sl.impl_.head_.next_[i] = nullptr;
        }
    }

    ~skip_list_base(){
        erase_after_(&impl_.head_, nullptr);
    }

protected:
    node_type* get_node(){
        auto ptr = node_allocator_traits::allocate(get_node_allocator(), 1);
        return std::addressof(*ptr);
    }
    template<typename... Args>
    node_type* create_node(Args&&... args){
        node_type* node_ = this->get_node();
        try{
            Tp_allocator_type a(get_node_allocator());
            ::new((void*)node_) node_type;
            alloc_traits::construct(a, node_->valptr(), std::forward<Args>(args)...);

        } catch(...) {
            this->put_node_(node_);
            THROW_EXCEPTION_AGAIN;
        }
        return node_;
    }
    void put_node_(node_type* p)
    {
        auto ptr = std::pointer_traits<ptr_>::pointer_to(*p);
        node_allocator_traits::deallocate(get_node_allocator(), ptr, 1);
    }
    skip_list_node_base* erase_after_(skip_list_node_base* __pos);

    skip_list_node_base* erase_after_(skip_list_node_base* __pos,
                                      skip_list_node_base* __last);
};

/********************  skip_list ***********************/
template<typename Tp, typename Allocator = std::allocator<Tp>>
class skip_list: private skip_list_base<Tp, Allocator>{
private:
    typedef skip_list_base<Tp, Allocator>               base;
    typedef skip_list_node<Tp>                          node_type;
    typedef skip_list_node_base                         node_base_type;
    typedef typename base::Tp_allocator_type            Tp_alloc_type;
    typedef typename base::node_allocator_type          node_allocator_type;
    typedef typename base::node_allocator_traits        node_allocator_traits;
    typedef std::allocator_traits<Tp_allocator_type>    allocator_traits;

public:
    typedef Tp                                          value_type;
    typedef typename allocator_traits::pointer          pointer;
    typedef typename allocator_traits::const_pointer    const_pointer;
    typedef value_type&                                 reference;
    typedef const reference                             const_reference;

    typedef skip_list_iterator<Tp>                      iterator;
    typedef skip_list_const_iterator<Tp>                const_iterator;
    typedef std::size_t                                 size_type;
    typedef std::ptrdiff_t                              difference_type;
    typedef Allocator                                   allocator_type;

/*==============construct==============*/
    explicit skip_list(uint height=12)
    noexcept(std::is_nothrow_default_constructible<node_allocator_type>::value)
    :base(){}

    explicit skip_list(const Allocator& al) noexcept
            :base(node_allocator_type(al)){}

    skip_list(const skip_list& sl, const Allocator& al) noexcept
            :base(node_allocator_type(al)){
        range_initialize(sl.begin(), sl.end());
    }

    ~skip_list() noexcept {}

    skip_list& operator=(const skip_list& sl);

//    skip_list& operator=(const skip_list&& sl)
//    noexcept(std::is_nothrow_move_assignable<node_allocator_traits>::value){
//        constexpr bool move_storage = std::__propagate_on_container_move_assignment<allocator_type>::type;
//    }

//    skip_list& operator=(std::initializer_list<value_type> il)
//    {
//        assign(il);
//        return *this;
//    }

/*==============iterator==============*/
    iterator before_begin() noexcept {
        return iterator(&this->impl_.head_);
    }

    const_iterator before_begin() const noexcept {
        return const_iterator(&this->impl_.head_);
    }

    iterator begin() noexcept {
        return iterator(this->impl_.head_.next(0));
    }
    const_iterator begin() const noexcept {
        return iterator(this->impl_.head_.next(0));
    }

    iterator end() noexcept {
        return iterator(0);
    }

    const_iterator end() const noexcept {
        return iterator(0);
    }

    const_iterator
    cbegin() const noexcept {
        return const_iterator(this->impl_.head_.next(0));
    }

    const_iterator cbefore_begin() const noexcept {
        return const_iterator(&this->impl_.head_);
    }

    const_iterator cend() const noexcept{
        return const_iterator(0);
    }

    bool empty() const noexcept {
        return this->impl_.head_.next(0) == 0;
    }

    reference front() {
        node_type* front = static_cast<node_type*>(this->impl_.head_.next(0));
        return *front->valptr();
    }

    const_reference front() const {
        node_type* front = static_cast<node_type*>(this->impl_.head_.next(0));
        return *front->valptr();
    }

/*==============impl==============*/
    void insert(const_reference key);

    bool contains(const_reference key) const;

protected:
    node_type* new_node(const_reference key, const uint height);

    uint random_height();

    // Return true if key is greater than the data stored in "n"
    bool key_is_after_node(const_reference key, node_type* n) const;

    // Return the earliest node that comes at or after key.
    // Return NULL if there is no such node.
    //
    // If prev is non-NULL, fills prev[level] with pointer to previous
    // node at "level" for every level in [0..max_height_-1].
    node_type* find_greater_or_equal(const_reference key, node_type** prev) const;

    // Return the latest node with a key < key.
    // Return head_ if there is no such node.
    node_type* find_less_than(const_reference key) const;

    node_type* find_last() const;

    mutable std::mutex mut;
private:
    template<typename InputIterator>
    void range_initialize(InputIterator first, InputIterator last);
};


template<typename Tp>
uint skip_list<Tp>::random_height() {
    // Increase height with probability 1 in kBranching
    static const unsigned int kBranching = 4;
    int height = 1;
    while (height < impl_.max_height_ && ((Donkey::random::uniform(0,1024) % kBranching) == 0)) {
        height++;
    }
    CHECK_GT(height, 0) << " height must > 0";
    CHECK_LE(height, impl_.max_height_) << " height must <= impl_.max_height_" ;
    return height;
}

template<typename Tp>
bool skip_list<Tp>::key_is_after_node(const_reference key, node_type* n) const{
    // NULL n is considered infinite
    return (n != NULL) && (*(n->valptr()) < key);
}
template<typename Tp>
node_type* skip_list<Tp>::find_greater_or_equal(const_reference key, node_type** prev) const{
    skip_list_node_base x = impl_.head_;
    int level = impl_.max_height_ - 1;
    while (true) {
        //CHECK(&x == &impl_.head_ || (*(x.impl_.valptr()) < key);
        node_type* next = static_cast<node_type*>(x.next(level));
        if (key_is_after_node(key, next)) { // next NULL is considered infinite
            // Keep searching in this list
            x = *next;
        } else {
            if (prev != NULL) prev[level] = &x;
            if (level == 0) {
                return next;
            } else {
                level--;
            }
        }
    }
}

template<typename Tp>
void skip_list<Tp>::insert(const_reference key) {
    std::lock_guard<std::mutex> lk(mut);
    node_type* prev[impl_.max_height_];
    node_type* x = find_greater_or_equal(key, prev);

    //x is null means tail
    if (x != NULL && key == x->valptr()) return;
    //CHECK(x == NULL || x == head_ || x->get_key() >= key) << "";

    int height = random_height();

    x = new_node(key, height);
    for (int i = 0; i < height; i++){
        x->next_[i]  = prev[i]->next(i);
        prev[i]->set_next(i,x);
    }

}

template<typename Tp>
bool skip_list<Tp>::contains(const_reference key) const {
    std::lock_guard<std::mutex> lk(mut);
    node_type* x = find_greater_or_equal(key, NULL);
    if(x == impl_.head_) return false;
    return x!=NULL && x->valptr() == key;
}



}
#endif //PROJECT_SKIPLIST_HPP
