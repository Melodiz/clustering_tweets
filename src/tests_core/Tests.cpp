#include "TestKmeansLogic.hpp"
#include "TestReadData.hpp"
#include "TestStructPoint.hpp"
#include "TestWriteData.hpp"
#include "TestKMeansND.hpp"
#include "TestClusters.hpp"
#include "TestClusterRelevantInfo.hpp"

int main()
{
    TestPoint().runTests();

    TestInitializeRandomCentroids().runTests();
    TestRecalculateCentroids().runTests();
    TestAssignPointsToCentroids().runTests();

    TestReadData().runTests();
    TestWriteData().runTests();

    TestKMeansND().runTests();
    TestClusterConstructo().runTests();
    TestClusterSort().runTests();
    TestClusterNeighbors().runTests();


    std::cout << "\n=========================\n";
    std::cout << "    All Tests Passed!";
    std::cout << "\n=========================\n";

    return 0;
}