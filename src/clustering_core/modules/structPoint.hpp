#pragma once

#include <climits>// for INT_MAX
#include <cmath>
#include <iostream>
#include <vector>

/**
 * @struct Point
 * @brief Represents a point in N-dimensional space.
 * 
 * This structure is used to represent both data points and centroids in a clustering algorithm.
 * It contains coordinates in N-dimensional space, the distance from the nearest centroid, and the cluster ID to which the point belongs.
 */

#pragma once
struct Point {
    std::vector<double> coords;///< Coordinates of the point in N-dimensional space.
    double distance;           ///< Distance from the nearest centroid. Initialized to INT_MAX for data points.
    int cluster_id;            ///< ID of the cluster to which the point belongs. Initialized to -1 to indicate no cluster assigned.

    Point(const std::vector<double>& coords, int cluster_id, double distance) : coords(coords), distance(distance), cluster_id(cluster_id){};
    /**
     * @brief Constructor for creating a point from a vector of coordinates.
     * @param coords A vector of doubles representing the coordinates of the point in N-dimensional space.
     * This constructor is typically used for initializing data points.
     */
    Point(std::initializer_list<double> list) : coords(list), distance(INT_MAX), cluster_id(-1){};
    Point(const std::vector<double>& coords) : coords(coords), distance(INT_MAX), cluster_id(-1){};
    /**
     * @brief Constructor for creating a centroid with specified coordinates and cluster ID.
     * @param coords A vector of doubles representing the coordinates of the centroid in N-dimensional space.
     * @param cluster_id An integer representing the unique ID of the cluster.
     * This constructor is used for initializing centroids.
     */

    Point(const std::vector<double>& coords, int cluster_id) : coords(coords), distance(0), cluster_id(cluster_id){};
    /**
     * @brief Default constructor.
     * Initializes a point with no coordinates, maximum distance, and no cluster assigned.
     */
    Point() : distance(INT_MAX), cluster_id(-1), coords({}){};

    /**
     * @brief Calculates the Euclidean distance between this point and another point.
     * @param other A reference to another Point object.
     * @return A double representing the Euclidean distance between the two points.
     */

    double calcDist(const Point& other) const
    {
        double sum = 0;
        for (int i = 0; i < coords.size(); i++)
        {
            sum += pow(coords[i] - other.coords[i], 2);
        }
        return sqrt(sum);
    }

    double CalcNorm() const
    {
        // calculate the norm of the point
        double sum = 0;
        for (int i = 0; i < coords.size(); i++)
        {
            sum += pow(coords[i], 2);
        }
        return sqrt(sum);
    }

    /**
     * @brief Default destructor.
     */
    ~Point() = default;

    // overload operators
    bool operator==(const Point& other) const
    {
        return (coords == other.coords);
    }
    bool operator!=(const Point& other) const { return !(*this == other); }

    bool operator<(const Point& other) const
    {
        // sort by distance from nearest centroid
        // if both are unassigned, sort by norms
        if (cluster_id == -1 && other.cluster_id == -1)
        {
            return CalcNorm() < other.CalcNorm();
        }
        return distance < other.distance;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p)
    {
        os << "cluster_id: " << p.cluster_id << ", distance: " << p.distance;
        os << ", coords: [ ";
        for (int i = 0; i < p.coords.size(); i++)
        {
            os << p.coords[i] << " ";
        }
        os << "]";
        return os;
    }
};