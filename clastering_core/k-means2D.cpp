#include <algorithm>
#include <cmath>
#include <fstream>// for file-reading
#include <iostream>
#include <string>
#include <vector>


// implementation of each point
struct Point {
    std::vector<double> coords;// coordinates of the point
    int cluster;               // cluster to which the point is assigned
    double distance;           // distance to the centroid of the assigned cluster

    // constructor
    Point(std::vector<double> coords, int cluster, double distance) : coords(coords), cluster(cluster), distance(distance){};

    // default constructor
    Point()
    {
        // since we don't know the coordinates of the point, we set them to 0
        // standart model for embeddings is 384 dimensional "all-minilm"
        coords = std::vector<double>();// zere vector in 384 dimensions
        cluster = -1;                  // unassigned
        distance = __DBL_MAX__;        // infinity
    }
    Point(const std::vector<double>& coords) : coords(coords), cluster(-1), distance(__DBL_MAX__){};

    // calculate the distance between two points
    double dist(Point other)
    {
        double sum = 0;
        for (int i = 0; i < coords.size(); i++)
        {
            sum += pow((coords[i] - other.coords[i]), 2);
        }
        return std::sqrt(sum);
    }
};

// reading the data from csv file

std::vector<Point> read_data(const std::string& filePath)
{
    // file contains x and y coordinates
    std::vector<Point> points = {};
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return points;
    }
    std::cout << "Reading..." << filePath << std::endl;
    std::string line;
    std::getline(file, line); // skip the header line
    while (std::getline(file, line))
    {
        std::vector<double> coords = {};
        double x = std::stoi(line.substr(0, line.find(',')));
        double y = std::stoi(line.substr(line.find(',') + 1));
        coords.push_back(x);
        coords.push_back(y);
        points.push_back(Point(coords));
    }

    file.close();
    return points;
}


std::vector<Point> initialize_random_centroids(const std::vector<Point>& points, int k)
{
    std::vector<Point> centroids;// assignment of the centroids
    for (int i = 0; i < k; i++)
    {
        int index = rand() % points.size();// random index of the point
        centroids.push_back(points[index]);// add the point to the centroids
        centroids[i].cluster = i;          // assign the cluster to the centroid
        centroids[i].distance = 0;         // set the distance to 0
    }
    return centroids;
}


int assignPointsToClasters(std::vector<Point>& points, const std::vector<Point>& centroids)
{
    // assign each point to the closest centroid
    int changed = 0;// number of changed points
    for (int i = 0; i < points.size(); i++)
    {
        double min_distance = __DBL_MAX__;        // set to infinity
        int min_index = -1;                       // index of the closest centroid, default -1
        for (int j = 0; j < centroids.size(); j++)// for each centroid
        {
            double distance = points[i].dist(centroids[j]);// calculate the distance
            // if the distance is smaller than the current minimum distance
            if (distance < min_distance)
            {
                min_distance = distance;// update the minimum distance
                min_index = j;          // update the index of the closest centroid
            }
        }
        if (points[i].cluster != min_index)// if the point is not assigned to the closest centroid
        {
            changed++;                        // increment the number of changed points
            points[i].cluster = min_index;    // assign the point to the closest centroid
            points[i].distance = min_distance;// update the distance to the centroid
        }
    }
    return changed;// return the number of changed points
}
void recalculateCentroids(std::vector<Point>& points, std::vector<Point>& centroids)
{
    // recalculate the centroids
    for (int i = 0; i < centroids.size(); i++)// for each centroid
    {
        std::vector<double> newCentroid;                    // new coordinates of the centroid
        for (int j = 0; j < centroids[i].coords.size(); j++)// for each coordinate
        {
            double sum = 0;                        // sum of the coordinates
            for (int k = 0; k < points.size(); k++)// for each point
            {
                if (points[k].cluster == i)// if the point is assigned to the centroid
                {
                    sum += points[k].coords[j];// add the coordinate to the sum
                }
            }
            newCentroid.push_back(sum / points.size());// add the average coordinate to the new centroid
        }
        centroids[i].coords = newCentroid;// update the centroid
    }
}

void kMeansClustering(std::vector<Point>& points, int epochs, int k)
{
    // pints is all points in the dataset
    // k is the number of clusters
    // epochs is the number of iterations

    // initialize the centroids for first time
    std::vector<Point> centroids = initialize_random_centroids(points, k);

    std::cout << "Initializing..." << std::endl;
    int changed = 0;// number of changed points
    for (int i = 0; i < epochs; i++)
    {
        std::cout << "Iteration " << i + 1 << "..." << std::endl;
        // recalculate the centroids
        changed = assignPointsToClasters(points, centroids);
        // assign each point to the closest centroid
        recalculateCentroids(points, centroids);
        std::cout << "Points changed: " << changed << std::endl;
        if (changed == 0)// if there are no changed points
            break;
    }
    std::cout << "Clusterization done successfully" << std::endl;
    // finally assign each point to the closest centroid
    assignPointsToClasters(points, centroids);
}

void save_result_to_csv(const std::vector<Point>& points, const std::string& filename)
{
    // save the result to the csv file
    // in the format:
    // point_index, cluster, distance from the centroid
    // since we don's change order the points, we can use the index of the point
    std::cout << "Saving..." << std::endl;
    std::ofstream file(filename);
    if (!file.is_open())// if the file is not open then error out
    {
        std::cout << "Error saving the file" << std::endl;
        return;
    }
    // save headers
    file << "id" << "," << "cluster" << "," << "distance" << "\n";

    // save the data to the file
    for (int i = 0; i < points.size(); i++)// for each point
    {
        file << i << ',' << std::to_string(points[i].cluster) << ',' << points[i].distance << '\n';
    }
    std::cout << "Saved to: " << filename << std::endl;// successfully saved
    file.close();
}

int main()
{

    // read the data from the npy file
    std::string filePathTSNE = "../data/train_embeddings_tsne.csv";
    std::vector<Point> points = read_data(filePathTSNE);

    // start the clustering...
    // hyper-parameters:
    int k = 20;     // number of clusters
    int epochs = 100;// number of iterations
    kMeansClustering(points, epochs, k);
    // save the result to the csv file
    std::string filename = "../data/TSNE_train_embeddings_clusters.csv";
    save_result_to_csv(points, filename);
    // done
    return 0;
}