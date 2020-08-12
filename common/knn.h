#ifndef COMMON_KNN_H
#define COMMON_KNN_H

#include <algorithm>
#include <unordered_map>
#include <utility>

namespace knn {

    struct knn_datapoint {
        std::string label;
        int value;
    };

    // Assumes that labels are ordered from nearest to farthest.
    std::string majority_vote(std::vector<std::string> labels) {
        std::string winner;
        int winner_count = 0;

        std::unordered_map<std::string, int> vote_counts;

        for (const std::string &label : labels) {
            vote_counts[label]++;
            if (vote_counts[label] >= winner_count) {
                winner = label;
                winner_count = vote_counts[label];
            }
        }

        int num_winners = 0;

        for (const std::string &label : labels) {
            if (vote_counts[label] == winner_count) {
                num_winners++;
            }
        }

        if (num_winners == 1) {
            return winner;
        } else {
            std::vector data_points_copied = std::move(labels);
            data_points_copied.pop_back();
            return majority_vote(data_points_copied);
        }
    }

    struct point {
        int distance;
        std::string label;
    };

    std::string classify(int k, std::vector<point> labeled_points, const point& new_point) {
        std::sort(labeled_points.begin(), labeled_points.end(), [new_point](const point i, const point j) -> int {
            return i.distance - new_point.distance; // todo does this work? if not, tag distance on point and then sort.
        });
        std::vector<std::string> k_nearest_labels(4);
        for (int i = 0; i < 4; i++) {
            k_nearest_labels.push_back(labeled_points[i].label);
        }

        return majority_vote(k_nearest_labels);
    }

}

#endif //COMMON_KNN_H
