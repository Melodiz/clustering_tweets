#pragma once
#include "../../clustering_core/modules/structPoint.hpp"
#include "SortingClusters.hpp"
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <vector>


std::vector<Point> getNeighbors(const Point& center, const std::vector<Point>& points, int k)
{
    // Check that k is valid (k > 0 && k < points.size())
    if (k <= 0) { return std::vector<Point>(); }
    if (k >= points.size()) { return points; }

    // Sort points by distance from the center
    std::vector<Point> sortedPoints = points;
    sortPointsByDistance(center, sortedPoints);

    // Select points based on max distance from each other and closest to center
    std::vector<Point> neighbors;
    neighbors.push_back(sortedPoints[0]); // Start with the closest point to the center

    while (neighbors.size() < k) {
        double maxMinDist = -1.0;
        Point bestCandidate;

        for (const auto& point : sortedPoints) {
            double minDist = __DBL_MAX__;
            for (const auto& neighbor : neighbors) {
                double dist = point.calcDist(neighbor);
                if (dist < minDist) {
                    minDist = dist;
                }
            }

            if (minDist > maxMinDist) {
                maxMinDist = minDist;
                bestCandidate = point;
            }
        }

        neighbors.push_back(bestCandidate);
    }

    return neighbors;
}