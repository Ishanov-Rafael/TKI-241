#pragma once
#include <string>

namespace miit::cinema
{
    /**
     * @brief Время суток с точностью до минуты, от 00:00 до 23:59
     */
    class TimeOfDay
    {
    private:
        /** @brief Часы от 0 до 23 */
        int hour;
        /** @brief Минуты от 0 до 59 */
        int minute;
    public:
        /**
         * @brief Создаёт время суток
         * @param hour Часы от 0 до 23
         * @param minute Минуты от 0 до 59
         * @throw std::invalid_argument Если часы или минуты вне допустимого диапазона
         */
        TimeOfDay(const int hour, const int minute);
        /**
         * @brief Читает время из строки
         * @param text Время строго в формате HH:MM
         * @throw std::invalid_argument Если формат неверен или время не существует
         */
        explicit TimeOfDay(const std::string& text);
        /**
         * @brief Возвращает число минут, прошедших с начала суток
         * @return Значение от 0 до 1439
         */
        int toMinutes() const noexcept;
        /**
         * @brief Сдвигает время на указанное число минут
         * @param minutes Число минут
         * @return Новое время в пределах тех же суток
         * @throw std::invalid_argument Если результат выходит за границы суток
         */
        TimeOfDay addMinutes(const int minutes) const;
        /**
         * @brief Формирует строку со временем
         * @return Время в формате HH:MM
         */
        std::string toString() const;
        /**
         * @brief Сравнивает моменты времени
         * @param other Время для сравнения
         * @return true, если текущее время раньше other
         */
        bool operator<(const TimeOfDay& other) const noexcept;
        /**
         * @brief Сравнивает моменты времени с учётом равенства
         * @param other Время для сравнения
         * @return true, если текущее время не позже other
         */
        bool operator<=(const TimeOfDay& other) const noexcept;
        /**
         * @brief Проверяет совпадение моментов времени
         * @param other Время для сравнения
         * @return true, если часы и минуты совпадают
         */
        bool operator==(const TimeOfDay& other) const noexcept;
    };
}
