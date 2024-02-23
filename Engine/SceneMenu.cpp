#include <fstream>
#include "SceneMenu.h"
#include "GameEngine.h"
#include "ScenePlay.h"
// - - - - - - - - - - -

SceneMenu::SceneMenu(GameEngine *GAMEENGINE) : Scene(GAMEENGINE)
{
    init();
}

void SceneMenu::init()
{
    mTitle = "Nah-rio"; //Add your own title, this is just a sample
    mFont.loadFromFile(R"(..\\Assets\\Fonts\\ka1.ttf)"); //This is for a sample game, change it to your own path using file dialog
    mLevelOptions = "Level 1\n";

    mMenuTitle.setString(mTitle);
    mMenuTitle.setFont(mFont);
    mMenuTitle.setOutlineThickness(5);
    mMenuTitle.setOutlineColor(sf::Color(0, 0, 0));
    mMenuTitle.setLetterSpacing(3);
    mMenuTitle.setCharacterSize(30);
    mMenuTitle.setFillColor(sf::Color(255, 0, 0));
//    mMenuTitle.setPosition(sceneGameEngine->getWindow().getSize().x/2 -200, sceneGameEngine->getWindow().getSize().y/2 -600);
    mMenuTitle.setPosition(500, 200);


    registerAction(sf::Keyboard::Enter, "START_LEVEL");
    registerAction(sf::Keyboard::Escape, "QUIT");
    registerAction(sf::Keyboard::Up, "PREVIOUS_LEVEL_SELECT");
    registerAction(sf::Keyboard::Down, "NEXT_LEVEL_SELECT");

    mMenuOptions.setString(mLevelOptions);
    mMenuOptions.setOutlineThickness(1);
    mMenuOptions.setOutlineColor(sf::Color(0, 0, 0));
    mMenuOptions.setLetterSpacing(2);
    mMenuOptions.setCharacterSize(20);
    mMenuOptions.setFillColor(sf::Color(255, 255, 255));

    rect = sf::RectangleShape(sf::Vector2f(100, 100));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(100, 100);
}

void SceneMenu::registerAction(int INPUTKEY, const std::string &ACTIONNAME)
{
    sceneActionMap[INPUTKEY] = ACTIONNAME;
}

void SceneMenu::sDoAction(const Action &ACTION)
{
    const std::string name = ACTION.getName();
    if (name == "START_LEVEL")
    {
        std::string controlFile = "Controls.txt";
        sceneGameEngine->changeScene("PLAY", std::make_shared<ScenePlay>(mLevelPaths[mSelectedMenuIndex], controlFile,sceneGameEngine));
    }
    if (name == "PREVIOUS_LEVEL_SELECT")
    {
        mSelectedMenuIndex--;
        if (mSelectedMenuIndex < 0)
        {
            mSelectedMenuIndex = mTotalLevels-1;
        }
        mLevelOptions = "Level " + std::to_string(mSelectedMenuIndex + 1) + "\n";
    }
    if (name == "NEXT_LEVEL_SELECT")
    {
        mSelectedMenuIndex++;
        if (mSelectedMenuIndex >= mTotalLevels)
        {
            mSelectedMenuIndex = 0;
        }
        mLevelOptions = "Level " + std::to_string(mSelectedMenuIndex + 1) + "\n";
    }
    else if (name == "QUIT")
    {
        onEnd();
    }

}

void SceneMenu::update()
{
    sRender();
}

void SceneMenu::onEnd()
{
    sceneHasEnded = true;
}

void SceneMenu::sRender()
{
    sceneGameEngine->getWindow().clear(sf::Color(0, 0, 0));
    sceneGameEngine->getWindow().draw(mMenuTitle);
    sceneGameEngine->getWindow().draw(mMenuOptions);
    sceneGameEngine->getWindow().draw(rect);
    sceneGameEngine->getWindow().display();
}