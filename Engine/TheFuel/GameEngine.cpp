#include "../TheMachine/GameEngine.h"
#include "../TheMachine/Management/Assets.h"
#include "../TheMachine/Scenes/SceneMenu.h"
#include "../TheMachine/Scenes/Scene.h"
#include <ctime>

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
    gWindow.create(sf::VideoMode(1024, 760), "Definately Not Mario");
    gWindow.setFramerateLimit(60);
    changeScene("MENU", std::make_shared<SceneMenu>(this), false);
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
                std::cout << "Quit called" << std::endl;
                quit();
                break;
            case sf::Event::KeyReleased:
                std::cout << "Key pressed" << eventManager.key.code << std::endl;
                if (eventManager.key.code == sf::Keyboard::Escape)
                {
                    std::cout << "Quit called" << std::endl;
                    quit();
                }
                switch (eventManager.key.code)
                {
                    case sf::Keyboard::X:
                        std::cout << "Screenshot called" << std::endl;
                        sf::Texture screenshot;
                        screenshot.create(gWindow.getSize().x, gWindow.getSize().y);
                        screenshot.update(gWindow);
                        time_t now = time(0);
                        std::string dateTime = ctime(&now);
                        dateTime.erase(std::remove(dateTime.begin(), dateTime.end(), ' '), dateTime.end());
                        dateTime.erase(std::remove(dateTime.begin(), dateTime.end(), '\n'), dateTime.end());
                        std::replace(dateTime.begin(), dateTime.end(), ':', '_');
                        std::string path = R"(..\\Screenshots\\)" + dateTime +".png";
                        if (screenshot.copyToImage().saveToFile(path));
                        {
                            std::cout << "Screenshot saved to " << path << std::endl;
                            break;
                        }
                }
                if(gSceneMap[gCurrentScene]->getActionMap().find(eventManager.key.code) == gSceneMap[gCurrentScene]->getActionMap().end())
                {
                    continue;
                }
                // determine whether it is a start or end of the action
                const std::string actionType = (eventManager.type == sf::Event::KeyPressed) ? "START" : "END";
                std::cout << "Action type: " << actionType << std::endl;
                gSceneMap[gCurrentScene]->sDoAction(Action(gSceneMap[gCurrentScene]->getActionMap().at(eventManager.key.code), actionType));
                std::cout << "Action done" << std::endl;
                break;
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
    gSceneMap[gCurrentScene]->update();
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

//Make the screen stay open for a few seconds


