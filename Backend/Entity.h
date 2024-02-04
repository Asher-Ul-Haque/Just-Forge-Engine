#ifndef SPACESHOOTER_ENTITY_H
#include "Components.h"
#include <memory>
#include <string>

class Entity
{
    friend class EntityManager;

    bool mAlive = true;
    size_t mID = 0;
    std::string mTag = "default";

    //construct
    Entity(const size_t ID, const std::string& TAG): mID(ID), mTag(TAG){};

public:
    //Component pointers
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CSprite> cSprite;
    std::shared_ptr<CColliison> cCollision;
    std::shared_ptr<CInput> cInput;
    std::shared_ptr<CScore> cScore;
    std::shared_ptr<CLifespan> cLifespan;

    //private member access
    bool isAlive(){return mAlive;};
    size_t getID(){return mID;};
    std::string getTag(){return mTag;};

    //Desctruct
    void destroy(){mAlive = false;};

};
#define SPACESHOOTER_ENTITY_H

#endif
