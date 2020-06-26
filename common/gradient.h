#ifndef COMMON_GRADIENT_H
#define COMMON_GRADIENT_H

#include <vector>

namespace gradient {

    class DoubleCallback {
    public:
        virtual double operator()(double f) = 0;
    };

    double difference_quotient(DoubleCallback *differenceQuotientCallback, double x, double h) {
        return ((*differenceQuotientCallback)(x + h) - (*differenceQuotientCallback)(x)) / h;
    }

    double square(double x) {
        return x * x;
    }

    double derivative(double x) {
        return 2 * x;
    }

//    double partial_difference_quotient(DoubleCallback *f, DoubleCallback *v, double i, double h) {
        // TODO the book doesn't really document what f and v should take or return, and it doesn't
        //  seem this function is used, so I'm not going to finish it until I see an example...
//    }

    template<typename Numeric>
    std::vector<Numeric> step(std::vector<Numeric> v, std::vector<Numeric> direction, Numeric step_size) {
        std::vector<Numeric> result{};
        for (int i = 0; i < v.size(); i++) {
            result.push_back(v[i] + step_size * direction[i]);
        }
        return result;
    }

    template<typename Numeric>
    std::vector<Numeric> sum_of_squares_gradient(std::vector<Numeric> v) {
        std::vector<Numeric> result{};
        for (Numeric v_i : v) {
            result.push_back(2 * v_i);
        }
        return result;
    }

}

#endif //COMMON_GRADIENT_H
