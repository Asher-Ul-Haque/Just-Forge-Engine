#ifndef ENTITY_H
#define ENTITY_H
#include "Components.h"
#include "../../TheMachine/Management/Animation.h"
#include <tuple>
#include <string>
//---------------------------------

class EntityManager;
typedef std::tuple<CTransform, CLifespan, CInput, CHitBox, CTexture, CGravity, CState, CSprite> ComponentTuple;

//---------------------------------

class EntityManager;

class Entity
{
    //Data
    bool eAlive = true;
    std::string eTag = "default";
    size_t eID = 0;
    ComponentTuple eComponents;
    bool eComponentPresence[8] = {false, false, false, false, false, false, false, false};
    //---------------------------------


    friend class EntityManager;
    //---------------------------------

    //METHODS
public:
    Animation* eAnimation;
    //Construction
    Entity(const size_t& ID, const std::string& TAG):eID(ID), eTag(TAG)
    {
        for (size_t i = 0; i < 8; i++)
        {
            eComponentPresence[i] = false;
        }
    }

    template<typename T, typename... TArgs>
    T& addComponent(TArgs&&... EARGS)
    {
        std::get<T>(eComponents) = T(std::forward<TArgs>(EARGS)...);
        return std::get<T>(eComponents);
    };

    template<typename T>
    bool hasComponent() const
    {
        for (size_t i = 0; i < 8; i++)
        {
            if (eComponentPresence[i])
            {
                return true;
            }
        }
        return false;
    };

    template<typename T>
    void removeComponent()
    {
        std::get<T>(eComponents).reset();
        std::get<T>(eComponentPresence) = false;
    };

    template<typename T>
    T& getComponent()
    {
        return std::get<T>(eComponents);
    };

    const std::string& getTag() const {return eTag;};
    bool isActive() const {return eAlive;}
    size_t getID() const {return eID;}
    void destroy() {eAlive = false;}
};
//---------------------------------

#endif //ENTITY_H
