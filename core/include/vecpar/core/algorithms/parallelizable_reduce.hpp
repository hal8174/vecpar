#ifndef VECPAR_PARALLELIZABLE_REDUCE_HPP
#define VECPAR_PARALLELIZABLE_REDUCE_HPP

#include "vecpar/core/algorithms/detail/reduce.hpp"

namespace vecpar::algorithm {

    template <typename R>
    struct parallelizable_reduce : public vecpar::detail::parallel_reduce<R> {};


} // namespace vecpar::algorithm
#endif // VECPAR_PARALLELIZABLE_REDUCE_HPP
