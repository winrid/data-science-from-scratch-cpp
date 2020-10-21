#ifndef COMMON_NAIVE_BAYES_H
#define COMMON_NAIVE_BAYES_H

#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>

namespace naive_bays {

    enum classification {
        GOOD, BAD
    };
    struct training_item {
        std::string value;
        classification classification;
    };

    struct training_probability {
        std::string value;
        std::map<classification, double> probability_by_classification;
    };

    std::set<std::string> tokenize(std::string input) {
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        std::set<std::string> result;
        std::regex word_regex("[a-z0-9]+");
        auto words_begin = std::sregex_iterator(input.begin(), input.end(), word_regex);
        auto words_end = std::sregex_iterator();
        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::smatch match = *i;
            result.insert(match.str());
        }
        return result;
    }

    std::map<std::string, std::map<classification, int>> count_words(const std::vector<training_item> &training_set) {
        std::map<std::string, std::map<classification, int>> result;

        for (const training_item &item : training_set) {
            for (const std::string &word : tokenize(item.value)) {
                result[word][item.classification]++;
            }
        }

        return result;
    }

    std::vector<training_probability>
    word_probabilities(std::map<std::string, std::map<classification, int>> counts, double k = 0.5) {
        std::vector<training_probability> result;

        std::map<classification, int> count_by_classification;
        for (std::pair<std::string, std::map<naive_bays::classification, int>> word_pair : counts) {
            for (std::pair<naive_bays::classification, int> classification_pair : word_pair.second) {
                count_by_classification[classification_pair.first] += classification_pair.second;
            }
        }

        for (std::pair<std::string, std::map<naive_bays::classification, int>> word_pair : counts) {
            std::map<classification, double> probabilities{};
            for (std::pair<naive_bays::classification, int> classification_pair : word_pair.second) {
                probabilities[classification_pair.first] = (classification_pair.second + k) / (count_by_classification[classification_pair.first] + 2 * k);
            }
            result.push_back({
                word_pair.first,
                probabilities
            });
        }

        return result;
    }

    // I was hoping to make this namespace generic so we could add different classifications, but this method
    // throws that out of the window.
    double spam_probability(std::vector<training_probability> word_probabilities, std::string message) {
        std::set<std::string> message_words = tokenize(message);
        double log_prob_if_spam = 0;
        double log_prob_if_not_spam = 0;

        for (training_probability probability : word_probabilities) {
            double prob_if_spam = probability.probability_by_classification[classification::BAD];
            double prob_if_not_spam = probability.probability_by_classification[classification::GOOD];

            // if word appears in the message,
            // add the log probability of seeing it
            if (message_words.count(probability.value) > 0) {
                log_prob_if_spam += prob_if_spam > 0 ? std::log(prob_if_spam) : 0;
                log_prob_if_not_spam += prob_if_not_spam > 0 ? std::log(prob_if_not_spam) : 0;
            } else {
                // if the word doesn't appear in the message, add the log probability of not seeing it
                // which is log(1 - probability of seeing it)
                log_prob_if_spam += (1.0 - prob_if_spam == 0 ? 0 : std::log(1.0 - prob_if_spam));
                log_prob_if_not_spam += (1.0 - prob_if_not_spam == 0 ? 0 : std::log(1.0 - prob_if_not_spam));
            }
        }

        double prob_if_spam = std::exp(log_prob_if_spam);
        double prob_if_not_spam = std::exp(log_prob_if_not_spam);
        return prob_if_spam / (prob_if_spam + prob_if_not_spam);
    }

}

#endif //COMMON_NAIVE_BAYES_H
