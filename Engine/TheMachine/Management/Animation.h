#ifndef ANIMATION_H
#define ANIMATION_H
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include "../PhysicsEngine/Vector2D.h"
//---------------------------------

class Animation
{
    //Data
    sf::Texture aSpriteSheet;
    std::string aSpriteSheetPath;
    std::string aName;
    size_t aCurrentFrame;
    sf::Sprite* aSprite;
    size_t aFrameCount;
    Vector2D aSize;
    size_t aSpeed;
    bool aloop;
    //---------------------------------

// - - - - - - - - - - - - - - - - -
public:
    //Construction
    Animation();
    Animation(std::string& NAME, sf::Sprite* SPRITE, std::string& SPRITESHEETPATH, size_t FRAMECOUNT, size_t SPEED, Vector2D SIZE, bool LOOP = true);
    void update();
    const Vector2D& getSize() const;
    const std::string& getName() const;
    const std::string& getSpriteSheetPath() const;
    bool hasEnded() const;
};
//---------------------------------

#endif //ANIMATION_H
