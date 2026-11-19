#include "FeatureFilm.h"

miit::cinema::FeatureFilm::FeatureFilm(const std::string& title, const int durationMinutes,
    const int minAge, const std::string& synopsis, const std::vector<std::string>& directors,
    const std::vector<std::string>& actors, const std::string& genre)
    : Film(title, durationMinutes, minAge, synopsis, directors, actors), genre(requireText(genre)) {}
const std::string& miit::cinema::FeatureFilm::getGenre() const noexcept { return genre; }
std::string miit::cinema::FeatureFilm::getKind() const { return "Художественный фильм"; }
std::string miit::cinema::FeatureFilm::toString() const
{
    return getKind() + ": «" + getTitle() + "»; жанр: " + genre + "; длительность: "
        + std::to_string(getDurationMinutes()) + " мин; возраст: " + getAgeRestrictionText();
}
