#include "../../TheMachine/Management/Animation.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Animation::Animation(){}

// - - - - - - - -

Animation::Animation(std::string &NAME, sf::Sprite* SPRITE, std::string& SPRITESHEETPATH, size_t FRAMECOUNT, size_t SPEED, Vector2D SIZE, bool LOOP):
aName(NAME), aSprite(SPRITE), aFrameCount(FRAMECOUNT), aSpeed(SPEED), aCurrentFrame(0), aSpriteSheetPath(SPRITESHEETPATH), aloop(LOOP)
{
    aSpriteSheet.loadFromFile(SPRITESHEETPATH);
    aSpriteSheet.setSmooth(true);
    std::cout << "The sprite sheet recieved is at: " << &aSpriteSheet << std::endl;

    aSize = Vector2D((float)aSpriteSheet.getSize().x/aFrameCount, (float)SIZE.y);
//    aSprite->setOrigin((float)aSize.x/2.0f, (float)aSize.y/2.0f);
    std::cout << "Set the texture of " << aName << " to " << aSpriteSheetPath << std::endl;
    aSprite->setTexture(aSpriteSheet);
    aSprite->setTextureRect(sf::IntRect(0, 0, SIZE.x, SIZE.y));
}

// - - - - - - - -

void Animation::update()
{
    switch (aloop)
    {
//        //When a loop is true, the animation will loop like 1->2->3->2->1
//        case true:
//            aCurrentFrame += 1;
//            if (aCurrentFrame >= aFrameCount * aSpeed)
//            {
//                aCurrentFrame = 0;
//            }
//            break;


        case true:
            aCurrentFrame += 1;
            if (aCurrentFrame >= aFrameCount * aSpeed)
            {
                aCurrentFrame = 0;
            }
            break;
        case false:
            if (aCurrentFrame < aFrameCount * aSpeed)
            {
                aCurrentFrame += 1;
            }
            break;
    }

    if (aSpeed!= 0)
    {
        aSprite->setTextureRect(sf::IntRect(std::floor(aCurrentFrame / aSpeed) * aSize.x, 0, aSize.x, aSize.y));
    }
}

// - - - - - - - -

const Vector2D& Animation::getSize() const
{
    return aSize;
}

// - - - - - - - -

const std::string& Animation::getName() const
{
    return aName;
}

// - - - - - - - -

const std::string& Animation::getSpriteSheetPath() const
{
    return aSpriteSheetPath;
}

bool Animation::hasEnded() const
{
    return (aCurrentFrame >= aFrameCount);
}
// - - - - - - - -
