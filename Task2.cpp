#include "Task2.h"
#include <cmath>
#include <vector>

miit::algebra::Task2::Task2(const size_t r, const size_t c, Generator& gen)
    : Exercise(r, c, gen)
{
    matrix.fill(generator);
}

void miit::algebra::Task2::solve()
{
    size_t r = matrix.getRows();
    size_t c = matrix.getCols();

    if (r == 0 || c == 0) return;

    int max_abs = std::abs(matrix[0][0]);
    for (size_t i = 0; i < r; ++i)
    {
        for (size_t j = 0; j < c; ++j)
        {
            int current_abs = std::abs(matrix[i][j]);
            if (current_abs > max_abs)
            {
                max_abs = current_abs;
            }
        }
    }

    for (int j = static_cast<int>(c) - 1; j >= 0; --j)
    {
        bool contains_max = false;
        for (size_t i = 0; i < r; ++i)
        {
            if (std::abs(matrix[i][j]) == max_abs)
            {
                contains_max = true;
                break;
            }
        }

        if (contains_max)
        {
            std::vector<int> zero_col(r, 0);
            matrix.insertCol(static_cast<size_t>(j) + 1, zero_col);
        }
    }
}
