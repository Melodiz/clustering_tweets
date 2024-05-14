#pragma once

#include "../clustering_core/modules/readData.hpp"// Include the header file for the read_data function
#include <cassert>
#include <filesystem>
#include <iostream>

class TestReadData
{
public:
    static void runTests()
    {
        std::cout << "Running TestReadData tests..." << std::endl;
        testReadFromCSV();
        testReadFromTXT();
        testReadFromNPY();
        testCompareAllFormats();
        std::cout << "All TestReadData tests passed.\n" << std::endl;
    }

protected:
    static void testReadFromCSV()
    {
        std::string path = "samples/sample_data.csv";
        std::vector<Point> points = read_data(path);
        assert(!points.empty());             // Ensure that points are read
        assert(points.size() == 10);         // Ensure that the correct number of points are read
        assert(points[0].coords.size() == 3);// Ensure that the correct number of dimensions are 3

        std::vector<Point> expected_points = CreateSampleData();
        assert(points.size() == expected_points.size());
        for (int i = 0; i < points.size(); i++)
        {
            assert(points[i].coords == expected_points[i].coords);
        }
        std::cout << "Test passed: read_from_csv with " << points.size() << " points." << std::endl;
    }

    static void testReadFromTXT()
    {
        std::string path = "samples/sample_data.txt";
        std::vector<Point> points = read_data(path);

        assert(!points.empty());             // Ensure that points are read
        assert(points.size() == 10);         // Ensure that the correct number of points are read
        assert(points[0].coords.size() == 3);// Ensure that the correct number of dimensions are 3

        std::vector<Point> expected_points = CreateSampleData();
        assert(points.size() == expected_points.size());
        for (int i = 0; i < points.size(); i++)
        {
            assert(points[i].coords == expected_points[i].coords);
        }
        std::cout << "Test passed: read_from_txt with " << points.size() << " points." << std::endl;
    }

    static void testReadFromNPY()
    {
        std::string path = "samples/sample_data.npy";
        std::vector<Point> points = read_data(path);
        assert(!points.empty());             // Ensure that points are read
        assert(points.size() == 10);         // Ensure that the correct number of points are read
        assert(points[0].coords.size() == 3);// Ensure that the correct number of dimensions are 3

        std::vector<Point> expected_points = CreateSampleData();
        assert(points.size() == expected_points.size());
        for (int i = 0; i < points.size(); i++)
        {
            assert(points[i].coords == expected_points[i].coords);
        }
        std::cout << "Test passed: read_from_npy with " << points.size() << " points." << std::endl;
    }

    static void testCompareAllFormats()
    {
        std::string path_csv = "samples/sample_data.csv";
        std::string path_txt = "samples/sample_data.txt";
        std::string path_npy = "samples/sample_data.npy";

        std::vector<Point> points_csv = read_data(path_csv);
        std::vector<Point> points_txt = read_data(path_txt);
        std::vector<Point> points_npy = read_data(path_npy);

        assert(points_csv.size() == points_txt.size());
        assert(points_csv.size() == points_npy.size());
        assert(points_txt.size() == points_npy.size());

        for (int i = 0; i < points_csv.size(); i++)
        {
            assert(points_csv[i] == points_txt[i]);
            assert(points_csv[i] == points_npy[i]);
            assert(points_txt[i] == points_npy[i]);
        }

        std::cout << "Test passed: compare_all_formats with " << points_csv.size() << " points." << std::endl;
    }

    static std::vector<Point> CreateSampleData()
    {
        std::vector<Point> data =
                {
                        {1.0, 2.0, 3.0},
                        {4.0, 5.0, 6.0},
                        {7.0, 8.0, 9.0},
                        {10.0, 11.0, 12.0},
                        {13.0, 14.0, 15.0},
                        {16.0, 17.0, 18.0},
                        {19.0, 20.0, 21.0},
                        {22.0, 23.0, 24.0},
                        {25.0, 26.0, 27.0},
                        {28.0, 29.0, 30.0}};

        for (size_t i = 0; i < data.size(); ++i)
        {
            data[i].cluster_id = static_cast<int>(i);
            data[i].distance = static_cast<double>(i) * 0.1;
        }

        return data;
    }
};