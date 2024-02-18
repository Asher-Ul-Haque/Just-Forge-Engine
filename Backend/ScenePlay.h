#ifndef SUPERMARIO_SCENEPLAY_H
#define SUPERMARIO_SCENEPLAY_H

#include "GameEngine.h"
#include "Components.h"
#include "Action.h"
#include "Scene.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class ScenePlay : Scene
{
    struct PlayerConfigurations
    {
        float x, y, cX, cY, speed, maxSpeed, jump, gravity;
        std::string weapon;
    };
// - - - - - - - - - - - - - - - - - - - - - - - - -
protected:
    PlayerConfigurations scenePlayerConfigurations;
    const Vector2D sceneGridSize = {64, 64};
    std::shared_ptr<Entity> gPlayer;
    bool sceneDrawHitboxes = false;
    bool sceneDrawTextures = true;
    std::string sceneLevelPath;
    bool sceneDrawGrid = false;
    bool scenePaused = false;
    sf::Text sceneGridText;
// - - - - - - - - - - - - - - - - - - - - - - - - -
public:
    Vector2D gridToMidPixel(int GRIDX, int GRIDY, std::shared_ptr<Entity> ENTITY);
    void registerAction(int INPUTKEY, const std::string& ACTIONNAME);
    ScenePlay(GameEngine* GAMEENGINE, std::string LEVELPATH);
    void loadLevel(const std::string& FILEPATH);
    void init(const std::string& LEVELPATH);
    void update();
    void onEnd();

    void spawnFireBall();
    void spawnPlayer();

    void sDoAction(const Action& ACTION);
    void sCollision();
    void sAnimation();
    void sMovement();
    void sLifespan();
    void sRender();
};

#endif //SUPERMARIO_SCENEPLAY_H
