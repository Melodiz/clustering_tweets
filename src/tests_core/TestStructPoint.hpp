#pragma once

#include "../clustering_core/modules/structPoint.hpp"// Include the header file for the Point struct
#include <cassert>
#include <cmath>
#include <vector>

/**
 * @file TestPoint.hpp
 * @brief Provides unit tests for the Point struct.
 */

class TestPoint
{
public:
    static void runTests()
    {
        std::cout << "Running Point structure tests..." << std::endl;
        testDefaultConstructor();
        testListConstructor();
        testVectorConstructor();
        testCentroidConstructor();
        testInitializeListConstructor();
        testMixedConstructor();
        testDistanceCalculation();
        testCalcNorm();
        testEqualityOperator();
        testInequalityOperator();
        testLessThanOperator();
        std::cout << "All TestPoint tests passed.\n"
                  << std::endl;
    }

protected:
    static void testDistanceCalculation()
    {
        Point p1({0, 0});
        Point p2({3, 4});
        assert(std::abs(p1.calcDist(p2) - 5.0) < 1e-9);// Distance should be 5.0

        Point p3({-1, -1});
        Point p4({-4, -5});
        assert(std::abs(p3.calcDist(p4) - 5.0) < 1e-9);// Distance should be 5.0

        std::cout << "Test passed: Distance calculation." << std::endl;
    }

    static void testDefaultConstructor()
    {
        Point p;
        assert(p.coords.empty());
        assert(p.distance == INT_MAX);
        assert(p.cluster_id == -1);
        std::cout << "Test passed: Default constructor." << std::endl;
    }

    static void testListConstructor()
    {
        Point p({1.0, 2.0, 3.0});
        assert(p.coords.size() == 3);
        assert(p.coords[0] == 1.0 && p.coords[1] == 2.0 && p.coords[2] == 3.0);
        assert(p.distance == INT_MAX);
        assert(p.cluster_id == -1);
        std::cout << "Test passed: List constructor." << std::endl;
    }

    static void testVectorConstructor()
    {
        std::vector<double> coords = {4.0, 5.0, 6.0};
        Point p(coords);
        assert(p.coords == coords);
        assert(p.distance == INT_MAX);
        assert(p.cluster_id == -1);
        std::cout << "Test passed: Vector constructor." << std::endl;
    }

    static void testCentroidConstructor()
    {
        std::vector<double> coords = {7.0, 8.0, 9.0};
        int cluster_id = 1;
        Point p(coords, cluster_id);
        assert(p.coords == coords);
        assert(p.distance == 0);// Centroid distance initialized to 0
        assert(p.cluster_id == cluster_id);
        std::cout << "Test passed: Centroid constructor." << std::endl;
    }

    static void testInitializeListConstructor()
    {
        std::vector<Point> points = {Point({1.0, 2.0}), Point({3.0, 4.5}), Point({5.0, 6.0})};
        assert(points[0].coords[0] == 1.0 && points[0].coords[1] == 2.0);
        assert(points[1].coords[0] == 3.0 && points[1].coords[1] == 4.5);
        assert(points[2].coords[0] == 5.0 && points[2].coords[1] == 6.0);
        assert(points[0].distance == INT_MAX && points[1].distance == INT_MAX && points[2].distance == INT_MAX);
        assert(points[0].cluster_id == -1 && points[1].cluster_id == -1 && points[2].cluster_id == -1);
        std::cout << "Test passed: Initialize list constructor." << std::endl;
    }

    static void testMixedConstructor()
    {
        std::vector<Point> points = {
                Point({1.0, 2.0}),
                Point({3.0, 4.5}, 1),
                Point({5.0, 6.0}, 2),
                Point({7, 2, 3, 4}, 3),
                Point({7, 2, 3, 4}, 3, 3.2)};

        assert(points[0].coords[0] == 1.0 && points[0].coords[1] == 2.0);
        assert(points[1].coords[0] == 3.0 && points[1].coords[1] == 4.5);
        assert(points[2].coords[0] == 5.0 && points[2].coords[1] == 6.0);
        assert(points[3].coords[0] == 7 && points[3].coords[1] == 2 && points[3].coords[2] == 3 && points[3].coords[3] == 4);
        assert(points[4].coords[0] == 7 && points[4].coords[1] == 2 && points[4].coords[2] == 3 && points[4].coords[3] == 4);
        assert(points[4].distance == 3.2);
        assert(points[4].cluster_id == 3);
        std::cout << "Test passed: Mixed constructor." << std::endl;
    }

    static void testCalcNorm()
    {
        Point p({3, 4});
        assert(std::abs(p.CalcNorm() - 5.0) < 1e-9);// 3^2 + 4^2 = 5^2
        std::cout << "Test passed: CalcNorm." << std::endl;
    }

    static void testEqualityOperator()
    {
        Point p1({1.0, 2.0}), p2({1.0, 2.0}), p3({2.0, 3.0});
        assert(p1 == p2);
        assert(!(p1 == p3));
        std::cout << "Test passed: Equality operator." << std::endl;
    }

    static void testInequalityOperator()
    {
        Point p1({1, 2}), p2({1, 2}), p3({2, 3});
        assert(!(p1 != p2));
        assert(p1 != p3);
        std::cout << "Test passed: Inequality operator." << std::endl;
    }

    static void testLessThanOperator()
    {
        Point p1({0, 0}, -1), p2({3, 4}, -1);// Both unassigned to a cluster
        Point p3({1, 1}, 0), p4({1, 1}, 0);
        p3.distance = 2.0;
        p4.distance = 3.0;// p3 is closer to its centroid than p4
        assert(p1 < p2);  // Based on norm
        assert(p3 < p4);  // Based on distance
        std::cout << "Test passed: Less than operator." << std::endl;
    }
};