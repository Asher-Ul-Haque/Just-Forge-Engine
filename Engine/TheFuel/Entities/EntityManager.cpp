#include "../../TheMachine/Entities/Entity.h"
#include "../../TheMachine/Entities/EntityManager.h"


EntityManager::EntityManager(): mTotalEntities(0) {}

// = = = = = = = = = = = = = = = = =

void EntityManager::update()
{
    for (auto& entity : mEntitiesToAdd)
    {
        mEntities.push_back(entity);
    }
    for (auto& entity : mEntities)
    {
        entity->eAnimation->update();
    }
    mEntitiesToAdd.clear();
    removeDeadEntities();
}

// = = = = = = = = = = = = = = = = =

std::shared_ptr<Entity> EntityManager::createEntity(const std::string& TAG)
{
    std::shared_ptr<Entity> a = std::make_shared<Entity>(mTotalEntities++, TAG);
    mEntityMap[TAG].push_back(a);
    mEntitiesToAdd.push_back(a);
    return a;
}

// = = = = = = = = = = = = = = = = =

const EntityVector& EntityManager::getEntities()
{
    return mEntities;
}

// = = = = = = = = = = = = = = = = =

const EntityVector& EntityManager::getEntities(const std::string &TAG)
{
    return mEntityMap[TAG];
}

// = = = = = = = = = = = = = = = = =

void EntityManager::removeDeadEntities()
{
    for (auto& entity : mEntitiesToDelete)
    {
        mEntities.erase(std::remove(mEntities.begin(), mEntities.end(), entity), mEntities.end());
        mEntityMap[entity->getTag()].erase(std::remove(mEntityMap[entity->getTag()].begin(), mEntityMap[entity->getTag()].end(), entity), mEntityMap[entity->getTag()].end());
    }
    mEntitiesToDelete.clear();
}

// = = = = = = = = = = = = = = = = =

void EntityManager::killEntity(std::shared_ptr<Entity> ENTITY)
{
    mEntitiesToDelete.push_back(ENTITY);
    ENTITY->destroy();
}

// = = = = = = = = = = = = = = = = =

void EntityManager::setTag(std::shared_ptr<Entity> ENTITY, const std::string& TAG)
{
    ENTITY->eTag = TAG;
}

void EntityManager::setAnimation(std::shared_ptr<Entity> ENTITY, const std::vector <std::string> ANIMATION)
{
    //The animation asset name is the first element in the vector
//    Animation::Animation(std::string &NAME, sf::Sprite* SPRITE, std::string& SPRITESHEETPATH, size_t FRAMECOUNT, size_t SPEED, Vector2D SIZE, bool LOOP):
}




