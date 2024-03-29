#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Management/Assets.h"
#include "Scenes/Scene.h"
#include "Entities/EntityManager.h"
#include <iostream>
#include <memory>

class Scene;

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

// = = = = = = = = = = = = = = = =

class GameEngine
{
protected:
    std::basic_string<char> gCurrentScene;
    std::string gCurrentSceneName;
    sf::RenderWindow gWindow;
    bool gRunning = true;
    std::string gPath;
    Assets gAssets;

    void init(const std::string& ASSETPATH);
    std::shared_ptr<Scene> currentScene();
    void sUserInput();
    void update();
// - - - - - - - - - - - - - - - - - -
public:
    size_t gSimulationSpeed = 1;
    void changeScene(std::string SCENENAME, std::shared_ptr<Scene> SCENE, std::string SCENEASSETPATH = "NONE", bool ENDCURRENTSCENE = false, bool INITNEWSCENE = true);
    GameEngine(const std::string& PATH);

    void quit();
    void run();

    Assets::allAssets& getAssets() const { return (Assets::allAssets &) gAssets.assets; }
    sf::RenderWindow& getWindow();
    const bool isRuning() const;

    SceneMap gSceneMap;
};


#endif //GAMEENGINE_H