#ifndef COMMON_GRADIENT_H
#define COMMON_GRADIENT_H

namespace gradient {

    class DifferenceQuotientCallback {
    public:
        virtual double operator() (double f) = 0;
    };

    double difference_quotient(DifferenceQuotientCallback* differenceQuotientCallback, double x, double h) {
        return ((*differenceQuotientCallback)(x + h) - (*differenceQuotientCallback)(x)) / h;
    }

    double square(double x) {
        return x * x;
    }

    double derivative(double x) {
        return 2 * x;
    }

}

#endif //COMMON_GRADIENT_H
