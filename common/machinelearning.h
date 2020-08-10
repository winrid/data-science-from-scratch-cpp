#ifndef COMMON_MACHINELEARNING_H

namespace machine_learning {
    // Accuracy, precision, and recall are not templated because if you pass ints, you could always get 0.

    // Accuracy is defined as the "fraction of correct predictions."
    double accuracy (double tp, double fp, double fn, double tn) {
        double correct = tp + tn;
        double total = tp + fp + fn + tn;
        return correct / total;
    }

    // Precision measures how accurate our positive predictions were.
    double precision (double tp, double fp, double fn, double tn) {
        return tp / (tp + fp);
    }

    // Recall measures what fraction of the positives our model identified.
    double recall(double tp, double fp, double fn, double tn) {
        return tp / (tp + fn);
    }

    // The harmonic mean of precision and recall.
    double f1_score(double tp, double fp, double fn, double tn) {
        double p = precision(tp, fp, fn, tn);
        double r = recall(tp, fp, fn, tn);

        return 2 * p * r / (p + r);
    }
}

#define COMMON_MACHINELEARNING_H

#endif //COMMON_MACHINELEARNING_H
