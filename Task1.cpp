#include "Task1.h"
#include <cmath>

miit::algebra::Task1::Task1(const size_t r, const size_t c, Generator& gen)
    : Exercise(r, c, gen)
{
    matrix.fill(generator);
}

void miit::algebra::Task1::solve()
{
    size_t r = matrix.getRows();
    size_t c = matrix.getCols();

    if (r == 0 || c == 0) return;

    int maxAbsVal = std::abs(matrix[0][0]);
    int maxElement = matrix[0][0];

    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            int current = matrix[i][j];
            int currentAbs = std::abs(current);
            if (currentAbs > maxAbsVal) {
                maxAbsVal = currentAbs;
                maxElement = current;
            }
        }
    }

    for (size_t j = 0; j < c; ++j) {
        for (size_t i = 0; i < r; ++i) {
            if (matrix[i][j] == 0) {
                matrix[i][j] = maxElement;
            }
        }
    }
}
