#pragma once
#include "FeatureFilm.h"
#include "AnimatedFilm.h"
#include "Hall.h"
#include "Session.h"
#include "Ticket.h"
#include "SessionSales.h"
#include "HallProgram.h"
#include <deque>
#include <functional>
#include <string>
#include <vector>

namespace miit::cinema
{
    /**
     * @brief Кинотеатр: хранит залы, фильмы, сеансы и проданные билеты и строит отчёты
     */
    class Cinema
    {
    private:
        /** 
         * @brief Название кинотеатра 
         */
        std::string cinemaName;
        /** 
         * @brief Принадлежащие кинотеатру художественные фильмы 
         */
        std::deque<FeatureFilm> featureFilms;
        /** 
         * @brief Принадлежащие кинотеатру мультфильмы 
         */
        std::deque<AnimatedFilm> animatedFilms;
        /** 
         * @brief Залы кинотеатра
         */
        std::deque<Hall> halls;
        /** 
         * @brief Сеансы всех залов 
         */
        std::deque<Session> sessions;
        /** 
         * @brief Проданные билеты 
         */
        std::deque<Ticket> tickets;
        /**
         * @brief Проверяет уникальность названия среди всех фильмов
         * @param title Название нового фильма
         * @throw std::invalid_argument Если название пусто или уже занято
         */
        void requireNewFilmTitle(const std::string& title) const;
        /**
         * @brief Считает проданные билеты сеанса
         * @param sessionId ID сеанса
         * @return Количество проданных билетов
         */
        Quantity countTickets(const Id sessionId) const noexcept;
    public:
        /**
         * @brief Создаёт пустой кинотеатр
         * @param name Непустое название
         * @throw std::invalid_argument Если название пусто после удаления пробелов
         */
        explicit Cinema(const std::string& name);
        /**
         * @brief Освобождает все принадлежащие кинотеатру записи
         */
        ~Cinema() = default;
        /**
         * @brief Стандартный конструктор копирования
         * @param other Исходный кинотеатр
         */
        Cinema(const Cinema& other) = default;
        /**
         * @brief Стандартное присваивание копированием
         * @param other Кинотеатр, данные которого заменяют текущие
         * @return Ссылка на текущий объект
         */
        Cinema& operator=(const Cinema& other) = default;
        /**
         * @brief Стандартный конструктор перемещения
         * @param other Кинотеатр, из которого переносятся данные
         */
        Cinema(Cinema&& other) noexcept = default;
        /**
         * @brief Стандартное присваивание перемещением
         * @param other Кинотеатр, из которого переносятся данные
         * @return Ссылка на текущий объект
         */
        Cinema& operator=(Cinema&& other) noexcept = default;
        /**
         * @brief Возвращает название кинотеатра
         * @return Константная ссылка на название
         */
        const std::string& getName() const noexcept;
        /**
         * @brief Добавляет зал
         * @param name Непустое название зала
         * @param seats Положительное число мест
         * @return Ссылка на добавленный зал
         * @throw std::invalid_argument Если название пусто или число мест неположительно
         */
        const Hall& addHall(const std::string& name, const Quantity seats);
        /**
         * @brief Добавляет художественный фильм
         * @param title Название
         * @param durationMinutes Длительность в минутах
         * @param minAge Минимальный возраст зрителя от 0 до 21
         * @param synopsis Краткое содержание
         * @param directors Список режиссёров
         * @param actors Список актёров
         * @param genre Жанр
         * @return Ссылка на добавленный фильм
         * @throw std::invalid_argument Если данные недопустимы или название уже занято
         */
        const FeatureFilm& addFeatureFilm(const std::string& title, const int durationMinutes,
            const int minAge, const std::string& synopsis,
            const std::vector<std::string>& directors,
            const std::vector<std::string>& actors, const std::string& genre);
        /**
         * @brief Добавляет мультфильм
         * @param title Название
         * @param durationMinutes Длительность в минутах
         * @param minAge Минимальный возраст зрителя от 0 до 21
         * @param synopsis Краткое содержание
         * @param directors Список режиссёров
         * @param actors Список актёров озвучивания
         * @param technique Техника анимации
         * @return Ссылка на добавленный фильм
         * @throw std::invalid_argument Если данные недопустимы или название уже занято
         */
        const AnimatedFilm& addAnimatedFilm(const std::string& title, const int durationMinutes,
            const int minAge, const std::string& synopsis,
            const std::vector<std::string>& directors,
            const std::vector<std::string>& actors, const std::string& technique);
        /**
         * @brief Добавляет сеанс
         * @param hallId ID существующего зала
         * @param filmId ID существующего фильма
         * @param date Дата сеанса
         * @param start Время начала сеанса
         * @param price Положительная цена билета в копейках
         * @return Ссылка на добавленный сеанс
         * @throw std::out_of_range Если зал или фильм не найден
         * @throw std::invalid_argument Если цена недопустима, сеанс заканчивается после полуночи или пересекается с другим сеансом того же зала
         */
        const Session& addSession(const Id hallId, const Id filmId, const Date& date,
            const TimeOfDay& start, const Money price);
        /**
         * @brief Находит зал по ID
         * @param id ID зала
         * @return Ссылка на зал
         * @throw std::out_of_range Если зал не найден
         */
        const Hall& getHall(const Id id) const;
        /**
         * @brief Находит фильм любого вида по ID
         * @param id ID фильма
         * @return Ссылка на фильм как на объект базового класса
         * @throw std::out_of_range Если фильм не найден
         */
        const Film& getFilm(const Id id) const;
        /**
         * @brief Находит сеанс по ID
         * @param id ID сеанса
         * @return Ссылка на сеанс
         * @throw std::out_of_range Если сеанс не найден
         */
        const Session& getSession(const Id id) const;
        /**
         * @brief Возвращает все фильмы как коллекцию базового типа
         * @return Ссылки на фильмы всех видов в порядке возрастания ID
         */
        std::vector<std::reference_wrapper<const Film>>& getFilms() const;
        /**
         * @brief Показывает сеансы, идущие в указанный момент
         * @param date Дата момента
         * @param time Время момента
         * @return Сеансы, которые уже начались и ещё не закончились, по времени начала и залу
         */
        std::vector<std::reference_wrapper<const Session>>& getSessionsAt(const Date& date, const TimeOfDay& time) const;
        /**
         * @brief Показывает фильмы по залам, идущие в указанный день
         * @param date Дата
         * @return Программы залов, в которых есть сеансы в этот день, в порядке добавления залов
         */
        std::vector<HallProgram> getFilmsByHalls(const Date& date) const;
        /**
         * @brief Возвращает цену билета на сеанс данного фильма
         * @param sessionId ID сеанса
         * @param filmId ID фильма
         * @return Цена в копейках
         * @throw std::out_of_range Если сеанс или фильм не найден
         * @throw std::invalid_argument Если на сеансе идёт другой фильм
         */
        Money getTicketPrice(const Id sessionId, const Id filmId) const;
        /**
         * @brief Возвращает справку о фильме: содержание, режиссёры и актёры
         * @param filmId ID фильма
         * @return Многострочный текст справки
         * @throw std::out_of_range Если фильм не найден
         */
        std::string getFilmInfo(const Id filmId) const;
        /**
         * @brief Возвращает число свободных мест на сеансе
         * @param sessionId ID сеанса
         * @return Число мест зала минус число проданных билетов
         * @throw std::out_of_range Если сеанс не найден
         */
        Quantity getFreeSeats(const Id sessionId) const;
        /**
         * @brief Продаёт билет на выбранный сеанс данного фильма
         * @param sessionId ID сеанса
         * @param filmId ID фильма
         * @param viewerAge Возраст зрителя в годах от 0 до 150
         * @return Ссылка на проданный билет
         * @throw std::out_of_range Если сеанс или фильм не найден
         * @throw std::invalid_argument Если на сеансе идёт другой фильм, возраст недопустим или меньше возрастного ограничения фильма
         * @throw std::runtime_error Если все места на сеанс проданы
         */
        const Ticket& sellTicket(const Id sessionId, const Id filmId, const int viewerAge);
        /**
         * @brief Возвращает итог продаж по одному сеансу
         * @param sessionId ID сеанса
         * @return Количество проданных билетов и выручка
         * @throw std::out_of_range Если сеанс не найден
         * @throw std::overflow_error Если выручка не помещается в Money
         */
        SessionSales getSessionSales(const Id sessionId) const;
        /**
         * @brief Возвращает продажи по всем сеансам
         * @return Итоги по каждому сеансу в порядке добавления сеансов
         * @throw std::overflow_error Если выручка не помещается в Money
         */
        std::vector<SessionSales> getSalesBySessions() const;
    };
}
