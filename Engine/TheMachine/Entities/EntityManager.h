#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <memory>
#include <vector>
#include "Entity.h"
//---------------------------------

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

//---------------------------------

class EntityManager
{
    //Data
    EntityVector mEntities;
    EntityVector mEntitiesToAdd;
    EntityVector mEntitiesToDelete;
    EntityMap mEntityMap;
    size_t mTotalEntities;
    //---------------------------------

    //Methods
    void removeDeadEntities();
//- - - - - - - - - - - -
public:
    EntityManager();
    void update();
    std::shared_ptr<Entity> createEntity(const std::string& TAG);
    const EntityVector& getEntities();
    const EntityVector& getEntities(const std::string &TAG);
    void killEntity(std::shared_ptr<Entity> ENTITY);
    void setTag(std::shared_ptr<Entity> ENTITY, const std::string &TAG);
    //MAKE A SET ANIMATION FUNCTION THAT TAKES ONLY AN ANIMATION ASSET NAME AND AN ENTITY
    void setAnimation(std::shared_ptr<Entity> ENTITY, const std::vector <std::string> ANIMATION);
};
//---------------------------------

#endif //ENTITYMANAGER_H
