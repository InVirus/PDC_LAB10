#include <iostream>
#include <fstream>
#include <Windows.h>

const int INF = 1000000000;

void loadGraph(const char* filename, int**& matrix, int& n, int& m) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Помилка відкриття файлу." << std::endl;
        return;
    }

    file >> n >> m;

    if (n <= 0 || m < 0) {
        std::cerr << "Некоректні значення для n або m." << std::endl;
        return;
    }

    matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = INF;
        }
        matrix[i][i] = 0;
    }

    int u, v, w;
    for (int i = 0; i < m; ++i) {
        file >> u >> v >> w;
        if (u < 1 || u > n || v < 1 || v > n) {
            std::cerr << "Помилка: індекси ребер виходять за межі матриці. u=" << u << ", v=" << v << std::endl;
            continue;
        }
        matrix[u - 1][v - 1] = w;
    }

    file.close();
}

void printMatrix(int** matrix, int n, const char* outputFile) {
    std::ofstream file(outputFile);
    if (!file) {
        std::cerr << "Помилка відкриття файлу для запису." << std::endl;
        return;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == INF) {
                std::cout << "INF ";
                file << "INF ";
            }
            else {
                std::cout << matrix[i][j] << " ";
                file << matrix[i][j] << " ";
            }
        }
        std::cout << std::endl;
        file << std::endl;
    }

    file.close();
}

void freeMatrix(int** matrix, int n) {
    if (matrix != nullptr) {
        for (int i = 0; i < n; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const char* inputFilename = "in.txt";
    const char* outputFilename = "out.txt";
    int n, m;
    int** matrix = nullptr;

    loadGraph(inputFilename, matrix, n, m);

    if (matrix != nullptr) {
        printMatrix(matrix, n, outputFilename);
        freeMatrix(matrix, n);
    }

    return 0;
}
