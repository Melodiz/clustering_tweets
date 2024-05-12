#pragma once
#include "../clustering_core/modules/kMeansLogic.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
// Prototype of the function to be tested
std::vector<Point> initialize_random_centroids(const std::vector<Point>& points, int k);

class TestInitializeRandomCentroids
{
public:
    static void runTests()
    {
        std::cout << "Running tests for initialize_random_centroids..." << std::endl;
        testReturnsCorrectNumberOfCentroids();
        testCentroidsAreUnique();
        testCentroidsAreFromInputPoints();
        std::cout << "All tests for initialize_random_centroids passed.\n"
                  << std::endl;
    }

protected:
    static void testReturnsCorrectNumberOfCentroids()
    {
        std::vector<Point> points = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
        int k = 3;
        auto centroids = initialize_random_centroids(points, k);
        assert(centroids.size() == k);
        std::cout << "Test passed: Returns correct number of centroids." << std::endl;
    }

    static void testCentroidsAreUnique()
    {
        std::vector<Point> points = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
        int k = 3;
        auto centroids = initialize_random_centroids(points, k);
        std::set<std::vector<double>> uniqueCentroids;
        for (const auto& centroid: centroids)
        {
            uniqueCentroids.insert(centroid.coords);
        }
        assert(uniqueCentroids.size() == centroids.size());
        std::cout << "Test passed: Centroids are unique." << std::endl;
    }

    static void testCentroidsAreFromInputPoints()
    {
        std::vector<Point> points = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
        int k = 5;
        auto centroids = initialize_random_centroids(points, k);
        for (const auto& centroid: centroids)
        {
            assert(std::find(points.begin(), points.end(), centroid) != points.end());
        }
        std::cout << "Test passed: Centroids are from input points." << std::endl;
    }
};


class TestRecalculateCentroids
{
public:
    static void runTests()
    {
        std::cout << "Running tests for recalculateCentroids..." << std::endl;
        testRecalculateCentroids();
        std::cout << "All TestRecalculateCentroids tests passed.\n"
                  << std::endl;
    }

private:
    static void testRecalculateCentroids()
    {
        // Setup
        std::vector<Point> points = {
                Point({0.0, 0.0}, 0), Point({2.0, 2.0}, 0),
                Point({3.0, 3.0}, 1), Point({5.0, 5.0}, 1)};
        std::vector<Point> centroids = {
                Point({1.0, 1.0}),// Initial centroid for cluster 0
                Point({4.0, 4.0}) // Initial centroid for cluster 1
        };

        // Expected centroids after recalculation
        std::vector<Point> expectedCentroids = {
                Point({1.0, 1.0}),// Expected centroid for cluster 0
                Point({4.0, 4.0}) // Expected centroid for cluster 1
        };

        // Recalculate centroids
        recalculateCentroids(centroids, points);

        // Assert the recalculated centroids match the expected centroids
        for (int i = 0; i < centroids.size(); i++)
        {
            assert(centroids[i].coords.size() == expectedCentroids[i].coords.size());
            for (int j = 0; j < centroids[i].coords.size(); j++)
            {
                assert(std::abs(centroids[i].coords[j] - expectedCentroids[i].coords[j]) < 1e-9);
            }
        }

        std::cout << "Test passed: recalculateCentroids." << std::endl;
    }

};

class TestAssignPointsToCentroids
{
public:
    static void runTests()
    {
        std::cout << "Running tests for assignPointsToCentroids..." << std::endl;
        testAssignPointsToCentroids();
        std::cout << "All TestAssignPointsToCentroids tests passed.\n" << std::endl;

    }

private:
    static void testAssignPointsToCentroids()
    {
        // Setup
        std::vector<Point> points = {
                Point({0.0, 0.0}), Point({10.0, 10.0}), // near centroid 0
                Point({2.0, 2.0}), Point({9.0, 9.0})}; // near centroid 1
        std::vector<Point> centroids = {
                Point({1.0, 1.0}),// Centroid for cluster 0
                Point({8.0, 8.0}) // Centroid for cluster 1
        };

        // Expected cluster assignments
        std::vector<int> expectedAssignments = {0, 1, 0, 1};

        // Execute
        int changes = assignPointsToCentroids(points, centroids);

        // Verify
        assert(changes > 0);// There should be some changes
        for (size_t i = 0; i < points.size(); ++i)
        {
            assert(points[i].cluster_id == expectedAssignments[i]);
        }

        std::cout << "Test passed: assignPointsToCentroids with " << changes << " changes." << std::endl;
    }

    static int assignPointsToCentroids(std::vector<Point>& _points, std::vector<Point>& _centroids)
    {
        int pointsChanged = 0;
        for (size_t i = 0; i < _points.size(); ++i)
        {
            double minDist = std::numeric_limits<double>::max();
            int closestCentroid = -1;
            for (size_t j = 0; j < _centroids.size(); ++j)
            {
                double dist = _points[i].calcDist(_centroids[j]);
                if (dist < minDist)
                {
                    minDist = dist;
                    closestCentroid = j;
                }
            }
            if (_points[i].cluster_id != closestCentroid)
            {
                _points[i].cluster_id = closestCentroid;
                _points[i].distance = minDist;
                pointsChanged++;
            }
        }
        return pointsChanged;
    }
};