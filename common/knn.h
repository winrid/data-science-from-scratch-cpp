#ifndef COMMON_KNN_H
#define COMMON_KNN_H

#include <algorithm>
#include <unordered_map>
#include <utility>
#include <cmath>

namespace knn {

    // Assumes that labels are ordered from nearest to farthest.
    std::string majority_vote(std::vector<std::string> labels) {
        std::string winner;
        int winner_count = 0;

        std::unordered_map<std::string, int> vote_counts;

        for (std::string label : labels) {
            vote_counts[label]++;
            if (vote_counts[label] >= winner_count) {
                winner = label;
                winner_count = vote_counts[label];
            }
        }

        int num_winners = 0;

        for (std::string label : labels) {
            if (vote_counts[label] == winner_count) {
                num_winners++;
            }
        }

        if (num_winners == 1) {
            return winner;
        } else {
            std::vector<std::string> labels_without_last = std::move(labels);
            labels_without_last.pop_back();
            return majority_vote(labels_without_last);
        }
    }

    struct point {
        double longitude;
        double latitude;
        std::string label;
    };

    double toRad(double degree) {
        return degree / 180 * 3.14;
    }

    double calculateDistance(double lat1, double long1, double lat2, double long2) {
        double dist;
        dist = sin(toRad(lat1)) * sin(toRad(lat2)) + cos(toRad(lat1)) * cos(toRad(lat2)) * cos(toRad(long1 - long2));
        dist = acos(dist);
        dist = 6371 * dist;
        return dist;
    }

    std::string classify(int k, std::vector<point> labeled_points, const point &new_point) {
        std::sort(labeled_points.begin(), labeled_points.end(), [new_point](const point i, const point j) -> int {
            return calculateDistance(i.latitude, i.longitude, new_point.latitude, new_point.longitude) <
                calculateDistance(j.latitude, j.longitude, new_point.latitude, new_point.longitude);
        });

        int label_count = std::min(k, (int) labeled_points.size());
        std::vector<std::string> k_nearest_labels;
        for (int i = 0; i < label_count; i++) {
            k_nearest_labels.push_back(labeled_points[i].label);
        }

        return majority_vote(k_nearest_labels);
    }

}

#endif //COMMON_KNN_H
