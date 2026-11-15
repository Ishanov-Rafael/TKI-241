#include "Entity.h"
#include <limits>
#include <stdexcept>

miit::cinema::Id miit::cinema::Entity::nextId = 1;

miit::cinema::Id miit::cinema::Entity::createId()
{
    if (nextId == (std::numeric_limits<Id>::max)())
        throw std::overflow_error("Закончились свободные идентификаторы.");
    return nextId++;
}

miit::cinema::Entity::Entity() : id(createId()) {}
miit::cinema::Id miit::cinema::Entity::getId() const noexcept { return id; }
