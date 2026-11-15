#pragma once
#include "Values.h"

namespace miit::cinema
{
    /**
     * @brief Базовый объект с положительным идентификатором логической записи
     */
    class Entity
    {
    private:
        /**
         * @brief Следующий свободный ключ
         */
        static Id nextId;
        /**
         * @brief Ключ логической записи, сохраняемый при копировании и перемещении
         */
        Id id;
        /**
         * @brief Выдаёт новый ключ без повторного использования старых
         * @return Положительный ID
         * @throw std::overflow_error Если диапазон ключей исчерпан
         */
        static Id createId();
    protected:
        /**
         * @brief Создаёт новую логическую запись с автоматически выданным ключом
         * @throw std::overflow_error Если диапазон ключей исчерпан
         */
        Entity();
    public:
        /**
         * @brief Виртуальный деструктор для корректного удаления наследников
         */
        virtual ~Entity() = default;
        /**
         * @brief Стандартный конструктор копирования
         * @param other Исходный объект
         */
        Entity(const Entity& other) = default;
        /**
         * @brief Стандартное присваивание копированием
         * @param other Объект, данные и ID которого заменяют текущие
         * @return Ссылка на текущий объект
         */
        Entity& operator=(const Entity& other) = default;
        /**
         * @brief Стандартный конструктор перемещения
         * @param other Объект, из которого переносятся данные
         */
        Entity(Entity&& other) noexcept = default;
        /**
         * @brief Стандартное присваивание перемещением
         * @param other Объект, из которого переносятся данные и ID
         * @return Ссылка на текущий объект
         */
        Entity& operator=(Entity&& other) noexcept = default;
        /**
         * @brief Возвращает идентификатор записи
         * @return Положительный ID
         */
        Id getId() const noexcept;
    };
}
