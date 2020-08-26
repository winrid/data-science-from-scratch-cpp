#include <iostream>
#include "../common/machinelearning.h"

int main() {

    std::cout << "Accuracy: " << machine_learning::accuracy(70, 4930, 13930, 981070) << "\n"; // 0.98114

    std::cout << "Precision: " << machine_learning::precision(70, 4930, 13930, 981070) << "\n"; // 0.014

    std::cout << "Recall: " << machine_learning::recall(70, 4930, 13930, 981070) << "\n"; // 0.005

    std::cout << "Harmonic Mean (f1_score): " << machine_learning::f1_score(70, 4930, 13930, 981070) << "\n"; // 0.007

}
