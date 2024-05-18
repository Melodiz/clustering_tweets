#include "KmeansND.hpp"
#include <string>


void clusterRow(const std::string& embPath, const std::string& saveToPath, const std::string& saveToCentroidsPath, int k, int maxIters);
void clusterTSNE(const std::string& tsnePath, const std::string& saveToPath2D, const std::string& saveToCentroidsPath2D, int k, int maxIters);
int main()
{
    std::string embPath = "../../data/big_data/embeddings.npy";
    std::string tsnePath = "../../data/big_data/t-SNE_projected.csv";

    std::string saveToPath = "../../data/big_data/rowClustered.csv";
    std::string saveToPath2D = "../../data/big_data/tsneClustered.csv";

    std::string saveToCentroidsPath = "../../data/big_data/rowCentroids.csv";
    std::string saveToCentroidsPath2D = "../../data/big_data/centroids2D.csv";

    int k = 25;
    int maxIters = 50;

    clusterRow(embPath, saveToPath, saveToCentroidsPath, k, maxIters);
    // clusterTSNE(tsnePath, saveToPath2D, saveToCentroidsPath2D, k, maxIters);

    return 0;
}

void clusterRow(const std::string& embPath, const std::string& saveToPath, const std::string& saveToCentroidsPath, int k, int maxIters)
{
    std::cout << "Clustering rows..." << std::endl;
    KMeansND kmeans(k, maxIters, embPath, saveToCentroidsPath, saveToPath);
    kmeans.setWithCoordinates(false);
    std::cout << "Initialization done. Starting clustering...";

    kmeans.Cluster(true);
    std::cout << "Clustering done." << std::endl;
    kmeans.save();
    std::cout << "saved to " << saveToPath << std::endl;
}

void clusterTSNE(const std::string& tsnePath, const std::string& saveToPath2D, const std::string& saveToCentroidsPath2D, int k, int maxIters)
{
    std::cout << "Clustering t-SNE..." << std::endl;
    std::cout << tsnePath << std::endl;
    std::cout << saveToPath2D << std::endl;
    std::cout << saveToCentroidsPath2D << std::endl;
    std::cout << k << std::endl;
    std::cout << maxIters << std::endl;
    KMeansND kmeans(k, maxIters, tsnePath, saveToCentroidsPath2D, saveToPath2D);
    kmeans.setWithCoordinates(true);
    std::cout << "Initialization done. Starting clustering...";
    std::cout << kmeans.getPoints().size() << std::endl;
    std::cout << kmeans.getPoints()[0].coords.size() << std::endl;
    kmeans.Cluster(true);
    std::cout << "Clustering done." << std::endl;
    kmeans.save();
    std::cout << "saved to " << saveToPath2D << std::endl;
}