#ifndef COMMON_MATRIXMATH_H
#define COMMON_MATRIXMATH_H

#include <vector>
#include <functional>

namespace matrixmath {

    // TODO this should be templated, but it breaks data::rescale
    std::vector<std::vector<double>> make_matrix(int num_rows, int num_cols, const std::function<double(int, int)>& matrixEntryFunction) {
        std::vector<std::vector<double>> result;

        for (int row = 0; row < num_rows; row++) {
            std::vector<double> row_data;
            for (int col = 0; col < num_cols; col++) {
                row_data.push_back(matrixEntryFunction(row, col));
            }
            result.push_back(row_data);
        }

        return result;
    }

    struct matrix_shape {
        int rows;
        int cols;
    };

    template<typename Numeric>
    matrix_shape shape(std::vector<std::vector<Numeric>> matrix) {
        return {(int) matrix.size(), (int) (matrix.size() > 0 ? matrix[0].size() : 0)};
    }

    template<typename Numeric>
    std::vector<Numeric> get_column(std::vector<std::vector<Numeric>> matrix, int column) {
        std::vector<Numeric> result;

        for (std::vector<Numeric> row : matrix) {
            result.push_back(row[column]);
        }

        return result;
    }

}

#endif //COMMON_MATRIXMATH_H
