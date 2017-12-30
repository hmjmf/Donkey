//
// Created by 启翔 张 on 2017/12/27.
//

#ifndef PROJECT_COMMENT_HPP
#define PROJECT_COMMENT_HPP

#define DONKEY_EXPORT
#define DEBUG
#define DONKEY_POLICY


#define DISABLE_COPY_AND_ASSIGN(__classname__) \
private:\
    __classname__(const __classname__&);\
    __classname__& operator=(const __classname__&)


#define SINGLETON(__classname__) \
public: \
    inline static __classname__* GetInstance(){ \
        static __classname__ instance; \
        return &instance; \
    } \
private: \
    __classname__(); \
    ~__classname__(); \
    DISABLE_COPY_AND_ASSIGN(__classname__)


#define DEFAULT_SHARE_PTR_FACTORY(__classname__) \
public:\
    static std::shared_ptr<__classname__> create(){ \
        return std::shared_ptr<__classname__>(new __classname__());\
    }   \
private:\
    __classname__()

#define ENABLE_COMPARATOR(__classsname__)\
bool operator==(const __classsname__& lhs,const __classsname__& rhs);\
bool operator>=(const __classsname__& lhs,const __classsname__& rhs);\
bool operator<=(const __classsname__& lhs,const __classsname__& rhs);\
bool operator>(const __classsname__& lhs,const __classsname__& rhs);\
bool operator<(const __classsname__& lhs,const __classsname__& rhs)




#endif //PROJECT_COMMENT_HPP
