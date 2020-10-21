#include "naive_bays_classifier.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>

static std::string SUBJECT_PREFIX = "Subject:";

void
add_file_to_training_set(const std::string &path, bool is_spam, std::vector<naive_bays::training_item> &training_set) {
    std::fstream file;
    file.open(path, std::ios::in);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.find(SUBJECT_PREFIX) == 0) { // we only care about email subjects
//                std::cout << "adding to set " << line << "\n";
                training_set.push_back({line.substr(SUBJECT_PREFIX.size() - 1), is_spam ? naive_bays::classification::BAD : naive_bays::classification::GOOD});
            }
        }
    }
}

void
add_dir_to_training_set(const std::string &path, bool is_spam, std::vector<naive_bays::training_item> &training_set) {
    for (const auto &entry : std::filesystem::directory_iterator(path))
        add_file_to_training_set(entry.path().generic_string(), is_spam, training_set);
}

struct classification_result {
    std::string subject;
    bool is_spam;
    double spam_probability;
};

int main() {
    std::vector<naive_bays::training_item> data;
    add_dir_to_training_set(R"(C:\Users\winri\Downloads\spam)", true, data);
    add_dir_to_training_set(R"(C:\Users\winri\Downloads\easy_ham)", false, data);
    add_dir_to_training_set(R"(C:\Users\winri\Downloads\hard_ham)", false, data);

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<> distr(0, 1); // define the range
    std::vector<naive_bays::training_item> training_data;
    std::vector<naive_bays::training_item> testing_data;

    for (const naive_bays::training_item& item : data) {
        if (distr(gen) > 0.75) {
            training_data.push_back(item);
        } else {
            testing_data.push_back(item);
        };
    }

    NaiveBayesClassifier classifier(0.5);
    classifier.train(training_data);

    std::vector<classification_result> classified;
    for (const naive_bays::training_item& item : testing_data) {
        double result = classifier.classify(item.value);
        std::cout << "Classification result: " << result << "\n";
        classified.push_back({item.value, item.classification == naive_bays::classification::BAD, result});
    }

    int actual_spam_count = 0;
    int predicted_spam_count = 0;
    int actual_not_spam_count = 0;
    int predicted_not_spam_count = 0;
    for (const classification_result& result : classified) {
        if (result.is_spam) {
            actual_spam_count++;
        } else {
            actual_not_spam_count++;
        }
        if (result.spam_probability > 0.5) {
            predicted_spam_count++;
        } else {
            predicted_not_spam_count++;
        }
    }
    std::cout << "Spam vs Predicted Spam " << actual_spam_count << " " << predicted_spam_count << "\n";
    std::cout << "Not Spam vs Predicted Spam " << actual_not_spam_count << " " << predicted_not_spam_count << "\n";
}