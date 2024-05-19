# Commits Changes summary

## Commit #1d5f553 "regrouping files, split modules"[Pull-link](https://github.com/Melodiz/clustering_tweets/pull/6)


- move "clustering_core/", "visualizing/", "tests_core/", "embeddings_core/" to "src/"
- split "KmeansND.h" to 5 modules:
  - kMeansLogic.hpp (k-means algorithm)
  - readData.hpp, (read files Modules)
  - structPoint.hpp (implementation of struct Point)
  - writeData.hpp (save result modules)
  - clusterTools.hpp (some methods, i.e. returnClustersSize)
- split complecated functions to easy-to-read modules. (S.O.L.I.D.)
  - readData to "read_from_csv", "read_from_npy", "read_from_txt"
  - saveData to "save_to_csv", "save_to_npy", "save_to_txt"
  - same idea for SaveClusters and so forth.
- implement .save() function for KMeansND class, which save result of clustering and centroids to corresponding files and take into account flag _with_coordinates, for reduce memory usage in higher dimentions

## Commit #23f1af4 "implement Doc. for modules"[Pull-link](https://github.com/Melodiz/clustering_tweets/pull/6)


- implement documentation files to "documentation/"
  - clusterTools.md
  - KMeansLogic.md
  - readData.md
  - structPoint.md
  - writeData.md

- implement in-code documentation in some modules files. Trying to avoid over-commenting, write intuitive-understandable code and self-explained names. All Docs. in "documentation/"

## Commit #6aa74d4 "Tests and Fixes"[Pull-link](https://github.com/Melodiz/clustering_tweets/pull/6)


- implement tests for all modules (with samples and checking output files)
- fixed consturctors in Struct Point
- implement operators overloading for struct Point
- add .norm() method for struct Point (calculate the norm of vector)
- fix writing modules, now they save proper headers
- implement a feature in reading modules: now recognize if it's clustered points and save them correctly
- add instruction how to install g-tests locally. (change to build-in further)

## Commit #9988f6b "Fix ClusteringND + tests"[Pull-link](https://github.com/Melodiz/clustering_tweets/pull/6)


- add tests for all constructors of Point structure
- fix recalculate centroids module
- fix assigToCentroid module
- fix tests for recalculate and assigToCentroid modules
- implement debugShowFullData function in clusterTools
- implement AllReseanable tests for KMeansND
- fix all bugs in Clustering Logic and KMeansND as well
- since now code is tested and guaranteed to be stable, remove non-obligatory ckecks in KMeansND

## Commit #c62065c "Doc. for Tests and Modules"[Pull-link](https://github.com/Melodiz/clustering_tweets/pull/6)

- rewrite docs for modules, take changes into account
- implement a docs for tests
- add changeLog.md, to store the summary of commits

## Commit #e0f2386 "update readme.md" [Pull-link](https://github.com/Melodiz/clustering_tweets/pull/7)

- Update README.md to include details about the clustering core's current implementation.
- Add clustering.cpp to demonstrate the use of KMeansND.hpp for raw data clustering.

## Commit #ca82e02 "Handle bigData for showcase" [Pull-link](https://github.com/Melodiz/clustering_tweets/pull/9)

- processing data for half-million set on external server
- implementing Clustering.cpp file
- implement .json file with pathes 
- clustering 2D locally
- Orginize data
- Upload compresed data files to disk

## Commit #85286a0 "Clustering sort & relevant choose & test" [Pull-link](https://github.com/Melodiz/clustering_tweets/pull/9)

- Fix typos in README.md
- Create new directory "data_processing" for handling pre-processed data
- Implement ClusterRelevantInfo.hpp in "modules/" which choose k relevant points near given point. (for choosing logic check the documentation)
- Implement SortingClusters.hpp in "modules/"
- Implement Cluster class with typedef Clusters
- Implement tests:
  - For constructor of Cluster class
  - For sorting points
  - For getRelevantNeighbors
- Extend TestClustering.cpp with tests for data_processing

## Commit #f6828b2 "Enhance Clustering & Visualization" [Pull-link](https://github.com/Melodiz/clustering_tweets/pull/9)

- Implement ReduceClusterSizes.hpp, which can:
  - Combine files of points coordinates, cluster_ids, centroids to singe vector of Points with cluster_id & distance
  - read Centroids files
  - read ClusterIds files
- add returnClusters method, which form vector of type Cluster, from vector of Points and vector of Centroids
- build 2D map of clustered points
- name all the clusters using gpt4o, with 112k tokens context
- add scatter plots to data/samples
- add names.json to data/ wich contains names of clusters
- implement test for ReduceClusterSizes.hpp

## Commit #... "Doc. for ReduceClusterSizes & ClusterTools" [Pull-link](https://github.com/Melodiz/clustering_tweets/pull/9)

- move paths.json to "data/"
- implement documentation for:
  - Cluster.hpp
  - ClusterRelevantInfo.hpp
  - TestClusterRelevantInfo.hpp
  - TestCluster.hpp
  - ClusterTools.hpp





