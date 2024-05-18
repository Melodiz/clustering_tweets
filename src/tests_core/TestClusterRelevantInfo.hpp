// TestClusterNeighbors.hpp
#pragma once
#include "../data_processing/Clusters.hpp"
#include <cassert>
#include <iostream>
#include <set>

class TestClusterNeighbors {
public:
    static void runTests() {
        testGetNeighbors2D();
        testGetNeighbors3D();
        testGetNeighbors4D();
        testDisjointChoose();
        testExtremeCases();
    }

private:
    static void testGetNeighbors2D() {
        int cluster_id = 1;
        Point center({0.0, 0.0});
        std::vector<Point> points = {Point({3.0, 4.0}), Point({1.0, 1.0}), Point({2.0, 2.0}), Point({5.0, 5.0})};
        Cluster cluster(cluster_id, center, points);

        int k = 2;
        std::vector<Point> neighbors = cluster.getNeighbors(k);

        assert(neighbors.size() == k);
        assert(neighbors[0].calcDist(center) <= neighbors[1].calcDist(center));

        std::cout << "Test passed: Cluster getNeighbors (2D)." << std::endl;
    }

    static void testGetNeighbors3D() {
        int cluster_id = 1;
        Point center({0.0, 0.0, 0.0});
        std::vector<Point> points = {Point({3.0, 4.0, 5.0}), Point({1.0, 1.0, 1.0}), Point({2.0, 2.0, 2.0}), Point({5.0, 5.0, 5.0})};
        Cluster cluster(cluster_id, center, points);

        int k = 2;
        std::vector<Point> neighbors = cluster.getNeighbors(k);

        assert(neighbors.size() == k);
        assert(neighbors[0].calcDist(center) <= neighbors[1].calcDist(center));

        std::cout << "Test passed: Cluster getNeighbors (3D)." << std::endl;
    }

    static void testGetNeighbors4D() {
        int cluster_id = 1;
        Point center({0.0, 0.0, 0.0, 0.0});
        std::vector<Point> points = {Point({3.0, 4.0, 5.0, 6.0}), Point({1.0, 1.0, 1.0, 1.0}), Point({2.0, 2.0, 2.0, 2.0}), Point({5.0, 5.0, 5.0, 5.0})};
        Cluster cluster(cluster_id, center, points);

        int k = 2;
        std::vector<Point> neighbors = cluster.getNeighbors(k);

        assert(neighbors.size() == k);
        assert(neighbors[0].calcDist(center) <= neighbors[1].calcDist(center));

        std::cout << "Test passed: Cluster getNeighbors (4D)." << std::endl;
    }

    static void testDisjointChoose() {
        int cluster_id = 1;
        Point center({0.0, 0.0});
        std::vector<Point> points = {
            Point({1.0, 1.0}), Point({1.1, 1.1}), Point({1.2, 1.2}),
            Point({5.0, 5.0}), Point({5.1, 5.1}), Point({5.2, 5.2}),
            Point({10.0, 10.0}), Point({10.1, 10.1}), Point({10.2, 10.2})
        };
        Cluster cluster(cluster_id, center, points);

        int k = 3;
        std::vector<Point> neighbors = cluster.getNeighbors(k);

        assert(neighbors.size() == k);

        // Check that the selected points are not too close to each other
        std::set<int> selectedDensities;
        for (const auto& neighbor : neighbors) {
            int density = std::round(neighbor.calcDist(center));
            assert(selectedDensities.find(density) == selectedDensities.end());
            selectedDensities.insert(density);
        }

        std::cout << "Test passed: Disjoint choose." << std::endl;
    }

    static void testExtremeCases() {
        // Case 1: k is larger than the number of points
        {
            int cluster_id = 1;
            Point center({0.0, 0.0});
            std::vector<Point> points = {Point({1.0, 1.0}), Point({2.0, 2.0})};
            Cluster cluster(cluster_id, center, points);

            int k = 5;
            std::vector<Point> neighbors = cluster.getNeighbors(k);

            assert(neighbors.size() == points.size());

            std::cout << "Test passed: Extreme case where k > number of points." << std::endl;
        }

        // Case 2: All points are equidistant from the center
        {
            int cluster_id = 1;
            Point center({0.0, 0.0});
            std::vector<Point> points = {Point({1.0, 1.0}), Point({-1.0, -1.0}), Point({1.0, -1.0}), Point({-1.0, 1.0})};
            Cluster cluster(cluster_id, center, points);

            int k = 2;
            std::vector<Point> neighbors = cluster.getNeighbors(k);

            assert(neighbors.size() == k);

            std::cout << "Test passed: Extreme case where all points are equidistant from the center." << std::endl;
        }

        // Case 3: No points in the cluster
        {
            int cluster_id = 1;
            Point center({0.0, 0.0});
            std::vector<Point> points;
            Cluster cluster(cluster_id, center, points);

            int k = 2;
            std::vector<Point> neighbors = cluster.getNeighbors(k);

            assert(neighbors.empty());

            std::cout << "Test passed: Extreme case where there are no points in the cluster." << std::endl;
        }
    }
};