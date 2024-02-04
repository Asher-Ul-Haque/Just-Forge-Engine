#ifndef SPACESHOOTER_COMPONENTS_H
#define SPACESHOOTER_COMPONENTS_H
#include "Vector2D.h"
#include <SFML/Graphics.hpp>

class CTransform
{
public:
    Vector2D position = {0.f, 0.f};
    Vector2D velocity = {0.f, 0.f};
    float angle = 0;

    CTransform(const Vector2D& POSITION, const Vector2D& VELOCITY, float ANGLE): position(POSITION), velocity(VELOCITY), angle(ANGLE){}
};

class CSprite
{
public:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string textureAddress;
    Vector2D size = {100.f, 100.f};

    CSprite(const std::string &FILE, Vector2D &SIZE);
    CSprite(const std::string &FILE);
};

class CColliison
{
    sf::Sprite otherSprite;
public:
    CColliison(sf::Sprite OTHERSPRITE): otherSprite(OTHERSPRITE){}
};

class CScore{
    unsigned int score = 0;
    CScore(int SCORE): score(SCORE){}
};

class CLifespan
{
public:
    int remaining = 0;
    int total = 0;
    CLifespan(int TOTAL): remaining(TOTAL), total(TOTAL){}
};

class CInput
{
public:
    std::string configFile;
    bool up = false;
    bool left = false;
    bool right = false;
    bool down = false;
    bool shoot = false;

    CInput(const std::string& CONFIGFILE):configFile(CONFIGFILE){}
};
#endif //SPACESHOOTER_COMPONENTS_H