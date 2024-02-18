#ifndef SUPERMARIO_ENTITY_H
#define SUPERMARIO_ENTITY_H
#include "Components.h"
#include <tuple>
#include <string>

class EntityManager;

// = = = = = = = = = = = = = = = = = = = = =

typedef std::tuple<CTransform, CLifespan, CInput, CHitBox, CTexture, CGravity, CState, CSprite> ComponentTuple;

// = = = = = = = = = = = = = = = = = = = = =

class Entity
{
    friend class EntityManager;
    bool eAlive = true;
    std::string eTag = "default";
    size_t eID = 0;
    ComponentTuple eComponents;

    Entity(const size_t& ID, const std::string& TAG);
// - - - - - - - - - -
public:
    template<typename T, typename... TArgs>
    T& addComponent(TArgs&&... EARGS);

    template<typename T>
    bool hasComponent() const;

    template<typename T>
    void removeComponent();

    template<typename T>
    T& getComponent();

    const std::string& getTag() const {return eTag;};
    bool isActive() const {return eAlive;}
    size_t getID() const {return eID;}
    void destroy() {eAlive = false;}
};

#endif //SUPERMARIO_ENTITY_H
