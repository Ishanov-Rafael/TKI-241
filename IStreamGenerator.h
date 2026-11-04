#pragma once
#include "Generator.h"
#include <iostream>

namespace miit::algebra
{
    /**
    * @brief генератор который считывает чсила из входного числа
    */
    class IStreamGenerator : public Generator
    {
    private:
        /**
        * @brief ссылка на входной поток из которого считывается точка
        */
        std::istream& in;

    public:
        /**
        * @brief конструктор генератора
        * @param in входной поток
        */
        IStreamGenerator(std::istream& in = std::cin);
        /**
        * @brief считытвает очередное число из потока
        * @return число считанное из входного потока
        */
        int generate() override;
    };
}
