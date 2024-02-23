#ifndef SUPERMARIO_COMPONENTS_H
#define SUPERMARIO_COMPONENTS_H
#include "Vector2D.h"
#include "Assets.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
//---------------------------------

// Basic class for all components
class Component
{
public:
    bool has = false;
};

//---------------------------------

//Transform class for position, velocity and angle
class CTransform : public Component
{
public:
    //Data
    Vector2D previousPosition = {0.f, 0.f};
    Vector2D position = {0.f, 0.f};
    Vector2D velocity = {0.f, 0.f};
    Vector2D scale = {1.0f, 1.0f};
    float angle = 0;
    //---------------------------------

    //Construction
    CTransform(const Vector2D& POSITION, const Vector2D& VELOCITY, float ANGLE): position(POSITION), velocity(VELOCITY), angle(ANGLE){}
    CTransform(){}
    //---------------------------------
};

//---------------------------------

//Sprite class for rendering
class CSprite : public Component
{
public:
    //Data
    Vector2D size = {64.0f, 64.0f};
    sf::Sprite sprite;
    //---------------------------------

    //Construction
    CSprite(Vector2D &SIZE): size(SIZE){};
    CSprite(){}; //Default constructor
    //---------------------------------
};

//---------------------------------

//Collision class for collision detection
class CColliison : public Component
{
    //Data
    sf::Sprite otherSprite;
    //---------------------------------

public:
    //Construction
    CColliison(sf::Sprite OTHERSPRITE): otherSprite(OTHERSPRITE){}
    CColliison(){}; //Default constructor
    //---------------------------------
};

//---------------------------------

//Score class for keeping track of score
class CScore : public Component
{
public:
    //Data
    unsigned int score = 0;
    //---------------------------------

    //Construction
    CScore(int SCORE): score(SCORE){}
    CScore(){} //Default constructor
    //---------------------------------
};

//---------------------------------

class CLifespan : public Component
{
public:
    //Data
    int remaining = 0;
    int total = 0;
    //---------------------------------

    //Construction
    CLifespan(int TOTAL): remaining(TOTAL), total(TOTAL){}
    CLifespan(){} //Default constructor
    //---------------------------------
};

//---------------------------------

class CInput : public Component
{
public:
    //Data
//    std::string configFile;
    bool right = false;
    bool shoot = false;
    bool left = false;
    bool down = false;
    bool up = false;
    //---------------------------------

    //Construction
//    CInput(const std::string& CONFIGFILE):configFile(CONFIGFILE){}
    CInput(){}
    //---------------------------------
};

//---------------------------------

class CState : public Component
{
public:
    //Data
    std::string state;
    //---------------------------------

    //Construction
    CState(const std::string& STATE): state(STATE){}
    CState(){} //Default constructor
    //---------------------------------
};

//---------------------------------

class CHitBox : public Component
{
    //Data
    sf::FloatRect hitBox;
public:
    Vector2D position;
    Vector2D size;
    Vector2D halfSize;
    Vector2D previousPosition;
    //---------------------------------

    //Construction
    CHitBox(const Vector2D& POSITION, const Vector2D& SIZE): position(POSITION), size(SIZE), halfSize(SIZE/2), previousPosition(Vector2D(0, 0)){}
    CHitBox(){} //Default constructor
    //---------------------------------
};

//---------------------------------

class CGravity : public Component
{
public:
    //Data
    float gravity = 0;
    //---------------------------------

    //Construction
    CGravity(float GRAVITY): gravity(GRAVITY){}
    CGravity(){} //Default constructor
    //---------------------------------
};

//---------------------------------

class CTexture : public Component
{
    //Data
    Assets::AnimationAsset textureAsset;
public:
    sf::Texture texture;
    std::string name = textureAsset.aName;
    std::string spriteSheetPath = textureAsset.aSpriteSheetPath;
    size_t frameCount = textureAsset.aFrameCount;
    size_t speed = textureAsset.aSpeed;
    //---------------------------------

    //Construction
    CTexture(std::shared_ptr<Assets::AnimationAsset> TEXTUREASSET) : textureAsset(*TEXTUREASSET){};
    CTexture(){} //Default constructor
    //---------------------------------

    //Methods
    const std::string getName() const {return name;};
    const std::string getSpriteSheetPath() const {return spriteSheetPath;}
    const size_t getFrameCount() const { return frameCount; }
    const size_t getSpeed() const { return speed; }
    //---------------------------------
};
//---------------------------------

#endif //SUPERMARIO_COMPONENTS_H
