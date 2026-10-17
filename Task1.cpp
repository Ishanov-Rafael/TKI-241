#include "Task1.h"
#include <cmath>
#include <algorithm>

miit::algebra::Task1::Task1(const size_t r, const size_t c, Generator& gen)
    : Exercise(r, c, gen)
{
}

void miit::algebra::Task1::solve()
{
    size_t r = matrix.getRows();
    size_t c = matrix.getCols();

    if (r == 0 || c == 0) return;

    for (size_t j = 0; j < c; ++j)
    {
        int max_abs_val = std::abs(matrix[0][j]);
        for (size_t i = 1; i < r; ++i)
        {
            int current_abs = std::abs(matrix[i][j]);
            if (current_abs > max_abs_val)
            {
                max_abs_val = current_abs;
            }
        }

        for (size_t i = 0; i < r; ++i)
        {
            if (matrix[i][j] == 0)
            {
                matrix[i][j] = max_abs_val;
            }
        }
    }
}
