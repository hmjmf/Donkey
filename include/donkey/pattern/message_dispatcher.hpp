/*******************************************************
 *  message_dispatcher
 *  My Website           https://zhangqixiang.cn
 *  My Github            https://github.com/hmjmf
 *  Email                zqx5449@gmail.com
 * 
 *  Created by 启翔 张 (QiXiang Zhang) on 2018/3/28.
 *  Copyright (c) 2018 . All rights reserved.
 *******************************************************/



#ifndef PROJECT_MESSAGE_DISPATCHER_HPP
#define PROJECT_MESSAGE_DISPATCHER_HPP

namespace Donkey{
namespace pattern{

//tuple参数的索引序列
template<int...>
struct IndexTuple{};

template<int N, int... Indexes>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...>{};

template<int... indexes>
struct MakeIndexes<0, indexes...> {
  typedef IndexTuple<indexes...> type;
};

template<std::size_t N, typename T1, typename T2>
using pair_type = std::pair<typename std::tuple_element<N, T1>::type,
                            typename std::tuple_element<N, T2>::type>;

template<std::size_t N, typename T1, typename T2>
pair_type<N, T1, T2> pair(const T1& tup1, const T2& tup2) {
  return std::make_pair(std::get<N>(tup1), std::get<N>(tup2));
}

template<int... Indexes, typename T1, typename T2>
auto pairs_helper(IndexTuple<Indexes...>, const T1& tup1, const T2& tup2)
      -> decltype(std::make_tuple(pair<Indexes>(tup1, tup2)...)) {
  return std::make_tuple(pair<Indexes>(tup1, tup2)...);
}

template<typename Tuple1, typename Tuple2>
auto zip_tuple(Tuple1 tup1, Tuple2 tup2)
  -> decltype(
      pairs_helper(typename MakeIndexes<std::tuple_size<Tuple1>::value>::type(),
      tup1, tup2)) {
  static_assert(std::tuple_size<Tuple1>::value == std::tuple_size<Tuple2>::value,
                "tuples should be the same size.");
  return pairs_helper(
      typename MakeIndexes<std::tuple_size<Tuple1>::value>::type(),
      tup1, tup2);
}

template<typename F, typename... Args>
auto apply(F &&f, Args &&... args)->decltype(f(args...)) {
  return std::forward<F>(f)(std::forward<Args>(args)...);
}



}
}

#endif //PROJECT_MESSAGE_DISPATCHER_HPP
