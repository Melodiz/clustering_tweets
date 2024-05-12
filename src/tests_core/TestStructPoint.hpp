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
        testConstructors();
        testDistanceCalculation();
        testCalcNorm();
        testEqualityOperator();
        testInequalityOperator();
        testLessThanOperator();
        std::cout << "All TestPoint tests passed.\n" << std::endl;
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

    static void testConstructors()
    {
        Point defaultPoint;
        assert(defaultPoint.coords.empty());
        assert(defaultPoint.distance == INT_MAX);
        assert(defaultPoint.cluster_id == -1);

        Point listPoint({1.0, 2.0});
        assert(listPoint.coords.size() == 2);
        assert(listPoint.coords[0] == 1.0 && listPoint.coords[1] == 2.0);

        Point vectorPoint(std::vector<double>{3.0, 4.0}, 1);
        assert(vectorPoint.cluster_id == 1);
        assert(std::abs(vectorPoint.distance - 0) < 1e-9);
        assert(vectorPoint.coords[0] == 3.0 && vectorPoint.coords[1] == 4.0);

        std::cout << "Test passed: Point constructors." << std::endl;
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