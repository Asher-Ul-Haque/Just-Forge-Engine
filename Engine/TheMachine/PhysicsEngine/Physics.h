#ifndef SUPERMARIO_PHYSICS_H
#define SUPERMARIO_PHYSICS_H
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

#endif //SUPERMARIO_PHYSICS_H
