#ifndef NAIVE_BAYS_CLASSIFIER_H
#define NAIVE_BAYS_CLASSIFIER_H
#include <utility>

#include "naive_bayes.h"


class NaiveBayesClassifier {
public:
    explicit NaiveBayesClassifier(double k);
    void train(const std::vector<naive_bays::training_item>& training_set);
    double classify(std::string message);
private:
    double k;
    std::vector<naive_bays::training_probability> word_probabilities;
};

NaiveBayesClassifier::NaiveBayesClassifier(double k) {
    this->k = k;
}

void NaiveBayesClassifier::train(const std::vector<naive_bays::training_item>& training_set) {
    std::map<std::string, std::map<naive_bays::classification, int>> word_counts = naive_bays::count_words(training_set);
    this->word_probabilities = naive_bays::word_probabilities(word_counts, k);
}

double NaiveBayesClassifier::classify(std::string message) {
    return naive_bays::spam_probability(this->word_probabilities, std::move(message));
}

#endif //NAIVE_BAYS_CLASSIFIER_H
