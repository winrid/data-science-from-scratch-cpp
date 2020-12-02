#ifndef COMMON_STATISTICS_H
#define COMMON_STATISTICS_H

#include <algorithm>
#include <numeric>
#include <vector>
#include <unordered_map>

#include "vectormath.h"

namespace statistics {

    template<typename Numeric>
    std::vector<Numeric> copy_and_sort(std::vector<Numeric> v) {
        // Sort, and don't modify the input vector.
        std::vector<Numeric> v_sorted (v.size());
        std::partial_sort_copy(v.begin(), v.end(), v_sorted.begin(), v_sorted.end());
        return v_sorted;
    }

    double mean(std::vector<double> v) {
        double sum = 0;
        for (double v_i : v) {
            sum += v_i;
        }
        return sum / (double) v.size();
    }

    template<typename Numeric>
    Numeric median(std::vector<Numeric> v) {
        int count = v.size();
        int midpoint = count / 2; // use floor division (would be count // 2 in python)
        std::vector<Numeric> v_sorted = copy_and_sort(v);

        if (count % 2 == 1) {
            // If odd, return the middle value.
            return v_sorted[midpoint];
        }
        else {
            // If even, return the average of the middle values.
            int lo = midpoint - 1;
            int hi = midpoint;
            return (v_sorted[lo] + v_sorted[hi]) / 2;
        }
    }

    template<typename Numeric>
    Numeric quantile(std::vector<Numeric> v, float p) {
        int p_index = p * v.size();
        std::vector<Numeric> v_sorted = copy_and_sort(v);
        return v_sorted[p_index];
    }

    template<typename Numeric>
    std::vector<Numeric> mode(std::vector<Numeric> v) {
        std::unordered_map<Numeric, int> counts = vectormath::vector_count(v);
        int max_count = 0;
        for (auto count : counts) {
            if (count.second > max_count) {
                max_count = count.second;
            }
        }

        std::vector<Numeric> result;
        for (auto count : counts) {
            if (count.second == max_count) {
                result.push_back(count.first);
            }
        }

        return result;
    }

    template<typename Numeric>
    Numeric data_range(std::vector<Numeric> v) {
        auto [min, max] = std::minmax_element(v.begin(), v.end());
        return *max - *min;
    }

    template<typename Numeric>
    std::vector<float> de_mean(std::vector<Numeric> v) { // the book calls this de_mean on page 61, but it's a bad name.
        float x_bar = mean(v);
        std::vector<float> result;
        for (Numeric item : v) {
            result.push_back(item - x_bar);
        }
        return result;
    }

    template<typename Numeric>
    float variance(std::vector<Numeric> v) { // variance measures how a single variable deviates from its mean
        std::vector<float> deviations = de_mean(v);
        return vectormath::vector_sum_of_squares(deviations) / (float) (v.size() - 1);
    }

    template<typename Numeric>
    float standard_deviation(std::vector<Numeric> v) {
        return sqrt(variance(v)); // wow! standard deviation is just the square root of variance!
    }

    template<typename Numeric>
    float interquartile_range(std::vector<Numeric> v) {
        return quantile(v, 0.75) - quantile(v, 0.25);
    }

    template<typename Numeric>
    float covariance(std::vector<Numeric> x, std::vector<Numeric> y) {
        if (x.size() != y.size()) {
            throw "Both input vectors must have the same number of elements!";
        }
        return vectormath::vector_dot_product(de_mean(x), de_mean(y)) / (float) (x.size() - 1);
    }

    template<typename Numeric>
    float correlation(std::vector<Numeric> x, std::vector<Numeric> y) {
        if (x.size() != y.size()) {
            throw "Both input vectors must have the same number of elements!";
        }
        float stdev_x = standard_deviation(x);
        float stdev_y = standard_deviation(y);

        if (stdev_x > 0 && stdev_y > 0) {
            return covariance(x, y) / stdev_x / stdev_y;
        }
        else {
            return 0; // if no variation, correlation is 0
        }
    }


}

#endif //COMMON_STATISTICS_H
