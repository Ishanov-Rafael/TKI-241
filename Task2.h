#pragma once
#include "Exercise.h"

namespace miit::algebra
{
    /**
     * @brief Класс для реализации второго задания (Вариант 10)
     */
    class Task2 : public Exercise
    {
    public:
        /**
         * @brief Конструктор класса Task2
         * @param r Количество строк
         * @param c Количество столбцов
         * @param gen Ссылка на генератор
         */
        Task2(const size_t r, const size_t c, const Generator& gen);

        /**
         * @brief Вставляет столбец из нулей после каждого столбца, содержащего максимальный по модулю элемент
         */
        void solve() override;
    };
}
