#include "Ticket.h"
#include <stdexcept>

miit::cinema::Ticket::Ticket(const Id sessionId, const Quantity seat, const Money price)
    : sessionId(sessionId), seat(seat), price(price)
{
    requireId(sessionId);
    if (seat <= 0) throw std::invalid_argument("Номер места должен быть положительным.");
    if (price <= 0) throw std::invalid_argument("Цена билета должна быть положительной.");
}
miit::cinema::Id miit::cinema::Ticket::getSessionId() const noexcept { return sessionId; }
miit::cinema::Quantity miit::cinema::Ticket::getSeat() const noexcept { return seat; }
miit::cinema::Money miit::cinema::Ticket::getPrice() const noexcept { return price; }
