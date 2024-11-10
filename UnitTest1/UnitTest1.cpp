#include "pch.h"
#include <CppUnitTest.h>
#include <fstream>
#include <stdexcept>
#include "../PDC_LAB10/source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(GraphTests)
    {
    public:
        TEST_METHOD(TestLoadGraph) {
            const char* inputFilename = "test_in.txt";
            std::ofstream testFile(inputFilename);
            testFile << "4 5\n1 2 10\n1 3 15\n2 3 5\n2 4 20\n3 4 10\n";
            testFile.close();

            int n, m;
            int** weightMatrix = nullptr;
            loadGraph(inputFilename, weightMatrix, n, m);

            Assert::AreEqual(n, 4);
            Assert::AreEqual(m, 5);
            Assert::AreEqual(weightMatrix[0][1], 10);
            Assert::AreEqual(weightMatrix[1][2], 5);

            freeMatrix(weightMatrix, n);
        }

        TEST_METHOD(TestPrintMatrix) {
            const char* outputFilename = "test_out.txt";
            const int n = 4;
            int** weightMatrix = new int* [n];
            for (int i = 0; i < n; ++i) {
                weightMatrix[i] = new int[n] { INF, INF, INF, INF };
            }
            weightMatrix[0][1] = 10;
            weightMatrix[1][2] = 5;
            weightMatrix[2][3] = 10;

            printMatrix(weightMatrix, n, outputFilename);

            std::ifstream outFile(outputFilename);
            std::string outputLine;
            bool foundINF = false;
            while (std::getline(outFile, outputLine)) {
                if (outputLine.find("INF") != std::string::npos) {
                    foundINF = true;
                    break;
                }
            }

            Assert::IsTrue(foundINF);

            freeMatrix(weightMatrix, n);
        }

        TEST_METHOD(TestFreeMatrix) {
            const int n = 4;
            int** weightMatrix = new int* [n];
            for (int i = 0; i < n; ++i) {
                weightMatrix[i] = new int[n] { INF, INF, INF, INF };
            }

            try {
                freeMatrix(weightMatrix, n);
                Assert::IsTrue(true);
            }
            catch (...) {
                Assert::Fail(L"Exception thrown during matrix deletion");
            }
        }
    };
}
