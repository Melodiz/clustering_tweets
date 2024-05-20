// SortingClusters.hpp
#pragma once
#include "../../clustering_core/modules/structPoint.hpp"
#include <algorithm>
#include <vector>

/**
 * @brief Sorts a collection of points by their distance from a given center point.
 * 
 * @param center The center point from which distances are calculated.
 * @param points The collection of points to be sorted.
 */
void sortPointsByDistance(const Point& center, std::vector<Point>& points)
{
    std::sort(points.begin(), points.end(), [&center](const Point& a, const Point& b) {
        return a.calcDist(center) < b.calcDist(center);
    });
}