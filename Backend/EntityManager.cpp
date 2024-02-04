#include "EntityManager.h"
#include <iostream>
#include <unistd.h>

EntityManager::EntityManager() {}

void EntityManager::update()
{
    for (const auto& e : mEntitiesToAdd)
    {
        mEntities.push_back(e);
    }
    mEntitiesToAdd.clear();
    removeDeadEntities();
}

std::shared_ptr<Entity> EntityManager::createEntity(const std::string &TAG)
{
    auto entity = std::shared_ptr<Entity>(new Entity(mTotalEntities++, TAG));
    mEntityMap[TAG].push_back(entity);
    mEntitiesToAdd.push_back(entity);
    return entity;
}

const EntityVector& EntityManager::getEntities()
{
    return mEntities;
}

const EntityVector& EntityManager::getEntities(const std::string &TAG)
{
    /*mEntitiesToReturn.clear();
    for (auto e : mEntities)
    {
        if (e->getTag() == TAG)
        {
            mEntitiesToReturn.push_back(e);
        }
    }
    return mEntitiesToReturn;*/

    return mEntityMap[TAG];
}

void EntityManager::removeDeadEntities()
{
    for (auto e : mEntitiesToDelete)
    {
        mEntityMap[e->getTag()].erase(std::remove(mEntityMap[e->getTag()].begin(), mEntityMap[e->getTag()].end(), e), mEntityMap[e->getTag()].end());
        for (auto i = mEntities.begin(); i != mEntities.end(); i++)
        {
            if (*i == e)
            {
                mEntities.erase(i);
                break;
            }
        }
    }

}

void EntityManager::killEntity(std::shared_ptr<Entity> ENTITY)
{
    mEntitiesToDelete.push_back(ENTITY);
    ENTITY->destroy();
}

void EntityManager::setScale(float SCALE, std::shared_ptr<Entity> ENTITY)
{
    ENTITY->cSprite->sprite.setScale(SCALE, SCALE);
}

void EntityManager::deathAnimation(std::shared_ptr<Entity> ENTITY)
{
    for (int i =0 ; i < 3; i++)
    {
        ENTITY->cSprite->sprite.setColor(sf::Color(255, 255, 255, 0));
        sleep(1);
        ENTITY->cSprite->sprite.setColor(sf::Color(255, 255, 255, 255));
        sleep(1);
    }
}
