#pragma once
#include "Entity.h"
#include <string>
#include <vector>

namespace miit::cinema
{
    /**
     * @brief Абстрактный базовый класс фильма, который показывают в кинотеатре
     */
    class Film : public Entity
    {
    private:
        /** @brief Название фильма */
        std::string title;
        /** @brief Длительность фильма в минутах */
        int durationMinutes;
        /** @brief Минимальный возраст зрителя, 0 означает отсутствие ограничения */
        int minAge;
        /** @brief Краткое содержание фильма */
        std::string synopsis;
        /** @brief Режиссёры фильма */
        std::vector<std::string> directors;
        /** @brief Актёры, задействованные в фильме */
        std::vector<std::string> actors;
    protected:
        /**
         * @brief Создаёт новую запись фильма
         * @param title Непустое название
         * @param durationMinutes Положительная длительность в минутах
         * @param minAge Минимальный возраст зрителя от 0 до 21
         * @param synopsis Непустое краткое содержание
         * @param directors Непустой список режиссёров без пустых имён
         * @param actors Непустой список актёров без пустых имён
         * @throw std::invalid_argument Если любой из аргументов недопустим
         * @throw std::overflow_error Если исчерпан диапазон ID
         */
        Film(const std::string& title, const int durationMinutes, const int minAge,
            const std::string& synopsis, const std::vector<std::string>& directors,
            const std::vector<std::string>& actors);
    public:
        /**
         * @brief Виртуальный деструктор базового класса фильмов
         */
        virtual ~Film() = default;
        /**
         * @brief Стандартный конструктор копирования
         * @param other Исходный объект
         */
        Film(const Film& other) = default;
        /**
         * @brief Стандартное присваивание копированием
         * @param other Объект, данные и ID которого заменяют текущие
         * @return Ссылка на текущий объект
         */
        Film& operator=(const Film& other) = default;
        /**
         * @brief Стандартный конструктор перемещения
         * @param other Объект, из которого переносятся данные
         */
        Film(Film&& other) noexcept = default;
        /**
         * @brief Стандартное присваивание перемещением
         * @param other Объект, из которого переносятся данные и ID
         * @return Ссылка на текущий объект
         */
        Film& operator=(Film&& other) noexcept = default;
        /**
         * @brief Возвращает название фильма
         * @return Константная ссылка на название
         */
        const std::string& getTitle() const noexcept;
        /**
         * @brief Возвращает длительность фильма
         * @return Длительность в минутах
         */
        int getDurationMinutes() const noexcept;
        /**
         * @brief Возвращает минимальный возраст зрителя
         * @return Возраст в годах, 0 если ограничения нет
         */
        int getMinAge() const noexcept;
        /**
         * @brief Проверяет наличие возрастного ограничения
         * @return true, если минимальный возраст больше нуля
         */
        bool hasAgeRestriction() const noexcept;
        /**
         * @brief Формирует текст возрастного ограничения
         * @return Строка вида «16+» либо «без ограничений»
         */
        std::string getAgeRestrictionText() const;
        /**
         * @brief Возвращает краткое содержание
         * @return Константная ссылка на текст содержания
         */
        const std::string& getSynopsis() const noexcept;
        /**
         * @brief Возвращает режиссёров фильма
         * @return Константная ссылка на список режиссёров
         */
        const std::vector<std::string>& getDirectors() const noexcept;
        /**
         * @brief Возвращает актёров, задействованных в фильме
         * @return Константная ссылка на список актёров
         */
        const std::vector<std::string>& getActors() const noexcept;
        /**
         * @brief Формирует полную справку: содержание, режиссёры и актёры
         * @return Многострочный текст для вывода в приложении
         */
        std::string getInfo() const;
        /**
         * @brief Возвращает название вида фильма
         * @return Строка, определяемая классом-наследником
         */
        virtual std::string getKind() const = 0;
        /**
         * @brief Формирует краткое описание конкретного вида фильма
         * @return Строка, определяемая классом-наследником
         */
        virtual std::string toString() const = 0;
    };
}
