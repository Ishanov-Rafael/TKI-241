#include "Hall.h"
#include <stdexcept>

miit::cinema::Hall::Hall(const std::string& name, const Quantity seats)
    : name(requireText(name)), seats(seats)
{
    if (seats <= 0) throw std::invalid_argument("Число мест должно быть положительным.");
}
const std::string& miit::cinema::Hall::getName() const noexcept { return name; }
miit::cinema::Quantity miit::cinema::Hall::getSeats() const noexcept { return seats; }
