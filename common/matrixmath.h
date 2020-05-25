#ifndef COMMON_MATRIXMATH_H
#define COMMON_MATRIXMATH_H

#include <vector>

namespace matrixmath {

    class MatrixEntryFunction {
    public:
        virtual Numeric operator() (int row, int col) = 0;
    };

    template<typename Numeric>
    std::vector<Numeric> make_matrix(int num_rows, int num_cols, MatrixEntryFunction* matrixEntryFunction) {
        std::vector<std::vector<Numeric>> result;

        for (int row = 0; row < num_rows; row++) {
            std::vector<Numeric> row;
            for (int col = 0; col < num_cols; col++) {
                row.push_back((*matrixEntryFunction)(row, col));
            }
            result.push_back(result);
        }

        return result;
    }

}

#endif //COMMON_MATRIXMATH_H
