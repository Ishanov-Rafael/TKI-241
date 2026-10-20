#include "Task2.h"
#include <cmath>
#include <vector>

miit::algebra::Task2::Task2(const size_t r, const size_t c, Generator& gen)
    : Exercise(r, c, gen)
{
}

void miit::algebra::Task2::solve()
{
    size_t r = matrix.getRows();
    size_t c = matrix.getCols();

    if (r == 0 || c == 0) return;

    int maxAbsVal = std::abs(matrix[0][0]);
    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            if (std::abs(matrix[i][j]) > maxAbsVal) {
                maxAbsVal = std::abs(matrix[i][j]);
            }
        }
    }

    for (int j = static_cast<int>(c) - 1; j >= 0; --j) {
        bool containsMax = false;
        for (size_t i = 0; i < r; ++i) {
            if (std::abs(matrix[i][j]) == maxAbsVal) {
                containsMax = true;
                break;
            }
        }

        if (containsMax) {
            std::vector<int> zeroCol(r, 0);
            matrix.insertCol(static_cast<size_t>(j) + 1, zeroCol);
        }
    }
}
