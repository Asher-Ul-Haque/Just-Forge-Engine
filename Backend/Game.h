#ifndef SPACESHOOTER_GAME_H
#define SPACESHOOTER_GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include <chrono>
#include "Entity.h"
#include "EntityManager.h"

class Game
{
    sf::RenderWindow gRoot;
    EntityManager gEntityManager;
    sf::Font gFont;
    sf::Text gLifeData, gScoreData;
    sf::Texture gExplosionTexture;
    int gScore = 0;
    int gCurrentFrame = 0;
    int gLastEnemySpawnTime = 0;
    bool gPaused = false;
    bool gRunning = true;
    float gEnemySpawnMinWait = 30.f;
    std::shared_ptr<Entity> gPlayer;

    void init();
    void setPaused(bool PAUSED);

    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender();
    void sEnemySpawner();
    void sCollision();
    void sDataDisplay();

    void spawnPlayer();
    void spawnEnemy();
    void spawnBullet(const Vector2D& POSITION);
    void spawnSpecialWeapon(std::shared_ptr<Entity> SPECIAL_WEAPON);

public:
    Game();
    void run();
};

#endif //SPACESHOOTER_GAME_H
