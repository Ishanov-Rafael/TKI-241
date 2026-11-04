#pragma once
#include "Generator.h"

namespace miit::algebra
{
    /**
    * @brief генератор который всегда возвращает всегда одно и то же константное число
    */
    class ConstGenerator : public Generator
    {
    private:
        /**
        * @brief константное значение возвращенное генератором
        */
        int value;
    public:
        /**
        * @brief конструктор генератора
        * @param val константное значение 
        */
        ConstGenerator(const int val = 0);
        /**
        * @brief возвращает константное значение
        * @return возвращает значение заданное в конструкторе 
        */
        int generate() override;
    };
}
