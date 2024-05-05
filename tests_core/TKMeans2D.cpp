#include "../clustering_core/KMeans.h"// Adjust this include to the actual path of your KMeans class definition
#include <cassert>
#include <iostream>

// Function to create a simple dataset
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

// Function to test the KMeans clustering
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

int main()
{
    testKMeansClustering();
    return 0;
}