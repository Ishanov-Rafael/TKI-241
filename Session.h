#pragma once
#include "Entity.h"
#include "Date.h"
#include "TimeOfDay.h"

namespace miit::cinema
{
    /**
     * @brief Сеанс: показ фильма в зале в установленные дату и время
     */
    class Session final : public Entity
    {
    private:
        /** @brief ID зала, в котором идёт сеанс */
        Id hallId;
        /** @brief ID фильма, который показывают на сеансе */
        Id filmId;
        /** @brief Дата сеанса */
        Date date;
        /** @brief Время начала сеанса */
        TimeOfDay start;
        /** @brief Время окончания сеанса */
        TimeOfDay end;
        /** @brief Цена одного билета на сеанс в копейках */
        Money price;
    public:
        /**
         * @brief Создаёт сеанс
         * @param hallId Положительный ID зала
         * @param filmId Положительный ID фильма
         * @param date Дата сеанса
         * @param start Время начала сеанса
         * @param durationMinutes Положительная длительность сеанса в минутах
         * @param price Положительная цена билета в копейках
         * @throw std::invalid_argument Если ID, длительность или цена недопустимы либо сеанс заканчивается после полуночи
         * @throw std::overflow_error Если исчерпан диапазон ID
         */
        Session(const Id hallId, const Id filmId, const Date& date, const TimeOfDay& start,
            const int durationMinutes, const Money price);
        /**
         * @brief Возвращает ключ зала
         * @return ID зала
         */
        Id getHallId() const noexcept;
        /**
         * @brief Возвращает ключ фильма
         * @return ID фильма
         */
        Id getFilmId() const noexcept;
        /**
         * @brief Возвращает дату сеанса
         * @return Константная ссылка на дату
         */
        const Date& getDate() const noexcept;
        /**
         * @brief Возвращает время начала
         * @return Константная ссылка на время начала
         */
        const TimeOfDay& getStart() const noexcept;
        /**
         * @brief Возвращает время окончания
         * @return Константная ссылка на время окончания
         */
        const TimeOfDay& getEnd() const noexcept;
        /**
         * @brief Возвращает цену билета
         * @return Цена в копейках
         */
        Money getPrice() const noexcept;
        /**
         * @brief Проверяет, идёт ли сеанс в указанный момент
         * @param moment Дата проверяемого момента
         * @param time Время проверяемого момента
         * @return true, если сеанс уже начался и ещё не закончился
         */
        bool isRunningAt(const Date& moment, const TimeOfDay& time) const noexcept;
        /**
         * @brief Проверяет пересечение с другим сеансом в том же зале
         * @param other Другой сеанс
         * @return true, если зал и дата совпадают, а интервалы времени пересекаются
         */
        bool overlaps(const Session& other) const noexcept;
    };
}
