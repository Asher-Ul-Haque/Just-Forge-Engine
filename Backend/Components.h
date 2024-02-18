#ifndef SUPERMARIO_COMPONENTS_H
#define SUPERMARIO_COMPONENTS_H
#include "Vector2D.h"
#include "Assets.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class Component
{
public:
    bool has = false;
};

// = = = = = = = = = = = = = = = = =

class CTransform : public Component
{
public:
    Vector2D previousPosition = {0.f, 0.f};
    Vector2D position = {0.f, 0.f};
    Vector2D velocity = {0.f, 0.f};
    Vector2D scale = {1.0f, 1.0f};
    float angle = 0;

    CTransform(const Vector2D& POSITION, const Vector2D& VELOCITY, float ANGLE): position(POSITION), velocity(VELOCITY), angle(ANGLE){}
};

// = = = = = = = = = = = = = = = = =

class CSprite : public Component
{
public:
    Vector2D size = {64.0f, 64.0f};
    sf::Sprite sprite;
    CSprite(Vector2D &SIZE): size(SIZE){};
};

// = = = = = = = = = = = = = = = = =

class CColliison : public Component
{
    sf::Sprite otherSprite;

public:
    CColliison(sf::Sprite OTHERSPRITE): otherSprite(OTHERSPRITE){}
};

// = = = = = = = = = = = = = = = = =

class CScore : public Component
{
public:
    unsigned int score = 0;
    CScore(int SCORE): score(SCORE){}
};

// = = = = = = = = = = = = = = = = =

class CLifespan : public Component
{
public:
    int remaining = 0;
    int total = 0;
    CLifespan(int TOTAL): remaining(TOTAL), total(TOTAL){}
};

// = = = = = = = = = = = = = = = = =

class CInput : public Component
{
public:
    std::string configFile;
    bool right = false;
    bool shoot = false;
    bool left = false;
    bool down = false;
    bool up = false;

    CInput(const std::string& CONFIGFILE):configFile(CONFIGFILE){}
};

// = = = = = = = = = = = = = = = = =

class CState : public Component
{
public:
    std::string state;
    CState(const std::string& STATE): state(STATE){}
};

// = = = = = = = = = = = = = = = = =

class CHitBox : public Component
{
    sf::FloatRect hitBox;
public:
    Vector2D position;
    Vector2D size;
    Vector2D halfSize;
    Vector2D previousPosition;
    CHitBox(const Vector2D& POSITION, const Vector2D& SIZE): position(POSITION), size(SIZE), halfSize(SIZE/2), previousPosition(Vector2D(0, 0)){}
};

// = = = = = = = = = = = = = = = = =

class CGravity : public Component
{
public:
    float gravity = 0;
    CGravity(float GRAVITY): gravity(GRAVITY){}
};

// = = = = = = = = = = = = = = = = =

class CTexture : public Component
{
    const Assets::AnimationAsset textureAsset;
public:
    sf::Texture texture;
    std::string name = textureAsset.aName;
    std::string spriteSheetPath = textureAsset.aSpriteSheetPath;
    size_t frameCount = textureAsset.aFrameCount;
    size_t speed = textureAsset.aSpeed;

    CTexture(std::shared_ptr<Assets::AnimationAsset> TEXTUREASSET) : textureAsset(*TEXTUREASSET){};
    const std::string getName() const {return name;};
    const std::string getSpriteSheetPath() const {return spriteSheetPath;}
    const size_t getFrameCount() const { return frameCount; }
    const size_t getSpeed() const { return speed; }
};
#endif //SUPERMARIO_COMPONENTS_H
