#include "AnimatedFilm.h"

miit::cinema::AnimatedFilm::AnimatedFilm(const std::string& title, const int durationMinutes,
    const int minAge, const std::string& synopsis, const std::vector<std::string>& directors,
    const std::vector<std::string>& actors, const std::string& technique)
    : Film(title, durationMinutes, minAge, synopsis, directors, actors),
      technique(requireText(technique)) {}
const std::string& miit::cinema::AnimatedFilm::getTechnique() const noexcept { return technique; }
std::string miit::cinema::AnimatedFilm::getKind() const { return "Мультфильм"; }
std::string miit::cinema::AnimatedFilm::toString() const
{
    return getKind() + ": «" + getTitle() + "»; техника: " + technique + "; длительность: "
        + std::to_string(getDurationMinutes()) + " мин; возраст: " + getAgeRestrictionText();
}
