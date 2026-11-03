#pragma once
#include "Generator.h"
#include <random>

namespace miit::algebra
{
    /**
    * @brief генератор случайных целых чисел из заданного диапозона
    */
    class RandomGenerator : public Generator
    {
    private:
        /**
        * @brief равномерное распределение целых чисел на отрезке min, max
        */
        std::uniform_int_distribution<int> distribution;
        /**
        * @brief генератор псевдослучайных чисел
        */
        std::mt19937 generator;
    public:
        /**
        * @brief конструктор генератора
        * @param min нижняя граница диапозона
        * @param max верхняя граница диапозона
        */
        RandomGenerator(const int min, const int max);
        /**
        * @brief генерирует случайное число из заданного диапозона
        * @return возвращает случайное число на отрезке min, max
        */
        int generate() override;
    };
}
