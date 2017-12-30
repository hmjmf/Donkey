//
// Created by 启翔 张 on 2017/12/29.
//

#ifndef PROJECT_RANGE_HPP
#define PROJECT_RANGE_HPP


namespace Donkey{

template <typename type>
class range_iterator{
public:
    explicit range_iterator(type val):value_(val){}

    bool operator!=(const range_iterator<type>& rhs) const {
        return (this->get_value()) != (rhs.get_value());
    }

    type operator*() const {
        return this->get_value();
    }

    const range_iterator& operator++() {
        ++value_;
        return *this;
    }
    const range_iterator& operator--() {
        --value_;
        return *this;
    }

private:
    type get_value() const {
        return value_;
    }
    type value_;
};


template <typename type>
class Range{
public:
    Range(type begin_v, type end_v)
            :begin_value_(begin_v), end_value_(end_v){
        if(begin_value_ > end_value_){
            begin_value_ = end_value_;
        }
    }


    range_iterator<type> begin() const {
        return range_iterator<type>(begin_value_);
    }
    range_iterator<type> end() const {
        return range_iterator<type>(end_value_ );
    }
private:
    type begin_value_;
    type end_value_;
};


}



#endif //PROJECT_RANGE_HPP
