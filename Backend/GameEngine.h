#ifndef SUPERMARIO_GAMEENGINE_H
#define SUPERMARIO_GAMEENGINE_H
#include "Assets.h"
#include "ScenePlay.h"
#include "SceneMenu.h"
#include "Scene.h"
#include <iostream>
#include <memory>

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

// = = = = = = = = = = = = = = = =

class GameEngine
{
protected:
    size_t gSimulationSpeed = 1;
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
    void changeScene(std::string SCENENAME, std::shared_ptr<Scene> SCENE, bool ENDCURRENTSCENE = false);
    GameEngine(const std::string& PATH);

    void quit();
    void run();

    Assets::allAssets& getAssets() const;
    sf::RenderWindow& getWindow();
    const bool isRuning() const;

    SceneMap gSceneMap;
};


#endif //SUPERMARIO_GAMEENGINE_H
