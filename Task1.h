#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Класс для реализации первого задания 
     */
    class Task1 : public Exercise
    {
    public:
        /**
         * @brief Конструктор класса Task1
         * @param r Количество строк
         * @param c Количество столбцов
         * @param gen Ссылка на генератор
         */
        Task1(const size_t r, const size_t c, Generator& gen);

        /**
         * @brief Заменяет нулевой элемент каждого столбца максимальным по модулю элементом столбца
         */
        void solve() override;
    };
}
