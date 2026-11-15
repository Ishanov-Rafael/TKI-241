#include "SessionSales.h"
#include <stdexcept>

miit::cinema::SessionSales::SessionSales(const Id sessionId, const Quantity ticketsSold,
    const Money revenue) : sessionId(sessionId), ticketsSold(ticketsSold), revenue(revenue)
{
    requireId(sessionId);
    if (ticketsSold < 0 || revenue < 0)
        throw std::invalid_argument("Количество билетов и выручка не могут быть отрицательными.");
}
miit::cinema::Id miit::cinema::SessionSales::getSessionId() const noexcept { return sessionId; }
miit::cinema::Quantity miit::cinema::SessionSales::getTicketsSold() const noexcept { return ticketsSold; }
miit::cinema::Money miit::cinema::SessionSales::getRevenue() const noexcept { return revenue; }
