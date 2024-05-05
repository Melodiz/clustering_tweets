#include "../clustering_core/KmeansND.h"
#include <cassert>
#include <filesystem>
#include <iostream>

// Utility function to compare two points
bool comparePoints(const Point& a, const Point& b)
{
    if (a.coords.size() != b.coords.size()) return false;
    for (size_t i = 0; i < a.coords.size(); ++i)
    {
        if (a.coords[i] != b.coords[i]) return false;
    }
    return true;
}

// Test reading data from a file
void testReadData()
{
    std::string testFilePath = "samples/test_data.csv";// Ensure this file exists with known content
    std::vector<Point> points = read_data(testFilePath);
    // Manually verify the content of test_data.csv matches expected points
    std::cout << "Read " << points.size() << " points from " << testFilePath << std::endl;
    // Further checks can be added based on known file content
}

// Test initializing random centroids
void testInitializeRandomCentroids()
{
    std::vector<Point> points = {{std::vector<double>{0.0, 1.0}}, {std::vector<double>{2.0, 3.0}}, {std::vector<double>{4.0, 5.0}}};
    int k = 2;
    std::vector<Point> centroids = initialize_random_centroids(points, k);
    assert(centroids.size() == k);
    std::cout << "Initialized " << k << " random centroids successfully.\n";
}

// Test the clustering process
void testClustering()
{
    // std::vector<Point> points = {{std::vector<double>{0.0, 1.0}}, {std::vector<double>{2.0, 3.0}}, {std::vector<double>{4.0, 5.0}}};

    Point p1({0.0, 1.0, 2.0, 3.0});
    Point p2({2.0, 3.0, 4.0, 5.0});
    Point p3({4.0, 5.0, 6.0, 7.0});

    std::vector<Point> points = {p1, p2, p3};

    // check the euclidian distance calculation
    assert(p1.calcDist(p2) == 4.0);// sqrt((0-2)^2 + (1-3)^2 + (2-4)^2 + (3-5)^2) = 4
    assert(p1.calcDist(p3) == 8.0);// sqrt((0-4)^2 + (1-5)^2 + (2-6)^2 + (3-7)^2) = 8
    assert(p1.calcDist(p1) == 0.0);// distance from a point to itself is 0

    std::cout << "Initialized " << points.size() << " test points.\n";
    KMeansND kmeans(2, 10, points);
    kmeans.setResultPath("output/test_result.csv");
    std::cout << "Initialized KMeansND with k = " << kmeans.getK() << std::endl;
    kmeans.run();
    // Manual verification needed to check the correctness of clustering
    std::cout << "Clustering completed. Manual verification required.\n";
}

// Test writing results to a file
void testWriteResults(std::string resultPath = "output/test_result.csv")
{
    std::vector<Point> points = {{std::vector<double>{0.0, 1.0}}, {std::vector<double>{2.0, 3.0}}, {std::vector<double>{4.0, 5.0}}};
    KMeansND kmeans(2, 10, points);
    kmeans.setResultPath(resultPath);
    kmeans.setCentroidsPath("output/test_centroids.csv");
    kmeans.run();
    // Verify the file exists and manually check its content
    assert(std::filesystem::exists(resultPath));
    std::cout << "Results written to " << resultPath << ". Manual verification required.\n";
}

int main()
{
    testReadData();
    testInitializeRandomCentroids();
    testClustering();
    testWriteResults();
    std::cout << "All tests completed. Check console output for details.\n";
    return 0;
}