#pragma once
#include "../clustering_core/modules/kMeansLogic.hpp"
#include "../clustering_core/modules/readData.hpp"
#include "../clustering_core/modules/structPoint.hpp"
#include "../clustering_core/modules/writeData.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// reference of functions to check
void save_result(const std::string& _resultPath, const std::vector<Point>& _points, const std::vector<Point>& _centroids, bool _with_coordinates);

class TestWriteData
{
public:
    static void runTests()
    {
        std::cout << "Running TestWriteData tests..." << std::endl;
        testWriteToCSV();
        testWriteToTXT();
        std::cout << "All TestWriteData tests passed.\n" << std::endl;
    }

private:
    static void testWriteToCSV()
    {
        std::string outputPath = "output/sample_data.csv";
        std::string verifyPath = "samples/sample_data.csv";
        std::vector<Point> points = CreateSampleData();
        std::vector<Point> centroids = initialize_random_centroids(points, 3);
        assignPointsToCentroids(points, centroids);

        save_result(outputPath, points, centroids, true);

        // Verify the file content
        std::vector<Point> resultOfSaving = read_data(outputPath);
        std::vector<Point> expectedResult = read_data(verifyPath);

        assert(resultOfSaving.size() == expectedResult.size());
        for (int i = 0; i < resultOfSaving.size(); i++)
        {
            assert(resultOfSaving[i] == expectedResult[i]);
        }
        std::cout << "Test passed: Write to CSV." << std::endl;
    }

    static void testWriteToTXT()
    {
        std::string outputPath = "output/sample_data.txt";
        std::string verifyPath = "samples/sample_data.txt";
        std::vector<Point> points = CreateSampleData();
        std::vector<Point> centroids = initialize_random_centroids(points, 3);
        assignPointsToCentroids(points, centroids);

        save_result(outputPath, points, centroids, true);

        // Verify the file content
        std::vector<Point> resultOfSaving = read_data(outputPath);
        std::vector<Point> expectedResult = read_data(verifyPath);

        assert(resultOfSaving.size() == expectedResult.size());
        for (int i = 0; i < resultOfSaving.size(); i++)
        {
            assert(resultOfSaving[i] == expectedResult[i]);
        }
        std::cout << "Test passed: Write to TXT." << std::endl;
    }


    static std::vector<Point> CreateSampleData()
    {
        std::vector<Point> data = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9},
                {10, 11, 12},
                {13, 14, 15},
                {16, 17, 18},
                {19, 20, 21},
                {22, 23, 24},
                {25, 26, 27},
                {28, 29, 30},
        };

        for (size_t i = 0; i < data.size(); ++i)
        {
            data[i].cluster_id = static_cast<int>(i);
            data[i].distance = static_cast<double>(i) * 0.1;
        }

        return data;
    }
};