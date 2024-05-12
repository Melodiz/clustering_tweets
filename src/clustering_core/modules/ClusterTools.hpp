#include "structPoint.hpp"
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

// std::map<int, int> returnClustersSize(std::vector<Point> _points);
// void iterationStatus(int iteration, int pointsChanged);

std::map<int, int> returnClustersSize(std::vector<Point> _points)
{
    std::map<int, int> clusters;
    for (int i = 0; i < _points.size(); i++)
    {
        clusters[_points[i].cluster_id]++;
    }
    return clusters;
}


void iterationStatus(int iteration, int pointsChanged)
{
    // display status of the current iteration 
    // in format: "Iteration: 5, Points changed: 321"
    std::cout << "Iteration: " + std::to_string(iteration) + ", Points changed: " + std::to_string(pointsChanged);
}
