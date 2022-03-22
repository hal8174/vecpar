#ifndef VECPAR_ALG5_HPP
#define VECPAR_ALG5_HPP

#include "vecpar/core/algorithms/parallelizable_map.hpp"
#include "vecpar/core/definitions/config.hpp"

#include "../data_types.hpp"
#include "algorithm.hpp"

class test_algorithm_5 :
        public traccc::algorithm<vecmem::vector<double>(vecmem::vector<double>, X)>,
        public vecpar::algorithm::parallelizable_mmap<double, X> {

public:

    TARGET test_algorithm_5(vecmem::memory_resource& mr) : parallelizable_mmap(), algorithm(), m_mr(mr) {}

    TARGET double& map(double& i, X second_i) override {
        i = i + second_i.f();
        return i;
    }

    TARGET vecmem::vector<double> operator() (vecmem::vector<double> data, X more_data) override {
        for (int i = 0; i < data.size(); i++)
            map(data[i], more_data);
        return data;
    }

private:
    vecmem::memory_resource& m_mr;
};

#endif