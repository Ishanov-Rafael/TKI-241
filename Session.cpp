#include "Session.h"
#include <stdexcept>

miit::cinema::Session::Session(const Id hallId, const Id filmId, const Date& date,
    const TimeOfDay& start, const int durationMinutes, const Money price)
    : hallId(hallId), filmId(filmId), date(date), start(start),
      end(start.addMinutes(durationMinutes)), price(price)
{
    requireId(hallId);
    requireId(filmId);
    if (durationMinutes <= 0) throw std::invalid_argument("Длительность сеанса должна быть положительной.");
    if (price <= 0) throw std::invalid_argument("Цена билета должна быть положительной.");
}
miit::cinema::Id miit::cinema::Session::getHallId() const noexcept { return hallId; }
miit::cinema::Id miit::cinema::Session::getFilmId() const noexcept { return filmId; }
const miit::cinema::Date& miit::cinema::Session::getDate() const noexcept { return date; }
const miit::cinema::TimeOfDay& miit::cinema::Session::getStart() const noexcept { return start; }
const miit::cinema::TimeOfDay& miit::cinema::Session::getEnd() const noexcept { return end; }
miit::cinema::Money miit::cinema::Session::getPrice() const noexcept { return price; }
bool miit::cinema::Session::isRunningAt(const Date& moment, const TimeOfDay& time) const noexcept
{
    return date == moment && start <= time && time < end;
}
bool miit::cinema::Session::overlaps(const Session& other) const noexcept
{
    return hallId == other.hallId && date == other.date && start < other.end && other.start < end;
}
