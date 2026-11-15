#pragma once
#include <cstdint>
#include <string>

namespace miit::cinema
{
    /**
     * @brief Тип положительного идентификатора логической записи
     */
    using Id = std::uint64_t;
    /**
     * @brief Целое количество: билеты, места, минуты
     */
    using Quantity = std::int64_t;
    /**
     * @brief Целая денежная сумма в копейках
     */
    using Money = std::int64_t;

    /**
     * @brief Удаляет по краям пробелы, табуляцию и переводы строк
     * @param text Проверяемая строка
     * @return Очищенная непустая строка
     * @throw std::invalid_argument Если после очистки строка пуста
     */
    std::string requireText(const std::string& text);
    /**
     * @brief Проверяет положительность ключа
     * @param id Проверяемый ID
     * @throw std::invalid_argument Если ID равен нулю
     */
    void requireId(const Id id);
    /**
     * @brief Складывает два неотрицательных числа с проверкой переполнения
     * @param left Первое число
     * @param right Второе число
     * @return Сумма чисел
     * @throw std::invalid_argument Если аргумент отрицателен
     * @throw std::overflow_error Если результат не помещается в int64_t
     */
    std::int64_t checkedAdd(const std::int64_t left, const std::int64_t right);
    /**
     * @brief Форматирует денежную сумму без вычислений с плавающей точкой
     * @param value Неотрицательная сумма в копейках
     * @return Строка вида «125.50 руб.»
     * @throw std::invalid_argument Если сумма отрицательна
     */
    std::string formatMoney(const Money value);
}
