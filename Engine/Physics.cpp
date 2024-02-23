#include "Physics.h"
#include "Components.h"

Vector2D Physics::getOverlap(std::shared_ptr<Entity> ENTITYA, std::shared_ptr<Entity> ENTITYB)
{
    Vector2D delta(abs(ENTITYA->getComponent<CHitBox>().position.x - ENTITYB->getComponent<CTransform>().position.x),
                   abs(ENTITYA->getComponent<CHitBox>().position.y - ENTITYB->getComponent<CTransform>().position.y));

    float overlapX = (ENTITYA->getComponent<CHitBox>().halfSize.x + ENTITYB->getComponent<CHitBox>().halfSize.x) - delta.x;
    float overlapY = (ENTITYA->getComponent<CHitBox>().halfSize.y + ENTITYB->getComponent<CHitBox>().halfSize.y) - delta.y;
    return Vector2D(overlapX, overlapY);
}

Vector2D Physics::getPreviousOverlap(std::shared_ptr<Entity> ENTITYA, std::shared_ptr<Entity> ENTITYB)
{
    Vector2D delta(abs(ENTITYA->getComponent<CHitBox>().previousPosition.x - ENTITYB->getComponent<CTransform>().previousPosition.x),
                   abs(ENTITYA->getComponent<CHitBox>().previousPosition.y - ENTITYB->getComponent<CTransform>().previousPosition.y));
    float overlapX = (ENTITYA->getComponent<CHitBox>().halfSize.x + ENTITYB->getComponent<CHitBox>().halfSize.x) - delta.x;
    float overlapY = (ENTITYA->getComponent<CHitBox>().halfSize.y + ENTITYB->getComponent<CHitBox>().halfSize.y) - delta.y;
    return Vector2D(overlapX, overlapY);
}
