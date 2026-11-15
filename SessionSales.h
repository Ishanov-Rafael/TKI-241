#pragma once
#include "Values.h"

namespace miit::cinema
{
    /**
     * @brief Итог продаж билетов на один сеанс
     */
    class SessionSales
    {
    private:
        /** @brief ID сеанса */
        Id sessionId;
        /** @brief Количество проданных билетов */
        Quantity ticketsSold;
        /** @brief Выручка от продажи билетов в копейках */
        Money revenue;
    public:
        /**
         * @brief Создаёт итог продаж по сеансу
         * @param sessionId Положительный ID сеанса
         * @param ticketsSold Неотрицательное число проданных билетов
         * @param revenue Неотрицательная выручка в копейках
         * @throw std::invalid_argument Если ID равен нулю либо количество или выручка отрицательны
         */
        SessionSales(const Id sessionId, const Quantity ticketsSold, const Money revenue);
        /**
         * @brief Возвращает ключ сеанса
         * @return ID сеанса
         */
        Id getSessionId() const noexcept;
        /**
         * @brief Возвращает число проданных билетов
         * @return Количество билетов
         */
        Quantity getTicketsSold() const noexcept;
        /**
         * @brief Возвращает выручку по сеансу
         * @return Сумма в копейках
         */
        Money getRevenue() const noexcept;
    };
}
