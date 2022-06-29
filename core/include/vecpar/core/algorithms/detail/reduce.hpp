#ifndef VECPAR_REDUCE_HPP
#define VECPAR_REDUCE_HPP

#include "vecpar/core/definitions/common.hpp"

namespace vecpar::detail {

/**
 * The operation has to be commutative and associative
 * since the order is not guaranteed.
 */
template <typename R> struct parallel_reduce {
  TARGET virtual typename R::value_type *reduce(typename R::value_type *result,
                                                typename R::value_type &partial_result) = 0;
};
} // namespace vecpar::detail
#endif // VECPAR_REDUCE_HPP
