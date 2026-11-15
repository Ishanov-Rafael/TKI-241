#pragma once
#include "Entity.h"
#include <string>

namespace miit::cinema
{
    /**
     * @brief Зал кинотеатра с фиксированным числом мест
     */
    class Hall final : public Entity
    {
    private:
        /** @brief Название зала */
        std::string name;
        /** @brief Число зрительских мест в зале */
        Quantity seats;
    public:
        /**
         * @brief Создаёт новый зал
         * @param name Непустое название зала
         * @param seats Положительное число мест
         * @throw std::invalid_argument Если название пусто или число мест неположительно
         * @throw std::overflow_error Если исчерпан диапазон ID
         */
        Hall(const std::string& name, const Quantity seats);
        /**
         * @brief Возвращает название зала
         * @return Константная ссылка на название
         */
        const std::string& getName() const noexcept;
        /**
         * @brief Возвращает число мест в зале
         * @return Количество мест
         */
        Quantity getSeats() const noexcept;
    };
}
