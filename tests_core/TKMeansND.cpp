#include "../clustering_core/KmeansND.h"
#include <cassert>
#include <filesystem>
#include <iostream>

/**
 * Compares two points for equality based on their coordinates.
 * 
 * @param a The first point to compare.
 * @param b The second point to compare.
 * @return True if both points have the same coordinates, false otherwise.
 */
bool comparePoints(const Point& a, const Point& b)
{
    if (a.coords.size() != b.coords.size()) return false;
    for (size_t i = 0; i < a.coords.size(); ++i)
    {
        if (a.coords[i] != b.coords[i]) return false;
    }
    return true;
}

/**
 * Tests the functionality of reading data from a file into a vector of Points.
 * 
 * This function assumes the existence of a file 'samples/test_data.csv' with known content.
 * It reads the data into a vector of Points and prints the number of points read.
 * Manual verification is suggested to ensure the correctness of the read data.
 */
void testReadData()
{
    std::string testFilePath = "samples/test_data.csv";// Ensure this file exists with known content
    std::vector<Point> points = read_data(testFilePath);
    std::cout << "Read " << points.size() << " points from " << testFilePath << std::endl;
    // Further checks can be added based on known file content
}

/**
 * Tests the initialization of random centroids from a given set of points.
 * 
 * Initializes 'k' random centroids from a predefined set of points and asserts
 * that the correct number of centroids has been initialized.
 */
void testInitializeRandomCentroids()
{
    std::vector<double> p1(0.0, 1.0);
    std::vector<double> p2(2.0, 3.0);
    std::vector<double> p3(4.0, 5.0);

    std::vector<Point> points;
    points.push_back(Point(p1));
    points.push_back(Point(p2));
    points.push_back(Point(p3));
    int k = 2;
    std::vector<Point> centroids = initialize_random_centroids(points, k);
    assert(centroids.size() == k);
    std::cout << "Initialized " << k << " random centroids successfully.\n";
}

/**
 * Tests the clustering process using the KMeansND algorithm.
 * 
 * Initializes a set of test points and performs clustering using the KMeansND algorithm.
 * The function checks the Euclidean distance calculation between points and asserts
 * the expected distances. It also initializes a KMeansND instance and runs the clustering process.
 * Manual verification is suggested to ensure the correctness of the clustering results.
 */
void testClustering()
{
    Point p1({0.0, 1.0, 2.0, 3.0});
    Point p2({2.0, 3.0, 4.0, 5.0});
    Point p3({4.0, 5.0, 6.0, 7.0});

    std::vector<Point> points = {p1, p2, p3};

    assert(p1.calcDist(p2) == 4.0);// sqrt((0-2)^2 + (1-3)^2 + (2-4)^2 + (3-5)^2) = 4
    assert(p1.calcDist(p3) == 8.0);// sqrt((0-4)^2 + (1-5)^2 + (2-6)^2 + (3-7)^2) = 8
    assert(p1.calcDist(p1) == 0.0);// distance from a point to itself is 0

    std::cout << "Initialized " << points.size() << " test points.\n";
    KMeansND kmeans(2, 10, points);
    kmeans.setResultPath("output/test_result.csv");
    std::cout << "Initialized KMeansND with k = " << kmeans.getK() << std::endl;
    kmeans.run();
    std::cout << "Clustering completed. Manual verification required.\n";
}

/**
 * Tests writing the results of the clustering process to a file.
 * 
 * Initializes a KMeansND instance with a predefined set of points and runs the clustering process.
 * The results are written to a specified file path. The function then verifies the existence of the
 * result file and suggests manual verification of its content.
 * 
 * @param resultPath The file path where the clustering results are to be written.
 */
void testWriteResults(std::string resultPath = "output/test_result.csv")
{
    std::vector<Point> points = {{std::vector<double>{0.0, 1.0}}, {std::vector<double>{2.0, 3.0}}, {std::vector<double>{4.0, 5.0}}};
    KMeansND kmeans(2, 10, points);
    kmeans.setResultPath(resultPath);
    kmeans.setCentroidsPath("output/test_centroids.csv");
    kmeans.run();
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