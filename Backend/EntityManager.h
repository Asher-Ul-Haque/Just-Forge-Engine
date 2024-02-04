#ifndef SPACESHOOTER_ENTITYMANAGER_H
#define SPACESHOOTER_ENTITYMANAGER_H

#include <cstddef>
#include <vector>
#include <map>
#include <memory>
#include "Entity.h"

typedef size_t identification;
typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
    EntityVector mEntitiesToDelete;
    EntityMap mEntityMap;
    identification mTotalEntities = 0;
    EntityVector mEntities;
    EntityVector mEntitiesToAdd;
    EntityVector mEntitiesToReturn;

    void removeDeadEntities();

public:
    EntityManager();
    void update();
    std::shared_ptr<Entity> createEntity(const std::string& TAG);
    const EntityVector& getEntities();
    const EntityVector& getEntities(const std::string& TAG);
    void killEntity(std::shared_ptr<Entity> ENTITY);
    void setScale(float SCALE, std::shared_ptr<Entity> ENTITY);
    void deathAnimation(std::shared_ptr<Entity> ENTITY);
};



#endif
