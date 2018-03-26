//
// Created by 启翔 张 on 2017/12/27.
//

#ifndef PROJECT_COMMENT_HPP
#define PROJECT_COMMENT_HPP

#define DONKEY_EXPORT
#define DEBUG
#define DONKEY_POLICY

#define THROW_EXCEPTION_AGAIN throw
#define DONKEY_TEMPLATE_VIS __attribute__ ((__visibility__("default")))
#define DONKEY_ALWAYS_INLINE __attribute__ ((__visibility__("hidden"), __always_inline__))



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
  }  \
private:\
  __classname__()

#define ENABLE_COMPARATOR(__classsname__)\
bool operator==(const __classsname__& lhs,const __classsname__& rhs);\
bool operator>=(const __classsname__& lhs,const __classsname__& rhs);\
bool operator<=(const __classsname__& lhs,const __classsname__& rhs);\
bool operator>(const __classsname__& lhs,const __classsname__& rhs);\
bool operator<(const __classsname__& lhs,const __classsname__& rhs)


#define _CONSTANT_RETURN __attribute__((const)) //函数不会反回
#define _NO_NULL(pos, ...) __attribute__((nonnull(pos, __VA_ARGS__)))  //参数非NULL检查

#define _CONSTRUCTOR __attribute__((constructor))  //main之前调用
#define _CONSTRUCTOR_PRIORITY(P) __attribute__((constructor(P))  //main之前调用(带优先级)
#define _DESTRUCTOR __attribute__((destructor))  //main之后调用
#define _DESTRUCTOR_PRIORITY(P) __attribute__((destructor(P)))  //main之后调用(带优先级)

#define _NO_RETURN __attribute__((noreturn))  //相同调用仅计算一次
#define _UNAVALIABLE __attribute__((unavailable))  //禁止使用
#define _DEPRECATED __attribute__((deprecated)) //不建议使用
#define _FORMAT(type, ...) __attribute__((format( type, __VA_ARGS__ ))) //格式化字符串检查
#define _CLEANUP(clean_func) __attribute__((cleanup(clean_func)))  //变量离开作用域后调用clean函数
#define _ALIGNED(m) __attribute__((aligned(m)))
#define _PACKED __attribute__((__packed__))
#define _ALIAS(f) __attribute__((alias(f)))
#define _WEAK __attribute__((weak))


#endif //PROJECT_COMMENT_HPP
