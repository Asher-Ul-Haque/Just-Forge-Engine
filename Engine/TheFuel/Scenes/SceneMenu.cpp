#include <fstream>
#include "../../TheMachine/Scenes/SceneMenu.h"
#include "../../TheMachine/GameEngine.h"
#include "../../TheMachine/Scenes/ScenePlay.h"
#include "../../TheMachine/Management/Animation.h"
#include <filesystem>
// - - - - - - - - - - -

SceneMenu::SceneMenu(GameEngine *GAMEENGINE) : Scene(GAMEENGINE)
{
}

void SceneMenu::collectAnimationAssets(std::vector<std::string> ASSETS)
{
    mAnimation = new Animation(ASSETS[0], &mBackground, ASSETS[1], std::stoi(ASSETS[2]), std::stoi(ASSETS[3]), Vector2D(std::stoi(ASSETS[4]), std::stoi(ASSETS[5])));
}

void SceneMenu::collectFontAssets(std::vector<std::string> ASSETS)
{
    //Parse the asset for font
    //The format is this: Font ka1 R"(..\\Assets\\Fonts\\ka1.ttf)"
    std::string mFontName = ASSETS[0];
    std::string mFontPath = ASSETS[1];
    mFont.loadFromFile(R"(..\\Assets\\Fonts\\)" + sceneGameEngine->getAssets().fAsset["PixelFont"].fPath);
}

void SceneMenu::init()
{
    currentFrame = 0;
    mTitle = "Nah-rio"; //Add your own title, this is just a sample
    mLevelOptions = "Level 1\n";

    mMenuTitle.setString(mTitle);
    mMenuTitle.setFont(mFont);
    mMenuTitle.setOutlineThickness(9);
    mMenuTitle.setOutlineColor(sf::Color(0, 0, 0));
    mMenuTitle.setLetterSpacing(3);
    mMenuTitle.setCharacterSize(70);
    mMenuTitle.setFillColor(sf::Color(255, 100, 100));
    mMenuTitle.setOrigin(mMenuTitle.getGlobalBounds().width/2, mMenuTitle.getGlobalBounds().height/2);
    mMenuTitle.setPosition(sceneGameEngine->getWindow().getSize().x/2, 370);

    mMenuOptions.setString(mLevelOptions);
    mMenuOptions.setFont(mFont);
    mMenuOptions.setOutlineThickness(1);
    mMenuOptions.setOutlineColor(sf::Color(0, 0, 0));
    mMenuOptions.setLetterSpacing(2);
    mMenuOptions.setCharacterSize(40);
    mMenuOptions.setOutlineColor(sf::Color(255, 100, 100));
    mMenuOptions.setOutlineThickness(3);
    mMenuOptions.setFillColor(sf::Color(0, 0, 0));
    mMenuOptions.setOrigin(mMenuOptions.getGlobalBounds().width/2, mMenuOptions.getGlobalBounds().height/2 );
    mMenuOptions.setPosition(sceneGameEngine->getWindow().getSize().x/2, 470);

    mBackground.setScale(1, 1);
    mBackground.setPosition(0, 0);
    mBackground.setTextureRect(sf::IntRect(0, 200, sceneGameEngine->getWindow().getSize().x, sceneGameEngine->getWindow().getSize().y));

    registerAction(sf::Keyboard::Enter, "START_LEVEL");
    registerAction(sf::Keyboard::Escape, "QUIT");
    registerAction(sf::Keyboard::Left, "PREVIOUS_LEVEL_SELECT");
    registerAction(sf::Keyboard::Right, "NEXT_LEVEL_SELECT");
    registerAction(sf::Keyboard::Space, "NEXT_FRAME");

    mTotalLevels = 0;
    for (const auto & entry : std::filesystem::directory_iterator("..//Assets//ConfigurationFiles//Levels//"))
    {
        mLevelPaths.push_back(entry.path().string());
        mTotalLevels++;
    }

    for (auto e : mLevelPaths)
    {
        std::cout << e << std::endl;
    }

}

