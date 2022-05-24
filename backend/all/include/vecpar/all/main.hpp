#ifndef VECPAR_MAIN_HPP
#define VECPAR_MAIN_HPP

#if defined(__CUDA__) && defined(__clang__)
        #include "vecpar/cuda/cuda_parallelization.hpp"
#endif

#if _OPENMP
#include "vecpar/omp/omp_parallelization.hpp"
#endif

#include <vecmem/containers/vector.hpp>

#include "vecpar/core/algorithms/parallelizable_map_filter.hpp"
#include "vecpar/core/algorithms/parallelizable_map_reduce.hpp"
#include "vecpar/core/definitions/config.hpp"

namespace vecpar {

    template<class Algorithm,
            class MemoryResource,
            typename R = typename Algorithm::result_type,
            typename T,
            typename... Arguments>
    vecmem::vector<R>& parallel_map(Algorithm& algorithm,
                    MemoryResource& mr,
                    vecpar::config config,
                    vecmem::vector<T>& data,
                    Arguments... args) {
#if defined(__CUDA__) && defined(__clang__)
        return vecpar::cuda::parallel_map<Algorithm, R, T, Arguments...>(algorithm, mr, config, data, args...);
#elif _OPENMP
      return vecpar::omp::parallel_map<Algorithm, R, T, Arguments...>(algorithm, mr, config, data, args...);
#endif
    }

    template<class Algorithm,
            class MemoryResource,
            typename R = typename Algorithm::result_type,
            typename T,
            typename... Arguments>
    vecmem::vector<R>& parallel_map(Algorithm& algorithm,
                                    MemoryResource& mr,
                                    vecmem::vector<T>& data,
                                    Arguments... args) {
#if defined(__CUDA__) && defined(__clang__)
        return vecpar::cuda::parallel_map<Algorithm, R, T, Arguments...>(algorithm, mr, data, args...);
#elif _OPENMP
        return vecpar::omp::parallel_map<Algorithm, R, T, Arguments...>(algorithm, mr, data, args...);
#endif
    }

    template<class Algorithm,
            class MemoryResource,
            typename R>
    R& parallel_reduce(Algorithm& algorithm,
                       MemoryResource& mr,
                       vecmem::vector<R>& data) {
#if defined(__CUDA__) && defined(__clang__)
        return vecpar::cuda::parallel_reduce<Algorithm, R>(algorithm, mr, data);
#elif _OPENMP
      return vecpar::omp::parallel_reduce<Algorithm, R>(algorithm, mr, data);
#endif
    }

    template<class Algorithm,
            class MemoryResource,
            typename T>
    vecmem::vector<T>& parallel_filter(Algorithm& algorithm,
                                        MemoryResource& mr,
                                        vecmem::vector<T>& data){
#if defined(__CUDA__) && defined(__clang__)
        return vecpar::cuda::parallel_filter<Algorithm, T>(algorithm, mr, data);
#elif _OPENMP
      return vecpar::omp::parallel_filter<Algorithm, T>(algorithm, mr, data);
#endif
    }

    template<class Algorithm,
            class MemoryResource,
            typename R = typename Algorithm::result_type,
            typename T,
            typename... Arguments>
    R& parallel_map_reduce(Algorithm& algorithm,
                          MemoryResource& mr,
                          vecpar::config config,
                          vecmem::vector<T>& data,
                          Arguments... args) {
#if defined(__CUDA__) && defined(__clang__)
        return vecpar::cuda::parallel_map_reduce<Algorithm, R, T, Arguments...>(algorithm, mr, config, data, args...);
#elif _OPENMP
      return vecpar::omp::parallel_map_reduce<Algorithm, R, T, Arguments...>(
          algorithm, mr, config, data, args...);
#endif
    }

    template<class Algorithm,
            class MemoryResource,
            typename R = typename Algorithm::result_type,
            typename T,
            typename... Arguments>
    R& parallel_map_reduce(Algorithm& algorithm,
                           MemoryResource& mr,
                           vecmem::vector<T>& data,
                           Arguments... args) {
#if defined(__CUDA__) && defined(__clang__)
        return vecpar::cuda::parallel_map_reduce<Algorithm, R, T, Arguments...>(algorithm, mr, data, args...);
#elif _OPENMP
        return vecpar::omp::parallel_map_reduce<Algorithm, R, T, Arguments...>(
                algorithm, mr, data, args...);
#endif
    }

