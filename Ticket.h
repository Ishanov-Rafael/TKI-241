#pragma once
#include "Entity.h"

namespace miit::cinema
{
    /**
     * @brief Проданный билет на конкретное место сеанса
     */
    class Ticket final : public Entity
    {
    private:
        /** @brief 
         * ID сеанса, на который продан билет 
         */
        Id sessionId;
        /** 
         * @brief Номер места в зале, начиная с 1 
         */
        Quantity seat;
        /** 
         * @brief Цена билета на момент продажи в копейках 
         */
        Money price;
    public:
        /**
         * @brief Создаёт запись о проданном билете
         * @param sessionId Положительный ID сеанса
         * @param seat Положительный номер места
         * @param price Положительная цена билета в копейках
         * @throw std::invalid_argument Если ID, место или цена недопустимы
         * @throw std::overflow_error Если исчерпан диапазон ID
         */
        Ticket(const Id sessionId, const Quantity seat, const Money price);
        /**
         * @brief Возвращает ключ сеанса
         * @return ID сеанса
         */
        Id getSessionId() const noexcept;
        /**
         * @brief Возвращает номер места
         * @return Номер места в зале
         */
        Quantity getSeat() const noexcept;
        /**
         * @brief Возвращает цену билета
         * @return Цена в копейках
         */
        Money getPrice() const noexcept;
    };
}
