#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager(): mTotalEntities(0) {}

// = = = = = = = = = = = = = = = = =

void EntityManager::update()
{
    for (auto& entity : mEntitiesToAdd)
    {
        mEntities.push_back(entity);
    }
    mEntitiesToAdd.clear();
    removeDeadEntities();
}

// = = = = = = = = = = = = = = = = =

std::shared_ptr<Entity> EntityManager::createEntity(const std::string& TAG)
{
    auto entity = std::shared_ptr<Entity>(new Entity(mTotalEntities++, TAG));
    mEntityMap[TAG].push_back(entity);
    mEntitiesToAdd.push_back(entity);
    return entity;
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



