#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Animation::Animation(){}

// - - - - - - - -

Animation::Animation(const std::string &NAME, sf::Sprite& SPRITE, std::string& SPRITESHEETPATH, size_t FRAMECOUNT, size_t SPEED):
aName(NAME), aSprite(SPRITE), aFrameCount(FRAMECOUNT), aSpeed(SPEED), aCurrentFrame(0), aSpriteSheetPath(SPRITESHEETPATH)
{
    aSpriteSheet.loadFromFile(SPRITESHEETPATH);
    aSpriteSheet.setSmooth(false);
    aSize = Vector2D((float)aSpriteSheet.getSize().x/(float)aFrameCount/(float)aSpeed, (float)aSpriteSheet.getSize().y);
    aSprite.setOrigin((float)aSize.x/2.0f, (float)aSize.y/2.0f);
    aSprite.setTextureRect(sf::IntRect(std::floor(aCurrentFrame) * aSize.x, 0, aSize.x, aSize.y));
}

// - - - - - - - -

void Animation::update()
{
    aCurrentFrame++;
    aSprite.setTextureRect(sf::IntRect(std::floor(aCurrentFrame / aSpeed) * aSize.x, 0, aSize.x, aSize.y));
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
