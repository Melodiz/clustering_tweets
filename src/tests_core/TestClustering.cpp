#include "TestKmeansLogic.hpp"
#include "TestReadData.hpp"
#include "TestStructPoint.hpp"
#include "TestWriteData.hpp"
#include "TestKMeansND.hpp"


int main()
{
    TestPoint().runTests();

    TestInitializeRandomCentroids().runTests();
    TestRecalculateCentroids().runTests();
    TestAssignPointsToCentroids().runTests();

    TestReadData().runTests();
    TestWriteData().runTests();

    TestKMeansND().runTests();

    return 0;
}