void SceneMenu::registerAction(int INPUTKEY, const std::string &ACTIONNAME)
{
    sceneActionMap[INPUTKEY] = ACTIONNAME;
}

void SceneMenu::sDoAction(const Action &ACTION)
{
    const std::string name = ACTION.getName();
    std::cout << " _ _ _ _ _ SCENE MENU MESSAGE _ _ _ _ _" << std::endl;
    std::cout << "Action: " << name << std::endl;
    std::cout << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _" << std::endl << std::endl;
    if (name == "START_LEVEL")
    {
        std::string controlFile = R"(..//Assets//ConfigurationFiles//Controls.txt)";
        sceneGameEngine->changeScene("PLAY", std::make_shared<ScenePlay>(mLevelPaths[mSelectedMenuIndex], controlFile,sceneGameEngine), "LEVEL1", false, true);
        std::cout << " _ _ _ _ _ SCENE MENU MESSAGE _ _ _ _ _" << std::endl;
        std::cout << "Playing game" << std::endl;
        std::cout << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _" << std::endl << std::endl;
    }
    if (name == "PREVIOUS_LEVEL_SELECT")
    {
        if (mSelectedMenuIndex <= 0 || mTotalLevels == 0)
        {
            mSelectedMenuIndex = mTotalLevels-1;
        }
        else
        {
            mSelectedMenuIndex--;
        }
        std::cout << " _ _ _ _ _ SCENE MENU MESSAGE _ _ _ _ _" << std::endl;
        std::cout << "Selected index: " << mSelectedMenuIndex << std::endl;
        mLevelOptions = "Level " + std::to_string(mSelectedMenuIndex + 1) + "\n";
        std::cout << mLevelOptions << std::endl;
        std::cout << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _" << std::endl << std::endl;
    }
    if (name == "NEXT_LEVEL_SELECT")
    {
        mSelectedMenuIndex++;
        if (mSelectedMenuIndex >= mTotalLevels)
        {
            mSelectedMenuIndex = 0;
        }
        std::cout << " _ _ _ _ _ SCENE MENU MESSAGE _ _ _ _ _" << std::endl;
        std::cout << "Selected index: " << mSelectedMenuIndex << std::endl;
        mLevelOptions = "Level " + std::to_string(mSelectedMenuIndex + 1) + "\n";
        std::cout << mLevelOptions << std::endl;
        std::cout << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _" << std::endl << std::endl;
    }
    if (name == "NEXT_FRAME")
    {
        if (currentFrame == 0)
        {
            direction = 1;
        }
        else if (currentFrame == 5)
        {
            direction = -1;
        }
        currentFrame += direction;
        std::cout << " _ _ _ _ _ SCENE MENU MESSAGE _ _ _ _ _" << std::endl;
        std::cout << "Current frame and direction: " << currentFrame << " " << direction << std::endl;
        std::cout << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _" << std::endl << std::endl;
        mBackground.setTextureRect(sf::IntRect(1000*currentFrame, 200, sceneGameEngine->getWindow().getSize().x, sceneGameEngine->getWindow().getSize().y));
    }
    else if (name == "QUIT")
    {
        onEnd();
    }
    mMenuOptions.setString(mLevelOptions);

}

void SceneMenu::update()
{
    mAnimation->update();
    sRender();
}

void SceneMenu::onEnd()
{
    sceneHasEnded = true;
    //delete the animation object
    delete mAnimation;
}

void SceneMenu::sRender()
{
    sceneGameEngine->getWindow().clear(sf::Color(4, 156, 216));
    sceneGameEngine->getWindow().draw(mBackground);
    sceneGameEngine->getWindow().draw(mMenuTitle);
    sceneGameEngine->getWindow().draw(mMenuOptions);
    sceneGameEngine->getWindow().display();
}