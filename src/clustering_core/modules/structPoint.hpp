#pragma once

#include <climits>// for INT_MAX
#include <cmath>
#include <iostream>
#include <vector>

/**
 * @class Point
 * @brief Represents a point in N-dimensional space.
 * 
 * This class is used to represent both data points and centroids in a clustering algorithm.
 * It contains coordinates in N-dimensional space, the distance from the nearest centroid, and the cluster ID to which the point belongs.
 */
class Point {
public:
    std::vector<double> coords; ///< Coordinates of the point in N-dimensional space.
    double distance;            ///< Distance from the nearest centroid. Initialized to INT_MAX for data points.
    int cluster_id;             ///< ID of the cluster to which the point belongs. Initialized to -1 to indicate no cluster assigned.

    Point(const std::vector<double>& coords, int cluster_id, double distance);
    Point(std::initializer_list<double> list);
    Point(const std::vector<double>& coords);
    Point(const std::vector<double>& coords, int cluster_id);
    Point();
    ~Point() = default;

    double calcDist(const Point& other) const;
    double CalcNorm() const;

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
    bool operator<(const Point& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

// Implementations of Point methods

Point::Point(const std::vector<double>& coords, int cluster_id, double distance)
    : coords(coords), distance(distance), cluster_id(cluster_id) {}

Point::Point(std::initializer_list<double> list)
    : coords(list), distance(INT_MAX), cluster_id(-1) {}

Point::Point(const std::vector<double>& coords)
    : coords(coords), distance(INT_MAX), cluster_id(-1) {}

Point::Point(const std::vector<double>& coords, int cluster_id)
    : coords(coords), distance(0), cluster_id(cluster_id) {}

Point::Point()
    : distance(INT_MAX), cluster_id(-1), coords({}) {}

double Point::calcDist(const Point& other) const {
    double sum = 0;
    for (int i = 0; i < coords.size(); i++) {
        sum += pow(coords[i] - other.coords[i], 2);
    }
    return sqrt(sum);
}

double Point::CalcNorm() const {
    double sum = 0;
    for (int i = 0; i < coords.size(); i++) {
        sum += pow(coords[i], 2);
    }
    return sqrt(sum);
}

bool Point::operator==(const Point& other) const {
    return (coords == other.coords);
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

bool Point::operator<(const Point& other) const {
    if (cluster_id == -1 && other.cluster_id == -1) {
        return CalcNorm() < other.CalcNorm();
    }
    return distance < other.distance;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "cluster_id: " << p.cluster_id << ", distance: " << p.distance;
    os << ", coords: [ ";
    for (int i = 0; i < p.coords.size(); i++) {
        os << p.coords[i] << " ";
    }
    os << "]";
    return os;
}