    template<class Algorithm,
            class MemoryResource,
            class R = typename Algorithm::result_type,
            typename T,
            typename... Arguments>
    vecmem::vector<R>& parallel_map_filter(Algorithm& algorithm,
                                          MemoryResource& mr,
                                          vecpar::config config,
                                          vecmem::vector<T>& data,
                                          Arguments... args) {
#if defined(__CUDA__) && defined(__clang__)
        return vecpar::cuda::parallel_map_filter<Algorithm, R, T, Arguments...>(algorithm, mr, config, data, args...);
#elif _OPENMP
      return vecpar::omp::parallel_map_filter<Algorithm, R, T, Arguments...>(
          algorithm, mr, config, data, args...);
#endif
    }

    template<class Algorithm,
            class MemoryResource,
            class R = typename Algorithm::result_type,
            typename T,
            typename... Arguments>
    vecmem::vector<R>& parallel_map_filter(Algorithm& algorithm,
                                           MemoryResource& mr,
                                           vecmem::vector<T>& data,
                                           Arguments... args) {
#if defined(__CUDA__) && defined(__clang__)
        return vecpar::cuda::parallel_map_filter<Algorithm, R, T, Arguments...>(algorithm, mr, data, args...);
#elif _OPENMP
        return vecpar::omp::parallel_map_filter<Algorithm, R, T, Arguments...>(
                algorithm, mr, data, args...);
#endif
    }

    template<class MemoryResource,
            class Algorithm,
            class R = typename Algorithm::result_type,
            class T, typename... Arguments,
            typename std::enable_if_t<std::is_base_of<vecpar::algorithm::parallelizable_map_filter<R, T, Arguments...>, Algorithm>::value ||
                                      std::is_base_of<vecpar::algorithm::parallelizable_mmap_filter<T, Arguments...>, Algorithm>::value, bool> = true>
    vecmem::vector<R>& parallel_algorithm(Algorithm algorithm,
                                         MemoryResource& mr,
                                         vecpar::config config,
                                         vecmem::vector<T>& data,
                                         Arguments... args) {

        return parallel_map_filter(algorithm, mr, config, data, args...);
    }

    template<class MemoryResource,
            class Algorithm,
            class R = typename Algorithm::result_type,
            class T, typename... Arguments,
            typename std::enable_if_t<std::is_base_of<vecpar::algorithm::parallelizable_map_filter<R, T, Arguments...>, Algorithm>::value ||
                                      std::is_base_of<vecpar::algorithm::parallelizable_mmap_filter<T, Arguments...>, Algorithm>::value, bool> = true>
    vecmem::vector<R>& parallel_algorithm(Algorithm algorithm,
                                          MemoryResource& mr,
                                          vecmem::vector<T>& data,
                                          Arguments... args) {

        return parallel_map_filter(algorithm, mr, data, args...);
    }

    template<class MemoryResource,
            class Algorithm,
            class R = typename Algorithm::result_type,
            class T, typename... Arguments,
            typename std::enable_if_t<std::is_base_of<vecpar::algorithm::parallelizable_map_reduce<R, T, Arguments...>, Algorithm>::value ||
                                      std::is_base_of<vecpar::algorithm::parallelizable_mmap_reduce<T, Arguments...>, Algorithm>::value, bool> = true>
    R& parallel_algorithm(Algorithm algorithm,
                         MemoryResource& mr,
                         vecpar::config config,
                         vecmem::vector<T>& data,
                         Arguments... args) {

        return parallel_map_reduce(algorithm, mr, config, data, args...);
    }

    template<class MemoryResource,
            class Algorithm,
            class R = typename Algorithm::result_type,
            class T, typename... Arguments,
            typename std::enable_if_t<std::is_base_of<vecpar::algorithm::parallelizable_map_reduce<R, T, Arguments...>, Algorithm>::value ||
                                      std::is_base_of<vecpar::algorithm::parallelizable_mmap_reduce<T, Arguments...>, Algorithm>::value, bool> = true>
    R& parallel_algorithm(Algorithm algorithm,
                          MemoryResource& mr,
                          vecmem::vector<T>& data,
                          Arguments... args) {

        return parallel_map_reduce(algorithm, mr, data, args...);
    }
}

#endif //VECPAR_MAIN_HPP
