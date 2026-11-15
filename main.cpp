#include <iostream>
#include <exception>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#endif
#include "Cinema.h"

using namespace miit::cinema;

/**
 * @brief Выводит сеанс: время, зал, фильм и сообщение о возрастном ограничении
 * @param cinema Кинотеатр, из которого берутся зал и фильм
 * @param session Выводимый сеанс
 */
static void printSession(const Cinema& cinema, const Session& session)
{
    const Film& film = cinema.getFilm(session.getFilmId());
    std::cout << session.getStart().toString() << "–" << session.getEnd().toString() << ", "
        << cinema.getHall(session.getHallId()).getName() << ": «" << film.getTitle() << "»";
    if (film.hasAgeRestriction())
        std::cout << " — ВНИМАНИЕ, возрастное ограничение " << film.getAgeRestrictionText();
    std::cout << '\n';
}

/**
 * @brief Демонстрирует полиморфную коллекцию фильмов и все отчёты кинотеатра
 * @return 0 при успешной работе
 */
int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    try
    {
        Cinema cinema("Кинотеатр «Октябрь»");
        const Hall& hall1 = cinema.addHall("Большой зал", 50);
        const Hall& hall2 = cinema.addHall("Малый зал", 30);

        const FeatureFilm& lighthouse = cinema.addFeatureFilm("Тайна старого маяка", 110, 12,
            "Подростки находят на заброшенном маяке дневник смотрителя и распутывают старую тайну.",
            { "Анна Соколова" }, { "Иван Орлов", "Мария Лебедева" }, "приключения");
        const FeatureFilm& express = cinema.addFeatureFilm("Ночной экспресс", 125, 18,
            "Во время ночного рейса поезда пассажиры понимают, что среди них скрывается преступник.",
            { "Пётр Дроздов", "Олег Рябов" }, { "Сергей Ветров", "Елена Март" }, "триллер");
        const AnimatedFilm& fox = cinema.addAnimatedFilm("Приключения Лисёнка", 85, 0,
            "Маленький лисёнок отправляется через зимний лес к друзьям, чтобы вернуть потерянный подарок.",
            { "Нина Белова" }, { "Дарья Светлова", "Антон Громов" }, "компьютерная");

        const Date today(2026, 11, 6);
        const Session& s1 = cinema.addSession(hall1.getId(), lighthouse.getId(), today, TimeOfDay(10, 0), 35000);
        const Session& s2 = cinema.addSession(hall1.getId(), lighthouse.getId(), today, TimeOfDay(14, 0), 40000);
        const Session& s3 = cinema.addSession(hall1.getId(), express.getId(), today, TimeOfDay(18, 0), 50000);
        const Session& s4 = cinema.addSession(hall2.getId(), fox.getId(), today, TimeOfDay(10, 30), 25000);
        cinema.addSession(hall2.getId(), fox.getId(), today, TimeOfDay(12, 30), 25000);
        cinema.addSession(hall2.getId(), lighthouse.getId(), today, TimeOfDay(15, 0), 40000);

        std::cout << cinema.getName() << ", сегодня " << today.toString() << "\n\n";

        std::cout << "Коллекция фильмов (объекты базового типа Film):\n";
        const std::vector<std::reference_wrapper<const Film>> films = cinema.getFilms();
        for (const Film& film : films)
            std::cout << "ID " << film.getId() << ": " << film.toString() << '\n';

        std::cout << "\n1. Сеансы, идущие в 10:45\n";
        for (const Session& session : cinema.getSessionsAt(today, TimeOfDay("10:45")))
            printSession(cinema, session);
        std::cout << "Сеансы, идущие в 18:30\n";
        for (const Session& session : cinema.getSessionsAt(today, TimeOfDay("18:30")))
            printSession(cinema, session);

        std::cout << "\n2. Фильмы по залам на сегодня\n";
        for (const HallProgram& program : cinema.getFilmsByHalls(today))
        {
            std::cout << cinema.getHall(program.getHallId()).getName() << ":\n";
            for (const Id filmId : program.getFilmIds())
                std::cout << "  «" << cinema.getFilm(filmId).getTitle() << "»\n";
        }

        std::cout << "\n3. Цена билета\n";
        std::cout << "«" << lighthouse.getTitle() << "», сеанс " << s1.getStart().toString() << ": "
            << formatMoney(cinema.getTicketPrice(s1.getId(), lighthouse.getId())) << '\n';
        std::cout << "«" << lighthouse.getTitle() << "», сеанс " << s2.getStart().toString() << ": "
            << formatMoney(cinema.getTicketPrice(s2.getId(), lighthouse.getId())) << '\n';

        std::cout << "\n4. Информация о фильме\n" << cinema.getFilmInfo(express.getId()) << '\n';

        std::cout << "\n5. Продажа билетов\n";
        cinema.sellTicket(s1.getId(), lighthouse.getId(), 30);
        cinema.sellTicket(s1.getId(), lighthouse.getId(), 14);
        const Ticket& ticket = cinema.sellTicket(s3.getId(), express.getId(), 25);
        std::cout << "Продан билет на «" << express.getTitle() << "», место " << ticket.getSeat()
            << ", цена " << formatMoney(ticket.getPrice()) << '\n';
        cinema.sellTicket(s4.getId(), fox.getId(), 7);
        try
        {
            cinema.sellTicket(s3.getId(), express.getId(), 16);
        }
        catch (const std::invalid_argument& error)
        {
            std::cout << "Отказ в продаже: " << error.what() << '\n';
        }
        std::cout << "Свободных мест на сеанс " << s1.getStart().toString() << ": "
            << cinema.getFreeSeats(s1.getId()) << '\n';

        std::cout << "\n6. Продажи по сеансам\n";
        for (const SessionSales& sales : cinema.getSalesBySessions())
        {
            const Session& session = cinema.getSession(sales.getSessionId());
            std::cout << session.getStart().toString() << ", "
                << cinema.getHall(session.getHallId()).getName() << ", «"
                << cinema.getFilm(session.getFilmId()).getTitle() << "»: билетов "
                << sales.getTicketsSold() << ", выручка " << formatMoney(sales.getRevenue()) << '\n';
        }
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}
