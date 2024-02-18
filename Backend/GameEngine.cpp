#include "GameEngine.h"
#include "Assets.h"
#include "ScenePlay.h"
#include "SceneMenu.h"

// - - - - - - - - - - -

GameEngine::GameEngine(const std::string &PATH)
{
    init(PATH);
}

// - - - - - - - - - - -

void GameEngine::init(const std::string& PATH)
{
    gAssets.setPath(PATH);
    gAssets.loadFromFile(PATH);
    gWindow.create(sf::VideoMode(1280, 760), "Definately Not Mario");
    gWindow.setFramerateLimit(60);
    changeScene("MENU", std::make_shared<SceneMenu>(this));
}

// - - - - - - - - - - -

void GameEngine::sUserInput()
{
    sf::Event eventManager;
    while (gWindow.pollEvent(eventManager))
    {
        switch (eventManager.type)
        {
            case sf::Event::Closed:
                quit();
            case sf::Event::KeyPressed || sf::Event::KeyReleased:
                switch (eventManager.key.code)
                {
                    case sf::Keyboard::X:
                        sf::Texture screenshot;
                        screenshot.update(gWindow);
                        if (screenshot.copyToImage().saveToFile("Test.png"))
                        {
                            std::cout << "Screenshot saved to test.png" << std::endl;
                            break;
                        }
                        break;
                }

                if(currentScene()->getActionMap().find(eventManager.key.code) == currentScene()->getActionMap().end())
                {
                    continue;
                }
                // determine whether it is a start or end of the action
                const std::string actionType = (eventManager.type == sf::Event::KeyPressed) ? "START" : "END";
                currentScene()->sDoAction(Action(currentScene()->getActionMap().at(eventManager.key.code), actionType));
        }
    }
}

// - - - - - - - - - - -

sf::RenderWindow &GameEngine::getWindow()
{
    return gWindow;
}

// - - - - - - - - - - -

void GameEngine::run()
{
    while (isRuning())
    {
        update();
    }
}

// - - - - - - - - - - -

void GameEngine::update()
{
    sUserInput();
    gWindow.clear();
    gSceneMap[gCurrentSceneName]->update();
    gWindow.display();
};

// - - - - - - - - - - -

void GameEngine::quit()
{
    gRunning = false;
    gWindow.close();
}

// - - - - - - - - - - -

const bool GameEngine::isRuning() const
{
    return gRunning;
}

// - - - - - - - - - - -

Assets::allAssets& GameEngine::getAssets() const
{
    return (Assets::allAssets &) gAssets.assets;
}

// - - - - - - - - - - -

std::shared_ptr<Scene> GameEngine::currentScene()
{
    return gSceneMap[gCurrentSceneName];
}

// - - - - - - - - - - - -
void GameEngine::changeScene(std::string SCENENAME, std::shared_ptr<Scene> SCENE, bool ENDCURRENTSCENE)
{
    if (ENDCURRENTSCENE)
    {
        gSceneMap[gCurrentScene]->onEnd();
    }
    gSceneMap[SCENENAME] = SCENE;
    gCurrentScene = SCENENAME;
    gSceneMap[SCENENAME]->init();
}

