#ifndef PHYSICS_H
#define PHYSICS_H
#include <memory>
#include "Vector2D.h"
#include "../Entities/Entity.h"
//---------------------------------

class Physics
{
public:
    //Static methods to get the overlap between two entities
    static Vector2D getOverlap(std::shared_ptr<Entity> ENTITYA, std::shared_ptr<Entity> ENTITYB);
    static Vector2D getPreviousOverlap(std::shared_ptr<Entity> ENTITYA, std::shared_ptr<Entity> ENTITYB);
};
//---------------------------------

#endif //PHYSICS_H
