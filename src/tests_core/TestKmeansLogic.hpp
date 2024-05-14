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
        std::vector<Point> centroids = initialize_random_centroids(points, k);
        assert(centroids.size() == k);
        for (int i = 0; i < centroids.size(); i++)
        {
            assert(centroids[i].coords.size() == 2);
            assert(centroids[i].cluster_id == i);
            assert(centroids[i].distance == 0.0);
        }
        std::cout << "Test passed: Returns correct number of centroids." << std::endl;
    }

    static void testCentroidsAreUnique()
    {
        std::vector<Point> points = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
        int k = 3;
        auto centroids = initialize_random_centroids(points, k);
        std::set<std::vector<double>> uniqueCentroids;
        assert(centroids.size() == k);
        for (int i = 0; i < centroids.size(); i++)
        {
            assert(centroids[i].coords.size() == 2);
            assert(centroids[i].cluster_id == i);
            assert(centroids[i].distance == 0.0);
        }
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
        assert(centroids.size() == k);
        for (int i = 0; i < centroids.size(); i++)
        {
            assert(centroids[i].coords.size() == 2);
            assert(centroids[i].cluster_id == i);
            assert(centroids[i].distance == 0.0);
        }
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
        testRecalculateCentroids2D();
        testRecalculateCentroids3D();
        std::cout << "All tests for recalculateCentroids passed.\n"
                  << std::endl;
    }

private:
    static void testRecalculateCentroids2D()
    {
        std::vector<Point> points = {
                Point({0, 0}, 0), Point({1, 1}, 0),
                Point({4, 4}, 0), Point({6, 6}, 0),
                Point({8, 8}, 0),
                Point({2, 2}, 1), Point({3, 3}, 1),
                Point({5, 5}, 1), Point({7, 7}, 1),
                Point({9, 9}, 1)};

        std::vector<Point> centroids = {
                Point({0, 0}), Point({1, 1})};

        recalculateCentroids(points, centroids);

        // Expected centroids are the average of points in each cluster
        Point expectedCentroid0({3.8, 3.8});
        Point expectedCentroid1({5.2, 5.2});

        assert(centroids[0].coords == expectedCentroid0.coords);
        assert(centroids[1].coords == expectedCentroid1.coords);

        std::cout << "Test passed: recalculateCentroids2D" << std::endl;
    }

    static void testRecalculateCentroids3D()
    {
        std::vector<Point> points = {
                Point({0.1, 0.2, 0.3}, 0), Point({1.4, 1.5, 1.6}, 0),
                Point({2.7, 2.8, 2.9}, 1), Point({3.0, 3.1, 3.2}, 1),
                Point({4.3, 4.4, 4.5}, 0), Point({5.6, 5.7, 5.8}, 1),
                Point({6.9, 7.0, 7.1}, 0), Point({8.2, 8.3, 8.4}, 1),
                Point({9.5, 9.6, 9.7}, 0), Point({10.8, 10.9, 11.0}, 1)};

        std::vector<Point> centroids = {
                Point({0, 0, 0}, 0, 0), Point({1, 1, 1}, 1, 0)};

        recalculateCentroids(points, centroids);

        // Expected centroids are the average of points in each cluster
        Point expectedCentroid0({4.44, 4.54, 4.64});
        Point expectedCentroid1({6.06, 6.16, 6.26});

        assert(centroids[0].coords.size() == expectedCentroid0.coords.size());
        assert(centroids[1].coords.size() == expectedCentroid1.coords.size());

        for (size_t i = 0; i < expectedCentroid0.coords.size(); i++)
        {
            assert((abs(centroids[0].coords[i] - expectedCentroid0.coords[i]) < 0.0001));
            assert((abs(centroids[1].coords[i] - expectedCentroid1.coords[i]) < 0.0001));
        }

        std::cout << "Test passed: recalculateCentroids3D" << std::endl;
    }
};

class TestAssignPointsToCentroids
{
public:
    static void runTests()
    {
        std::cout << "Running tests for assignPointsToCentroids..." << std::endl;
        testAssignPointsToCentroids();
        std::cout << "All TestAssignPointsToCentroids tests passed.\n"
                  << std::endl;
    }

private:
    static void testAssignPointsToCentroids()
    {
        // Setup
        std::vector<Point> points = {
                Point({0.0, 0.0}), Point({10.0, 10.0}),
                Point({2.0, 2.0}), Point({9.0, 9.0})};

        std::vector<Point> row_points = {
                Point({0.0, 0.0}), Point({10.0, 10.0}),
                Point({2.0, 2.0}), Point({9.0, 9.0})};

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
        // Verify points's coordinates are not changed
        for (size_t i = 0; i < row_points.size(); ++i)
        {
            assert(row_points[i].coords == points[i].coords);
        }

        std::cout << "Test passed: assignPointsToCentroids" << std::endl;
    }
    static void testAssignPointsToCentroids2()
    {
        std::vector<Point> points = {
                Point({1.0, 2.0}), Point({1.5, 1.8}),
                Point({2.0, 2.0}), Point({1.8, 1.5}),
                Point({5.0, 5.0}), Point({5.5, 4.8}),
                Point({5.0, 5.5}), Point({4.8, 5.2}),
                Point({2.5, 2.0}), Point({2.0, 2.5})};

        std::vector<Point> row_points = {
                Point({1.0, 2.0}), Point({1.5, 1.8}),
                Point({2.0, 2.0}), Point({1.8, 1.5}),
                Point({5.0, 5.0}), Point({5.5, 4.8}),
                Point({5.0, 5.5}), Point({4.8, 5.2}),
                Point({2.5, 2.0}), Point({2.0, 2.5})};

        std::vector<Point> centroids = {Point({1.0, 2.0}, 0, 0), Point({5.0, 5.0}, 1, 0)};

        // Expected cluster assignments
        std::vector<int> expectedAssignments = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0};
        // do the assignment
        assignPointsToCentroids(points, centroids);
        assignPointsToCentroids(points, centroids);

        // Verify
        for (size_t i = 0; i < points.size(); ++i)
        {
            assert(points[i].cluster_id == expectedAssignments[i]);
        }
        // Verify points's coordinates are not changed
        for (size_t i = 0; i < row_points.size(); ++i)
        {
            assert(row_points[i].coords == points[i].coords);
        }

        std::cout << "Test passed: assignPointsToCentroids2" << std::endl;
    }
};