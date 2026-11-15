#include "HallProgram.h"

miit::cinema::HallProgram::HallProgram(const Id hallId, const std::vector<Id>& filmIds)
    : hallId(hallId), filmIds(filmIds)
{
    requireId(hallId);
    for (const Id id : this->filmIds) requireId(id);
}
miit::cinema::Id miit::cinema::HallProgram::getHallId() const noexcept { return hallId; }
const std::vector<miit::cinema::Id>& miit::cinema::HallProgram::getFilmIds() const noexcept { return filmIds; }
