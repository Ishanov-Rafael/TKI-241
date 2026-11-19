#include "TimeOfDay.h"
#include <stdexcept>

namespace miit::cinema
{
    TimeOfDay::TimeOfDay(const int hour, const int minute) : hour(hour), minute(minute)
    {
        if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
            throw std::invalid_argument("Неверное время суток.");
    }

    TimeOfDay::TimeOfDay(const std::string& text) : TimeOfDay(0, 0)
    {
        if (text.size() != 5 || text[2] != ':')
            throw std::invalid_argument("Ожидается время HH:MM.");
        for (std::size_t i = 0; i < text.size(); ++i)
            if (i != 2 && (text[i] < '0' || text[i] > '9'))
                throw std::invalid_argument("Во времени допустимы только цифры и двоеточие.");
        *this = TimeOfDay(std::stoi(text.substr(0, 2)), std::stoi(text.substr(3, 2)));
    }

    int TimeOfDay::toMinutes() const noexcept { return hour * 60 + minute; }

    TimeOfDay TimeOfDay::addMinutes(const int minutes) const
    {
        const int total = toMinutes() + minutes;
        if (total < 0 || total >= 24 * 60)
            throw std::invalid_argument("Время выходит за границы суток.");
        return TimeOfDay(total / 60, total % 60);
    }

    std::string TimeOfDay::toString() const
    {
        return (hour < 10 ? "0" : "") + std::to_string(hour) + ":"
            + (minute < 10 ? "0" : "") + std::to_string(minute);
    }

    bool TimeOfDay::operator<(const TimeOfDay& other) const noexcept
    { return toMinutes() < other.toMinutes(); }
    bool TimeOfDay::operator<=(const TimeOfDay& other) const noexcept
    { return toMinutes() <= other.toMinutes(); }
    bool TimeOfDay::operator==(const TimeOfDay& other) const noexcept
    { return toMinutes() == other.toMinutes(); }
}
