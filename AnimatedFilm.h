#pragma once
#include "Film.h"

namespace miit::cinema
{
    /**
     * @brief Анимационный фильм с указанием техники анимации
     */
    class AnimatedFilm final : public Film
    {
    private:
        /** 
         * @brief Техника анимации 
         */
        std::string technique;
    public:
        /**
         * @brief Создаёт новый анимационный фильм
         * @param title Непустое название
         * @param durationMinutes Длительность в минутах
         * @param minAge Минимальный возраст зрителя от 0 до 21
         * @param synopsis Непустое краткое содержание
         * @param directors Непустой список режиссёров
         * @param actors Непустой список актёров озвучивания
         * @param technique Непустое название техники анимации
         * @throw std::invalid_argument Если любой из аргументов недопустим
         * @throw std::overflow_error Если исчерпан диапазон ID
         */
        AnimatedFilm(const std::string& title, const int durationMinutes, const int minAge,
            const std::string& synopsis, const std::vector<std::string>& directors,
            const std::vector<std::string>& actors, const std::string& technique);
        /**
         * @brief Возвращает технику анимации
         * @return Константная ссылка на название техники
         */
        const std::string& getTechnique() const noexcept;
        /**
         * @brief Возвращает название вида фильма
         * @return Строка "Мультфильм"
         */
        std::string getKind() const override;
        /**
         * @brief Формирует краткое описание фильма
         * @return Строка с названием, техникой, длительностью и возрастным ограничением
         */
        std::string toString() const override;
    };
}
