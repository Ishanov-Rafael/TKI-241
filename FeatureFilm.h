#pragma once
#include "Film.h"

namespace miit::cinema
{
    /**
     * @brief Художественный фильм с указанием жанра
     */
    class FeatureFilm final : public Film
    {
    private:
        /** @brief Жанр фильма */
        std::string genre;
    public:
        /**
         * @brief Создаёт новый художественный фильм
         * @param title Непустое название
         * @param durationMinutes Длительность в минутах
         * @param minAge Минимальный возраст зрителя от 0 до 21
         * @param synopsis Непустое краткое содержание
         * @param directors Непустой список режиссёров
         * @param actors Непустой список актёров
         * @param genre Непустое название жанра
         * @throw std::invalid_argument Если любой из аргументов недопустим
         * @throw std::overflow_error Если исчерпан диапазон ID
         */
        FeatureFilm(const std::string& title, const int durationMinutes, const int minAge,
            const std::string& synopsis, const std::vector<std::string>& directors,
            const std::vector<std::string>& actors, const std::string& genre);
        /**
         * @brief Возвращает жанр фильма
         * @return Константная ссылка на жанр
         */
        const std::string& getGenre() const noexcept;
        /**
         * @brief Возвращает название вида фильма
         * @return Строка «Художественный фильм»
         */
        std::string getKind() const override;
        /**
         * @brief Формирует краткое описание фильма
         * @return Строка с названием, жанром, длительностью и возрастным ограничением
         */
        std::string toString() const override;
    };
}
