// TestCluster.hpp
#pragma once
#include "../data_processing/Clusters.hpp"
#include <cassert>
#include <vector>
#include <iostream>

class TestClusterConstructor
{
public:
    static void runTests()
    {
        std::cout << "\nRunning Cluster class tests..." << std::endl;
        testDefaultConstructor();
        testClusterIdConstructor();
        testClusterIdCenterConstructor();
        testClusterIdPointsConstructor();
        testClusterIdCenterPointsConstructor();
        testClusterIdCenterPointsNumPointsConstructor();
        std::cout << "All Cluster class tests passed.\n" << std::endl;
    }

protected:
    static void testDefaultConstructor()
    {
        Cluster c;
        assert(c.getClusterId() == -1);
        assert(c.getNumPoints() == 0);
        assert(c.getPoints().empty());
        std::cout << "Test passed: Default constructor." << std::endl;
    }

    static void testClusterIdConstructor()
    {
        int cluster_id = 1;
        Cluster c(cluster_id);
        assert(c.getClusterId() == cluster_id);
        assert(c.getNumPoints() == 0);
        assert(c.getPoints().empty());
        std::cout << "Test passed: Cluster ID constructor." << std::endl;
    }

    static void testClusterIdCenterConstructor()
    {
        int cluster_id = 1;
        Point center({1.0, 2.0});
        Cluster c(cluster_id, center);
        assert(c.getClusterId() == cluster_id);
        assert(c.getCenter() == center);
        assert(c.getNumPoints() == 0);
        assert(c.getPoints().empty());
        std::cout << "Test passed: Cluster ID and Center constructor." << std::endl;
    }

    static void testClusterIdPointsConstructor()
    {
        int cluster_id = 1;
        std::vector<Point> points = {Point({1.0, 2.0}), Point({3.0, 4.0})};
        Cluster c(cluster_id, points);
        assert(c.getClusterId() == cluster_id);
        assert(c.getPoints() == points);
        assert(c.getNumPoints() == points.size());
        std::cout << "Test passed: Cluster ID and Points constructor." << std::endl;
    }

    static void testClusterIdCenterPointsConstructor()
    {
        int cluster_id = 1;
        Point center({1.0, 2.0});
        std::vector<Point> points = {Point({3.0, 4.0}), Point({5.0, 6.0})};
        Cluster c(cluster_id, center, points);
        assert(c.getClusterId() == cluster_id);
        assert(c.getCenter() == center);
        assert(c.getPoints() == points);
        assert(c.getNumPoints() == points.size());
        std::cout << "Test passed: Cluster ID, Center, and Points constructor." << std::endl;
    }

    static void testClusterIdCenterPointsNumPointsConstructor()
    {
        int cluster_id = 1;
        Point center({1.0, 2.0});
        std::vector<Point> points = {Point({3.0, 4.0}), Point({5.0, 6.0})};
        int num_points = points.size();
        Cluster c(cluster_id, center, points, num_points);
        assert(c.getClusterId() == cluster_id);
        assert(c.getCenter() == center);
        assert(c.getPoints() == points);
        assert(c.getNumPoints() == num_points);
        std::cout << "Test passed: Cluster ID, Center, Points, and Num Points constructor." << std::endl;
    }
};

class TestClusterSort {
public:
    static void runTests() {
        std::cout << "\nRunning Cluster sort tests..." << std::endl;
        testSort2D();
        testSort3D();
        testSort4D();
        std::cout << "All Cluster sort tests passed.\n" << std::endl;
    }

private:
    static void testSort2D() {
        int cluster_id = 1;
        Point center({0.0, 0.0});
        std::vector<Point> points = {Point({3.0, 4.0}), Point({1.0, 1.0}), Point({2.0, 2.0})};
        Cluster cluster(cluster_id, center, points);

        cluster.sort();

        const std::vector<Point>& sortedPoints = cluster.getPoints();
        assert(sortedPoints[0].calcDist(center) <= sortedPoints[1].calcDist(center));
        assert(sortedPoints[1].calcDist(center) <= sortedPoints[2].calcDist(center));

        std::cout << "Test passed: Cluster sort by distance from center (2D)." << std::endl;
    }

    static void testSort3D() {
        int cluster_id = 1;
        Point center({0.0, 0.0, 0.0});
        std::vector<Point> points = {Point({3.0, 4.0, 5.0}), Point({1.0, 1.0, 1.0}), Point({2.0, 2.0, 2.0})};
        Cluster cluster(cluster_id, center, points);

        cluster.sort();

        const std::vector<Point>& sortedPoints = cluster.getPoints();
        assert(sortedPoints[0].calcDist(center) <= sortedPoints[1].calcDist(center));
        assert(sortedPoints[1].calcDist(center) <= sortedPoints[2].calcDist(center));

        std::cout << "Test passed: Cluster sort by distance from center (3D)." << std::endl;
    }

    static void testSort4D() {
        int cluster_id = 1;
        Point center({0.0, 0.0, 0.0, 0.0});
        std::vector<Point> points = {Point({3.0, 4.0, 5.0, 6.0}), Point({1.0, 1.0, 1.0, 1.0}), Point({2.0, 2.0, 2.0, 2.0})};
        Cluster cluster(cluster_id, center, points);

        cluster.sort();

        const std::vector<Point>& sortedPoints = cluster.getPoints();
        assert(sortedPoints[0].calcDist(center) <= sortedPoints[1].calcDist(center));
        assert(sortedPoints[1].calcDist(center) <= sortedPoints[2].calcDist(center));

        std::cout << "Test passed: Cluster sort by distance from center (4D)." << std::endl;
    }
};