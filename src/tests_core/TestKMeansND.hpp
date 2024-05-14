#include "../clustering_core/KmeansND.hpp"
#include <cassert>
#include <iostream>
#include <vector>

class TestKMeansND
{
public:
    static void runTests()
    {
        std::cout << "Starting KMeansND tests..." << std::endl;
        testInitialization2D();
        testCoordsResetBug2D();
        testClustering2D();
        testCentroidCalculation2D();
        testInitialization3D();
        testCoordsResetBug3D();
        testClustering3D();
        testCentroidCalculation3D();
        testCentroidCalculation3DComplex();
        std::cout << "All KMeansND tests passed." << std::endl;
    }

private:
    static void testInitialization2D()
    {
        // Create a KMeansND instance with 2 clusters and 100 iterations maximum
        KMeansND kmeans(2, 100);

        // Initialize with 10 random points in 2D space
        std::vector<Point> points = {
                Point({1.0, 2.0}), Point({1.5, 1.8}),
                Point({2.0, 2.0}), Point({1.8, 1.5}),
                Point({5.0, 5.0}), Point({5.5, 4.8}),
                Point({5.0, 5.5}), Point({4.8, 5.2}),
                Point({2.5, 2.0}), Point({2.0, 2.5})};

        kmeans.setPoints(points);

        // Check if centroids are initialized and not equal to each other
        assert(!kmeans.getCentroids().empty());   // Ensure centroids are initialized
        assert(kmeans.getCentroids().size() == 2);// Ensure two centroids are initialized

        // Check if centroids are different from each other
        assert(kmeans.getCentroids()[0].coords != kmeans.getCentroids()[1].coords);

        assert(kmeans.getPoints().size() == points.size());// Ensure all points are initialized
        assert(kmeans.getPoints()[0].coords.size() == points[0].coords.size());

        // check that all clusters are members of given points
        for (size_t i = 0; i < kmeans.getCentroids().size(); ++i)
        {
            // check that that centroid in points using find
            assert(std::find(kmeans.getPoints().begin(), kmeans.getPoints().end(), kmeans.getCentroids()[i]) != kmeans.getPoints().end());
        }

        std::cout << "Test Passed: testInitialization2D" << std::endl;
    }

    static void testCoordsResetBug2D()
    {
        std::vector<Point> points = {
                Point({1.0, 2.0}), Point({1.5, 1.8}),
                Point({2.0, 2.0}), Point({1.8, 1.5}),
                Point({5.0, 5.0}), Point({5.5, 4.8}),
                Point({5.0, 5.5}), Point({4.8, 5.2}),
                Point({2.5, 2.0}), Point({2.0, 2.5})};

        std::vector<Point> row_points = {
                Point({1.0, 2.0}), Point({1.5, 1.8}),
                Point({2.0, 2.0}), Point({1.8, 1.5}),
                Point({5.0, 5.0}), Point({5.5, 4.8}),
                Point({5.0, 5.5}), Point({4.8, 5.2}),
                Point({2.5, 2.0}), Point({2.0, 2.5})};

        KMeansND kmeans(2, 100);
        kmeans.setPoints(points);
        assert(kmeans.getPoints().size() == points.size());
        assert(kmeans.getPoints()[0].coords.size() == points[0].coords.size());
        for (size_t i = 0; i < 5; ++i)
        {
            std::vector<Point> current_points = kmeans.getPoints();
            std::vector<Point> current_centroids = kmeans.getCentroids();
            // perform iteration
            int changed = assignPointsToCentroids(points, kmeans.getCentroids());
            recalculateCentroids(points, current_centroids);
            // set the result of iteration to kmeans
            kmeans.setPoints(points);
            kmeans.setCentroids(current_centroids);
            // check if the result is correct
            assert(kmeans.getCentroids().size() == 2);
            assert(kmeans.getPoints()[0].coords.size() == points[0].coords.size());
            for (size_t i = 0; i < kmeans.getPoints().size(); ++i)
            {
                assert(kmeans.getPoints()[i].coords == row_points[i].coords);
            }
        }
        std::cout << "Test Passed: testCoordsResetBug2D" << std::endl;
    }

