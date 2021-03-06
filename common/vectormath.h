#ifndef COMMON_VECTORMATH_H
#define COMMON_VECTORMATH_H

#include <vector>
#include <unordered_map>
#include <cmath>

namespace vectormath {

    template<typename Numeric>
    std::vector<Numeric> vector_add(std::vector<Numeric> v, std::vector<Numeric> w) {
        std::vector<Numeric> result{};

        for (int i = 0; i < std::min(v.size(), w.size()); i++) {
            result.push_back(v[i] + w[i]);
        }

        return result;
    }

    template<typename Numeric>
    std::vector<Numeric> vector_subtract(std::vector<Numeric> v, std::vector<Numeric> w) {
        std::vector<Numeric> result{};

        for (int i = 0; i < std::min(v.size(), w.size()); i++) {
            result.push_back(v[i] - w[i]);
        }

        return result;
    }

    template<typename Numeric>
    std::vector<Numeric> vectors_sum(std::vector<std::vector<Numeric>> vectors) {
        std::vector<Numeric> result{};

        for (int i = 0; i < vectors.size(); i++) {
            result = vector_add(result, vectors[i]);
        }

        return result;
    }

    template<typename Numeric>
    std::vector<Numeric> vector_scalar_multiply(std::vector<Numeric> v, Numeric s) {
        std::vector<Numeric> result{};

        for (int i = 0; i < v.size(); i++) {
            result.push_back(v[i] * s);
        }

        return result;
    }

    template<typename Numeric>
    std::vector<Numeric> vectors_mean(std::vector<Numeric> vectors) {
        return vector_scalar_multiply(1 / vectors.size(), vectors_sum(vectors));
    }

    template<typename Numeric>
    float vector_dot_product(std::vector<Numeric> v, std::vector<Numeric> w) {
        float result = 0;

        for (int i = 0; i < std::min(v.size(), w.size()); i++) {
            result += v[i] * w[i];
        }

        return result;
    }

    template<typename Numeric>
    Numeric vector_sum_of_squares(std::vector<Numeric> v) {
        return vector_dot_product(v, v);
    }

    template<typename Numeric>
    Numeric vector_magnitude(std::vector<Numeric> v) {
        return sqrt(vector_sum_of_squares(v));
    }

    template<typename Numeric>
    Numeric vector_squared_distance(std::vector<Numeric> v, std::vector<Numeric> w) {
        return vector_sum_of_squares(vector_subtract(v, w));
    }

    template<typename Numeric>
    Numeric vector_distance(std::vector<Numeric> v, std::vector<Numeric> w) {
        return vector_magnitude(vector_subtract(v, w));
    }

    template<typename Numeric>
    std::unordered_map<Numeric, int> vector_count(std::vector<Numeric> v) {
        std::unordered_map<Numeric, int> result;
        for (Numeric item : v) {
            result[item]++; // autovivication!
        }
        return result;
    }

}

#endif //COMMON_VECTORMATH_H
