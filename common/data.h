#ifndef CHAPTER_16_DATA_H
#define CHAPTER_16_DATA_H

#include <vector>
#include "statistics.h"
#include "matrixmath.h"

namespace data {

    template<typename Numeric>
    struct scale_result {
        std::vector<Numeric> means{};
        std::vector<Numeric> stdevs{};
    };

    template<typename Numeric>
    scale_result<Numeric> scale(const std::vector<std::vector<Numeric>> &matrix) {
        auto[num_rows, num_cols] = matrixmath::shape(matrix);
        std::vector<Numeric> means;
        for (int i = 0; i < num_cols; i++) {
            means.push_back(statistics::mean(matrixmath::get_column(matrix, i)));
        }

        std::vector<Numeric> stdevs;
        for (int i = 0; i < num_cols; i++) {
            stdevs.push_back(statistics::standard_deviation(matrixmath::get_column(matrix, i)));
        }

        return {means, stdevs};
    }

    // Rescales the input data so that each column has mean 0 and standard deviation 1, ignores columns with no standard deviation.
    template<typename Numeric>
    std::vector<std::vector<Numeric>> rescale(std::vector<std::vector<Numeric>> matrix) {
        scale_result scale_result = scale(matrix);

        auto[num_rows, num_cols] = matrixmath::shape(matrix);
        return matrixmath::make_matrix(num_rows, num_cols, [matrix, scale_result](int row, int col) -> double {
            if (scale_result.stdevs[col] > 0) {
                return (matrix[row][col] - scale_result.means[col]) / scale_result.stdevs[col];
            } else {
                return matrix[row][col];
            }
        });
    }

}

#endif //CHAPTER_16_DATA_H
