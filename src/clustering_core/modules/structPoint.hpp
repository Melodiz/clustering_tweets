#include <climits>         // for INT_MAX
#include <iostream>
#include <vector>
#include <cmath>

/**
 * @struct Point
 * @brief Represents a point in N-dimensional space.
 * 
 * This structure is used to represent both data points and centroids in a clustering algorithm.
 * It contains coordinates in N-dimensional space, the distance from the nearest centroid, and the cluster ID to which the point belongs.
 */

#pragma once
struct Point {
    std::vector<double> coords; ///< Coordinates of the point in N-dimensional space.
    double distance; ///< Distance from the nearest centroid. Initialized to INT_MAX for data points.
    int cluster_id;  ///< ID of the cluster to which the point belongs. Initialized to -1 to indicate no cluster assigned.

    /**
     * @brief Constructor for creating a point from a vector of coordinates.
     * @param coords A vector of doubles representing the coordinates of the point in N-dimensional space.
     * This constructor is typically used for initializing data points.
     */
    Point(const std::vector<double>& coords) : coords(coords), distance(INT_MAX), cluster_id(-1) {};

    /**
     * @brief Constructor for creating a centroid with specified coordinates and cluster ID.
     * @param coords A vector of doubles representing the coordinates of the centroid in N-dimensional space.
     * @param cluster_id An integer representing the unique ID of the cluster.
     * This constructor is used for initializing centroids.
     */
    Point(const std::vector<double>& coords, int cluster_id) : coords(coords), distance(0), cluster_id(cluster_id) {};

    /**
     * @brief Default constructor.
     * Initializes a point with no coordinates, maximum distance, and no cluster assigned.
     */
    Point() : distance(INT_MAX), cluster_id(-1), coords({}) {};

    /**
     * @brief Constructor for creating a point from an initializer list.
     * @param list An initializer list of doubles representing the coordinates of the point.
     * This constructor allows for easy inline initialization of points.
     */
    Point(std::initializer_list<double> list) : coords(list) {}

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

    /**
     * @brief Default destructor.
     */
    ~Point() = default;
};