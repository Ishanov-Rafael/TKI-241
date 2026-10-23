#pragma once

namespace miit::algebra
{
    /**
     * @brief базовый абстрактный класс генератора чисел
     */
    class Generator
    {
    public:
        virtual ~Generator() = default;
        virtual int generate() = 0;
    };
}
