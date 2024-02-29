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
    //Add a default icon
//    sf::Image icon;
//    icon.loadFromFile(R"(C:\Users\conta\CLionProjects\JustForge_V2\Assets\Textures\Logo - Copy.png)"); // File/Image/Pixel
//    gWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    gAssets.setPath(PATH);
    gAssets.loadFromFile(PATH);
    gWindow.create(sf::VideoMode(1000, 800), "Definately Not Mario");
    gWindow.setFramerateLimit(60);
    changeScene("MENU", std::make_shared<SceneMenu>(this), false, false);
    //Collect the first line from gAssets and make a vector of strings
    std::cout << "Collecting assets" << std::endl;
    std::vector<std::string> assets;
//    assets.push_back("Background");
//    std::string path = R"(..\\Assets\\Textures\\)";
//    path = path + "background.png";
//    assets.push_back(path);
//    assets.push_back("9");
//    assets.push_back("10");
//    assets.push_back("1000");
//    assets.push_back("800");

    std::cout << gAssets.assets.aAsset["Background"].aName << std::endl;
    assets.push_back(gAssets.assets.aAsset["Background"].aName);
    std::string path = R"(..\\Assets\\Textures\\)" + gAssets.assets.aAsset["Background"].aSpriteSheetPath;
    assets.push_back(path);
    assets.push_back(std::to_string(gAssets.assets.aAsset["Background"].aFrameCount));
    assets.push_back(std::to_string(gAssets.assets.aAsset["Background"].aSpeed));
    assets.push_back(std::to_string(gAssets.assets.aAsset["Background"].aFrameSize.x));
    assets.push_back(std::to_string(gAssets.assets.aAsset["Background"].aFrameSize.y));

    gSceneMap[gCurrentScene]->collectAssets(assets);
    std::cout << "Scene assets collected" << std::endl;
    gSceneMap[gCurrentScene]->init();
    std::cout << "Scene initialized" << std::endl;
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
void GameEngine::changeScene(std::string SCENENAME, std::shared_ptr<Scene> SCENE, bool ENDCURRENTSCENE, bool INITNEWSCENE)
{
    if (ENDCURRENTSCENE)
    {
        gSceneMap[gCurrentScene]->onEnd();
    }
    gSceneMap[SCENENAME] = SCENE;
    gCurrentScene = SCENENAME;
    if (INITNEWSCENE)
    {
        gSceneMap[SCENENAME]->init();
    }
}

//Make the screen stay open for a few seconds


