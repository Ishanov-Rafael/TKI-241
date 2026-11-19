#include "Film.h"
#include <stdexcept>

namespace
{
    /**
     * @brief Очищает список имён от пробелов и проверяет, что он не пуст
     * @param names Исходный список
     * @return Очищенный непустой список
     * @throw std::invalid_argument Если список пуст или содержит пустое имя
     */
    std::vector<std::string> requireNames(const std::vector<std::string>& names)
    {
        if (names.empty()) throw std::invalid_argument("Список имён не может быть пустым.");
        std::vector<std::string> result;
        for (const auto& name : names) result.push_back(miit::cinema::requireText(name));
        return result;
    }

    /**
     * @brief Склеивает имена через запятую
     * @param names Список имён
     * @return Строка вида "Иванов, Петров"
     */
    std::string join(const std::vector<std::string>& names)
    {
        std::string result;
        for (std::size_t i = 0; i < names.size(); ++i)
            result += (i == 0 ? "" : ", ") + names[i];
        return result;
    }
}

miit::cinema::Film::Film(const std::string& title, const int durationMinutes, const int minAge,
    const std::string& synopsis, const std::vector<std::string>& directors,
    const std::vector<std::string>& actors)
    : title(requireText(title)), durationMinutes(durationMinutes), minAge(minAge),
      synopsis(requireText(synopsis)), directors(requireNames(directors)),
      actors(requireNames(actors))
{
    if (durationMinutes <= 0 || durationMinutes >= 24 * 60)
        throw std::invalid_argument("Длительность фильма должна быть от 1 до 1439 минут.");
    if (minAge < 0 || minAge > 21)
        throw std::invalid_argument("Возрастное ограничение должно быть от 0 до 21.");
}

const std::string& miit::cinema::Film::getTitle() const noexcept { return title; }
int miit::cinema::Film::getDurationMinutes() const noexcept { return durationMinutes; }
int miit::cinema::Film::getMinAge() const noexcept { return minAge; }
bool miit::cinema::Film::hasAgeRestriction() const noexcept { return minAge > 0; }
std::string miit::cinema::Film::getAgeRestrictionText() const
{
    return minAge > 0 ? std::to_string(minAge) + "+" : "без ограничений";
}
const std::string& miit::cinema::Film::getSynopsis() const noexcept { return synopsis; }
const std::vector<std::string>& miit::cinema::Film::getDirectors() const noexcept { return directors; }
const std::vector<std::string>& miit::cinema::Film::getActors() const noexcept { return actors; }

std::string miit::cinema::Film::getInfo() const
{
    return getKind() + " «" + title + "» (" + getAgeRestrictionText() + ")\n"
        + "Краткое содержание: " + synopsis + "\n"
        + "Режиссёры: " + join(directors) + "\n"
        + "Актёры: " + join(actors);
}
