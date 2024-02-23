#ifndef SUPERMARIO_ANIMATION_H
#define SUPERMARIO_ANIMATION_H
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Vector2D.h"
//---------------------------------

class Animation
{
    //Data
    sf::Texture aSpriteSheet;
    const std::string aSpriteSheetPath;
    const std::string aName;
    size_t aCurrentFrame;
    sf::Sprite aSprite;
    size_t aFrameCount;
    Vector2D aSize;
    size_t aSpeed;
    //---------------------------------

// - - - - - - - - - - - - - - - - -
public:
    //Construction
    Animation();
    Animation(const std::string& NAME, sf::Sprite& SPRITE, std::string& SPRITESHEETPATH, size_t FRAMECOUNT, size_t SPEED);
    void update();
    const Vector2D& getSize() const;
    const std::string& getName() const;
    const std::string& getSpriteSheetPath() const;
    bool hasEnded() const;
};
//---------------------------------

#endif //SUPERMARIO_ANIMATION_H
