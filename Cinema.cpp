#include "Cinema.h"
#include <algorithm>
#include <stdexcept>

namespace miit::cinema
{
    Cinema::Cinema(const std::string& name) : cinemaName(requireText(name)) {}
    const std::string& Cinema::getName() const noexcept { return cinemaName; }

    void Cinema::requireNewFilmTitle(const std::string& title) const
    {
        const std::string clean = requireText(title);
        for (const Film& film : getFilms())
            if (film.getTitle() == clean)
                throw std::invalid_argument("Фильм с таким названием уже есть.");
    }

    Quantity Cinema::countTickets(const Id sessionId) const noexcept
    {
        return std::count_if(tickets.begin(), tickets.end(),
            [sessionId](const Ticket& t) { return t.getSessionId() == sessionId; });
    }

    const Hall& Cinema::addHall(const std::string& name, const Quantity seats)
    {
        halls.emplace_back(name, seats);
        return halls.back();
    }

    const FeatureFilm& Cinema::addFeatureFilm(const std::string& title, const int durationMinutes,
        const int minAge, const std::string& synopsis, const std::vector<std::string>& directors,
        const std::vector<std::string>& actors, const std::string& genre)
    {
        requireNewFilmTitle(title);
        featureFilms.emplace_back(title, durationMinutes, minAge, synopsis, directors, actors, genre);
        return featureFilms.back();
    }

    const AnimatedFilm& Cinema::addAnimatedFilm(const std::string& title, const int durationMinutes,
        const int minAge, const std::string& synopsis, const std::vector<std::string>& directors,
        const std::vector<std::string>& actors, const std::string& technique)
    {
        requireNewFilmTitle(title);
        animatedFilms.emplace_back(title, durationMinutes, minAge, synopsis, directors, actors, technique);
        return animatedFilms.back();
    }

    const Session& Cinema::addSession(const Id hallId, const Id filmId, const Date& date,
        const TimeOfDay& start, const Money price)
    {
        getHall(hallId);
        const Film& film = getFilm(filmId);
        const Session session(hallId, filmId, date, start, film.getDurationMinutes(), price);
        for (const Session& existing : sessions)
            if (existing.overlaps(session))
                throw std::invalid_argument("Сеанс пересекается с другим сеансом этого зала.");
        sessions.push_back(session);
        return sessions.back();
    }

    const Hall& Cinema::getHall(const Id id) const
    {
        for (const Hall& hall : halls)
            if (hall.getId() == id) return hall;
        throw std::out_of_range("Зал не найден.");
    }

    const Film& Cinema::getFilm(const Id id) const
    {
        for (const Film& film : featureFilms)
            if (film.getId() == id) return film;
        for (const Film& film : animatedFilms)
            if (film.getId() == id) return film;
        throw std::out_of_range("Фильм не найден.");
    }

    const Session& Cinema::getSession(const Id id) const
    {
        for (const Session& session : sessions)
            if (session.getId() == id) return session;
        throw std::out_of_range("Сеанс не найден.");
    }

    std::vector<std::reference_wrapper<const Film>> Cinema::getFilms() const
    {
        std::vector<std::reference_wrapper<const Film>> result;
        for (const Film& film : featureFilms) result.push_back(film);
        for (const Film& film : animatedFilms) result.push_back(film);
        std::sort(result.begin(), result.end(),
            [](const Film& a, const Film& b) { return a.getId() < b.getId(); });
        return result;
    }

    std::vector<std::reference_wrapper<const Session>> Cinema::getSessionsAt(const Date& date,
        const TimeOfDay& time) const
    {
        std::vector<std::reference_wrapper<const Session>> result;
        for (const Session& session : sessions)
            if (session.isRunningAt(date, time)) result.push_back(session);
        std::sort(result.begin(), result.end(), [](const Session& a, const Session& b)
        {
            return a.getStart() == b.getStart() ? a.getHallId() < b.getHallId() : a.getStart() < b.getStart();
        });
        return result;
    }

    std::vector<HallProgram> Cinema::getFilmsByHalls(const Date& date) const
    {
        std::vector<HallProgram> result;
        for (const Hall& hall : halls)
        {
            std::vector<std::reference_wrapper<const Session>> daily;
            for (const Session& session : sessions)
                if (session.getHallId() == hall.getId() && session.getDate() == date)
                    daily.push_back(session);
            if (daily.empty()) continue;
            std::sort(daily.begin(), daily.end(),
                [](const Session& a, const Session& b) { return a.getStart() < b.getStart(); });
            std::vector<Id> filmIds;
            for (const Session& session : daily)
                if (std::find(filmIds.begin(), filmIds.end(), session.getFilmId()) == filmIds.end())
                    filmIds.push_back(session.getFilmId());
            result.emplace_back(hall.getId(), filmIds);
        }
        return result;
    }

    Money Cinema::getTicketPrice(const Id sessionId, const Id filmId) const
    {
        const Session& session = getSession(sessionId);
        getFilm(filmId);
        if (session.getFilmId() != filmId)
            throw std::invalid_argument("На этом сеансе идёт другой фильм.");
        return session.getPrice();
    }

    std::string Cinema::getFilmInfo(const Id filmId) const { return getFilm(filmId).getInfo(); }

    Quantity Cinema::getFreeSeats(const Id sessionId) const
    {
        const Session& session = getSession(sessionId);
        return getHall(session.getHallId()).getSeats() - countTickets(sessionId);
    }

    const Ticket& Cinema::sellTicket(const Id sessionId, const Id filmId, const int viewerAge)
    {
        const Session& session = getSession(sessionId);
        const Film& film = getFilm(filmId);
        if (session.getFilmId() != filmId)
            throw std::invalid_argument("На этом сеансе идёт другой фильм.");
        if (viewerAge < 0 || viewerAge > 150)
            throw std::invalid_argument("Недопустимый возраст зрителя.");
        if (viewerAge < film.getMinAge())
            throw std::invalid_argument("Возрастное ограничение фильма: " + film.getAgeRestrictionText() + ".");
        const Quantity sold = countTickets(sessionId);
        if (sold >= getHall(session.getHallId()).getSeats())
            throw std::runtime_error("Все места на сеанс проданы.");
        tickets.emplace_back(sessionId, sold + 1, session.getPrice());
        return tickets.back();
    }

    SessionSales Cinema::getSessionSales(const Id sessionId) const
    {
        getSession(sessionId);
        Quantity count = 0;
        Money revenue = 0;
        for (const Ticket& ticket : tickets)
            if (ticket.getSessionId() == sessionId)
            {
                ++count;
                revenue = checkedAdd(revenue, ticket.getPrice());
            }
        return SessionSales(sessionId, count, revenue);
    }

    std::vector<SessionSales> Cinema::getSalesBySessions() const
    {
        std::vector<SessionSales> result;
        for (const Session& session : sessions) result.push_back(getSessionSales(session.getId()));
        return result;
    }
}
