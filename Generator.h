#pragma once

namespace miit::algebra
{
    /**
     * @brief базовый абстрактный класс генератора чисел
     */
    class Generator
    {
    public:
        /**
        * @brief виртуальный диструктор
        */
        virtual ~Generator() = default;
        /**
        * @brief генерирует очередное число
        * @return сгенериованное целое число
        */
        virtual int generate() = 0;
    };
}
