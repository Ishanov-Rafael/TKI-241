#pragma once
#include "Values.h"
#include <vector>

namespace miit::cinema
{
    /**
     * @brief Программа зала на день: какие фильмы идут в этом зале
     */
    class HallProgram
    {
    private:
        /** 
         * @brief ID зала 
         */
        Id hallId;
        /** 
         * @brief ID фильмов зала без повторов в порядке начала сеансов 
         */
        std::vector<Id> filmIds;
    public:
        /**
         * @brief Создаёт программу зала
         * @param hallId Положительный ID зала
         * @param filmIds Список ID фильмов, идущих в зале
         * @throw std::invalid_argument Если ID зала или любой ID фильма равен нулю
         */
        HallProgram(const Id hallId, const std::vector<Id>& filmIds);
        /**
         * @brief Возвращает ключ зала
         * @return ID зала
         */
        Id getHallId() const noexcept;
        /**
         * @brief Возвращает ключи фильмов зала
         * @return Константная ссылка на список ID фильмов
         */
        const std::vector<Id>& getFilmIds() const noexcept;
    };
}
