#include "../clustering_core/KMeans2D.h"// Adjust this include to the actual path of your KMeans class definition
#include <cassert>
#include <iostream>

/**
 * Creates a simple dataset for testing KMeans clustering.
 * 
 * This function generates a small dataset consisting of points clustered around two centers: (1,1) and (5,5).
 * It is used to test the basic functionality of the KMeans clustering algorithm.
 * 
 * @return A vector of Point objects representing the dataset.
 */
std::vector<Point> createSimpleDataset()
{
    std::vector<Point> points;
    // Cluster around (1,1)
    points.push_back(Point(1.1, 1.1));
    points.push_back(Point(0.9, 0.9));
    // Cluster around (5,5)
    points.push_back(Point(5.1, 5.1));
    points.push_back(Point(4.9, 4.9));
    return points;
}

/**
 * Tests the KMeans clustering algorithm.
 * 
 * This function creates a simple dataset, applies KMeans clustering to it, and asserts that the points
 * are correctly assigned to their respective clusters. It assumes the existence of a KMeans class with
 * methods for setting points, performing clustering, and retrieving clustered points.
 * 
 * The test passes if all points are correctly assigned to their expected clusters, based on their proximity
 * to the cluster centers.
 */
void testKMeansClustering()
{
    std::vector<Point> points = createSimpleDataset();
    KMeans kmeans(2, 100);// Assuming KMeans can be initialized without file paths for this test

    std::cout << "KMeans clustering test started." << std::endl;
    kmeans.setPoints(points);
    kmeans.kMeansClustering();

    // This part assumes you have a way to access the points after clustering, e.g., a getPoints method
    std::vector<Point> clusteredPoints = kmeans.getPoints();// This method needs to be implemented
    for (const auto& point: clusteredPoints)
    {
        if (point.x < 3)
        {
            assert(point.cluster_id == 0);// Assuming points near (1,1) are assigned to cluster 0
        }
        else
        {
            assert(point.cluster_id == 1);// Assuming points near (5,5) are assigned to cluster 1
        }
    }

    std::cout << "KMeans clustering test passed." << std::endl;
}

/**
 * Main function to run the KMeans clustering test.
 * 
 * This function serves as the entry point for the program. It calls the testKMeansClustering function
 * to verify the correctness of the KMeans clustering implementation.
 * 
 * @return An integer indicating the exit status of the program. Returns 0 if the test passes.
 */
int main()
{
    testKMeansClustering();
    return 0;
}