#ifndef SUPERMARIO_SCENEPLAY_H
#define SUPERMARIO_SCENEPLAY_H
#include "Scene.h"
#include <memory>
#include <map>
#include <string>
#include "SFML/Graphics.hpp"
//---------------------------------

class ScenePlay : public Scene
{
    typedef struct playerConfig
    {
        float x, y, cX, cY, speed, maxSpeed, jump, gravity;
        std::string WEAPON;
    } PlayerConfig;
protected:
    std::shared_ptr<Entity> gPlayer;
    std::string sceneLevelPath;
    std::string sceneControls;
    PlayerConfig scenePlayerConfigurations;
    bool sceneDrawGrid = false;
    bool sceneDrawTextures = true;
    bool sceneDrawHitboxes = true;
    bool scenePaused = false;
    const Vector2D sceneGridSize = {64, 64};
    sf::Text sceneGridText;

    //- - - - - - - - -

public:
    //Construction
    ScenePlay(std::string& SCENELEVELPATH, std::string& CONTROLSPECIFICATIONFILE, GameEngine* GAMEENGINE = nullptr);
    void setPath(const std::string& LEVELPATH);
    void loadLevel(const std::string& LEVELPATH);
    void registerAction(int INPUTKEY, const std::string& ACTIONNAME) override;
    void init() override;
    void setControls(std::string& CONTROLSPECIFICATIONFILE);

    void sRender() override;
    void update() override;
    void spawnPlayer();
    void spawnFireBall();
    void onEnd() override;
    void sDoAction(const Action& ACTION) override;
    void setPaused(bool PAUSED) {scenePaused = PAUSED;};
    void drawLine(const Vector2D& POINT1, const Vector2D& POINT2) override;
    void sCollision();
    void sAnimation();
    void sLifespan();
    void sMovement();
    Vector2D gridToMidPixel(int GRIDX, int GRIDY);
};
//---------------------------------

#endif //SUPERMARIO_SCENEPLAY_H
