#ifndef VECPAR_ALG2_HPP
#define VECPAR_ALG2_HPP

#include "vecpar/core/algorithms/parallelizable_map_reduce.hpp"
#include "vecpar/core/definitions/config.hpp"

#include "../data_types.hpp"
#include "algorithm.hpp"

class test_algorithm_2 :
        public traccc::algorithm<double*(vecmem::vector<int>, X)>,
        public vecpar::algorithm::parallelizable_map_reduce<double, int, X> {

public:

    TARGET test_algorithm_2(vecmem::memory_resource& mr): parallelizable_map_reduce(), algorithm(), m_mr(mr) {}

    TARGET double& map(double& result_i, int& first_i, X second_i) override {
        result_i = first_i * second_i.f();
        return result_i;
    }

    TARGET double* reduce(double* result, double& result_i) override {
        *result += result_i;
        return result;
    }

    TARGET double* operator() (vecmem::vector<int> data, X x, double* result) {
        vecmem::vector<double> result_tmp(data.size(), &m_mr);
        for (int i = 0; i < data.size(); i++)
            reduce(result, map(result_tmp[i], data[i], x));
        return result;
    }

    TARGET double* operator() (vecmem::vector<int> data, X more_data) override {
        double* result = new double();
        this->operator()(data, more_data, result);
        return result;
    }

private:
    vecmem::memory_resource& m_mr;
};

#endif