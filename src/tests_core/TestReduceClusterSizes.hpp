#include "../data_processing/ReduceClusterSizes.hpp"
#include <cassert>
#include <iostream>

class TestReadCentroids
{
public:
    static void runTests()
    {
        std::cout << "\nRunning TestReadCentroids..." << std::endl;
        testReadCentroidsFromCSV();
        std::cout << "All ReadCentroids tests passed." << std::endl;
    }

private:
    static void testReadCentroidsFromCSV()
    {
        std::string path = "samples/sample_centroids.csv";
        std::vector<Point> centroids = readCentroids_from_csv(path);

        // Ensure that centroids are read
        assert(!centroids.empty());

        // Ensure that the correct number of centroids are read
        assert(centroids.size() == 3);

        // Ensure that the coordinates are read correctly
        std::vector<Point> expected_centroids = createSampleCentroids();
        assert(centroids.size() == expected_centroids.size());
        for (size_t i = 0; i < centroids.size(); ++i)
        {
            assert(centroids[i].coords == expected_centroids[i].coords);
            assert(centroids[i].cluster_id == expected_centroids[i].cluster_id);
        }

        std::cout << "Test passed: readCentroids_from_csv with " << centroids.size() << " centroids." << std::endl;
    }

    static std::vector<Point> createSampleCentroids()
    {
        std::vector<Point> centroids;

        std::vector<double> coords;
        coords.push_back(1.0);
        coords.push_back(2.0);
        coords.push_back(3.0);
        centroids.push_back(Point(coords, 0, 0));

        coords.clear();
        coords.push_back(4.0);
        coords.push_back(5.0);
        coords.push_back(6.0);
        centroids.push_back(Point(coords, 1, 0));

        coords.clear();
        coords.push_back(7.0);
        coords.push_back(8.0);
        coords.push_back(9.0);
        centroids.push_back(Point(coords, 2, 0));

        return centroids;
    }
};