    static void testClustering2D()
    {
        // Create a KMeansND instance with 2 clusters and 100 iterations maximum
        KMeansND kmeans(2, 100);

        // Initialize with 10 random points in 2D space
        std::vector<Point> points = {
                Point({1.0, 2.0}), Point({1.5, 1.8}),
                Point({2.0, 2.0}), Point({1.8, 1.5}),
                Point({5.0, 5.0}), Point({5.5, 4.8}),
                Point({5.0, 5.5}), Point({4.8, 5.2}),
                Point({2.5, 2.0}), Point({2.0, 2.5})};

        kmeans.setPoints(points);

        kmeans.Cluster(false);// Run clustering without showing status

        // Assuming we know the expected cluster IDs for each point
        std::vector<int> expectedClusterIds = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0};
        std::vector<Point> result_points = kmeans.getPoints();

        assert(result_points.size() == points.size());
        testExpectedClustering(result_points, expectedClusterIds);

        // check that points Point({5.0, 5.0}), Point({5.5, 4.8}),Point({5.0, 5.5}), Point({4.8, 5.2})
        // assigned to one cluster and all other points assigned to another cluster
        std::cout << "Test Passed: testClustering2D" << std::endl;
    }

    static void testCentroidCalculation2D()
    {
        // Initialize a set of points and their expected cluster assignments
        std::vector<Point> points = {
                Point({1.0, 2.0}), Point({1.5, 1.8}),
                Point({2.0, 2.0}), Point({1.8, 1.5}),
                Point({5.0, 5.0}), Point({5.5, 4.8}),
                Point({5.0, 5.5}), Point({4.8, 5.2}),
                Point({2.5, 2.0}), Point({2.0, 2.5})};

        KMeansND kmeans(2, 100);
        kmeans.setPoints(points);
        kmeans.Cluster(false);// Run clustering without showing status
        std::vector<Point> centroids = kmeans.getCentroids();
        std::vector<Point> result_points = kmeans.getPoints();

        // Calculate expected centroids for each cluster
        Point expectedCentroid0({1.76, 2.06});  // Average of points in cluster 0
        Point expectedCentroid1({5.075, 5.125});// Average of points in cluster 1

        // Check if the recalculated centroids match the expected centroids
        // at least diffrence less than 0.1
        assert(centroids.size() == 2);
        for (size_t i = 0; i < centroids[0].coords.size(); ++i)
        {
            assert((std::abs(centroids[0].coords[i] - expectedCentroid0.coords[i]) < 0.1) ||
                   (std::abs(centroids[0].coords[i] - expectedCentroid1.coords[i]) < 0.1));
            assert((std::abs(centroids[1].coords[i] - expectedCentroid0.coords[i]) < 0.1) ||
                   (std::abs(centroids[1].coords[i] - expectedCentroid1.coords[i]) < 0.1));
        }
        std::cout << "Test Passed: testCentroidCalculation2D" << std::endl;
    }

    static void testInitialization3D()
    {
        // Create a KMeansND instance with 2 clusters and 100 iterations maximum for 3D points
        KMeansND kmeans(2, 100);

        // Initialize with 10 random points in 3D space
        std::vector<Point> points = {
                Point({1.0, 2.0, 3.0}), Point({1.5, 1.8, 2.5}),
                Point({2.0, 2.0, 3.0}), Point({1.8, 1.5, 2.8}),
                Point({5.0, 5.0, 5.0}), Point({5.5, 4.8, 5.2}),
                Point({5.0, 5.5, 5.0}), Point({4.8, 5.2, 5.5}),
                Point({2.5, 2.0, 3.5}), Point({2.0, 2.5, 3.0})};

        kmeans.setPoints(points);

        // Check if centroids are initialized and not equal to each other
        assert(!kmeans.getCentroids().empty());   // Ensure centroids are initialized
        assert(kmeans.getCentroids().size() == 2);// Ensure two centroids are initialized

        // Check if centroids are different from each other
        assert(kmeans.getCentroids()[0].coords != kmeans.getCentroids()[1].coords);

        assert(kmeans.getPoints().size() == points.size());                    // Ensure all points are initialized
        assert(kmeans.getPoints()[0].coords.size() == points[0].coords.size());// Ensure points are 3D

        // check that all clusters are members of given points
        for (size_t i = 0; i < kmeans.getCentroids().size(); ++i)
        {
            // check that that centroid in points using find
            assert(std::find_if(kmeans.getPoints().begin(), kmeans.getPoints().end(),
                                [&](const Point& p) { return p == kmeans.getCentroids()[i]; }) != kmeans.getPoints().end());
        }

        std::cout << "Test Passed: testInitialization3D" << std::endl;
    }

    static void testCoordsResetBug3D()
    {
        std::vector<Point> points = {
                Point({1.0, 2.0, 3.0}), Point({1.5, 1.8, 2.5}),
                Point({2.0, 2.0, 3.0}), Point({1.8, 1.5, 2.8}),
                Point({5.0, 5.0, 5.0}), Point({5.5, 4.8, 5.2}),
                Point({5.0, 5.5, 5.0}), Point({4.8, 5.2, 5.5}),
                Point({2.5, 2.0, 3.5}), Point({2.0, 2.5, 3.0})};

        std::vector<Point> row_points = {
                Point({1.0, 2.0, 3.0}), Point({1.5, 1.8, 2.5}),
                Point({2.0, 2.0, 3.0}), Point({1.8, 1.5, 2.8}),
                Point({5.0, 5.0, 5.0}), Point({5.5, 4.8, 5.2}),
                Point({5.0, 5.5, 5.0}), Point({4.8, 5.2, 5.5}),
                Point({2.5, 2.0, 3.5}), Point({2.0, 2.5, 3.0})};

        KMeansND kmeans(2, 100);
        kmeans.setPoints(points);
        assert(kmeans.getPoints().size() == points.size());
        assert(kmeans.getPoints()[0].coords.size() == points[0].coords.size());
        for (size_t i = 0; i < 5; ++i)
        {
            std::vector<Point> current_points = kmeans.getPoints();
            std::vector<Point> current_centroids = kmeans.getCentroids();
            // perform iteration
            int changed = assignPointsToCentroids(points, kmeans.getCentroids());
            recalculateCentroids(points, current_centroids);
            // set the result of iteration to kmeans
            kmeans.setPoints(points);
            kmeans.setCentroids(current_centroids);
            // check if the result is correct
            assert(kmeans.getCentroids().size() == 2);
            assert(kmeans.getPoints()[0].coords.size() == points[0].coords.size());
            for (size_t i = 0; i < kmeans.getPoints().size(); ++i)
            {
                assert(kmeans.getPoints()[i].coords == row_points[i].coords);
            }
        }
        std::cout << "Test Passed: testCoordsResetBug3D" << std::endl;
    }

    static void testClustering3D()
    {
        // Create a KMeansND instance with 2 clusters and 100 iterations maximum for 3D points
        KMeansND kmeans(2, 100);

        // Initialize with 10 random points in 3D space
        std::vector<Point> points = {
                Point({1.0, 2.0, 3.0}), Point({1.5, 1.8, 2.5}),
                Point({2.0, 2.0, 3.0}), Point({1.8, 1.5, 2.8}),
                Point({5.0, 5.0, 5.0}), Point({5.5, 4.8, 5.2}),
                Point({5.0, 5.5, 5.0}), Point({4.8, 5.2, 5.5}),
                Point({2.5, 2.0, 3.5}), Point({2.0, 2.5, 3.0})};

        kmeans.setPoints(points);

        kmeans.Cluster(false);// Run clustering without showing status

        // Assuming we know the expected cluster IDs for each point
        // Note: The actual expectedClusterIds need to be determined based on the clustering result
        // This is just a placeholder to illustrate how the test could be structured
        std::vector<int> expectedClusterIds = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0};
        std::vector<Point> result_points = kmeans.getPoints();

        assert(result_points.size() == points.size());
        testExpectedClustering(result_points, expectedClusterIds);

        // check that points in one cluster are closer to each other than to points in the other cluster
        // This is a simplified check and may need to be adjusted based on actual clustering logic
        std::cout << "Test Passed: testClustering3D" << std::endl;
    }

    static void testCentroidCalculation3D()
    {
        std::vector<Point> points = {
                Point({0, 0, 0}, 0), Point({1, 1, 1}, 0),
                Point({2, 2, 2}, 0), Point({3, 3, 3}, 0),
                Point({4, 4, 4}, 0),
                Point({5, 5, 5}, 1), Point({6, 6, 6}, 1),
                Point({7, 7, 7}, 1), Point({8, 8, 8}, 1),
                Point({9, 9, 9}, 1)};

        std::vector<Point> centroids = {
                Point({0, 0, 0}), Point({5, 5, 5})};

        recalculateCentroids(points, centroids);

        // Expected centroids are the average of points in each cluster
        Point expectedCentroid0({2, 2, 2});
        Point expectedCentroid1({7, 7, 7});

        assert(centroids[0].coords == expectedCentroid0.coords);
        assert(centroids[1].coords == expectedCentroid1.coords);

        std::cout << "Test Passed: testCentroidCalculation3D" << std::endl;
    }

    static void testCentroidCalculation3DComplex()
    {
        std::vector<Point> points = {
                Point({-0.1, -0.2, 0.3}), Point({0.2, 1.1, 0.4}),// near (0, 0, 0) cluster
                Point({0.3, 0.4, 0.5}), Point({0.6, 0.7, 0.8}),  // near (0, 0, 0) cluster
                Point({0.9, 1.0, 1.1}), Point({-1, -1.1, -1.2}), // near (0, 0, 0) cluster
                Point({1.2, 1.3, 1.4}), Point({1.5, 1.6, 1.7}),  //  near (0, 0, 0) cluster
                Point({5.1, 5.2, 5.3}), Point({5.4, 5.1, 5.4}),  // near (5, 5, 5) cluster
                Point({5.7, 5.8, 5.9}), Point({6.0, 6.1, 6.2}),  // near (5, 5, 5) cluster
                Point({6.3, 6.4, 6.5}), Point({6.6, 6.7, 6.8}),  // near (5, 5, 5 cluster
        };
        KMeansND kmeans(2, 100);
        kmeans.setPoints(points);
        kmeans.Cluster(false);// Run clustering without showing status
        std::vector<Point> result_points = kmeans.getPoints();
        std::vector<Point> centroids = kmeans.getCentroids();
        std::vector<Point> expected_centroids = {
                Point({5.85, 5.883, 6.01667}, 0),
                Point({0.45, 0.6, 0.625}, 1)};

        // Verify the calculated centroids against the expected centroids
        assert(centroids.size() == expected_centroids.size());
        // since we dont care about the order of clusters, we can just check that
        // firt centroid is the same as the first expected centroid or the second
        for (size_t axis = 0; axis < centroids[0].coords.size(); ++axis)
        {
            assert((std::abs(centroids[0].coords[axis] - expected_centroids[0].coords[axis]) < 0.001) ||
                   (std::abs(centroids[0].coords[axis] - expected_centroids[1].coords[axis]) < 0.001));
            assert((std::abs(centroids[1].coords[axis] - expected_centroids[0].coords[axis]) < 0.001) ||
                   (std::abs(centroids[1].coords[axis] - expected_centroids[1].coords[axis]) < 0.001));
        }
        std::cout << "Test Passed: testCentroidCalculation3DComplex" << std::endl;
    }

    static void testExpectedClustering(const std::vector<Point> points, const std::vector<int> expectedClusterIds)
    {
        std::vector<int> ClusterIds(points.size(), -1);
        for (size_t i = 0; i < points.size(); ++i) { ClusterIds[i] = points[i].cluster_id; }
        std::map<int, int> cluster_map = buildClusterMap(points, expectedClusterIds);

        // map cluster_id names to expected cluster id names
        for (size_t i = 0; i < ClusterIds.size(); ++i) { ClusterIds[i] = cluster_map[ClusterIds[i]]; }
        // check if the result is correct
        for (size_t i = 0; i < ClusterIds.size(); ++i) { assert(ClusterIds[i] == expectedClusterIds[i]); }
        std::cout << "Test Passed: testExpectedClustering" << std::endl;
    }
    static std::map<int, int> buildClusterMap(const std::vector<Point> points, const std::vector<int> expectedCluster)
    {
        // needed to check up to permutation of cluster ids
        // i.e. 1,2,3,4 points assigned to 0-th cluster, 5,6,7,8 points assigned to 1-st cluster
        // so expectedClusterIds = {0, 0, 0, 0, 1, 1, 1, 1}
        // but realClusterIds could be {0, 0, 0, 0, 1, 1, 1, 1} or {1, 1, 1, 1, 0, 0, 0, 0} both of them are correct
        std::vector<int> ClusterIds(points.size(), -1);
        for (size_t i = 0; i < points.size(); ++i) { ClusterIds[i] = points[i].cluster_id; }
        assert(ClusterIds.size() == expectedCluster.size());
        std::map<int, int> cluster_map;
        for (size_t i = 0; i < expectedCluster.size(); ++i)
        {
            if (cluster_map.find(expectedCluster[i]) == cluster_map.end())
            {
                cluster_map[expectedCluster[i]] = points[i].cluster_id;
            }
            else
            {
                assert(cluster_map[expectedCluster[i]] == points[i].cluster_id);
            }
        }
        return cluster_map;
    }
};