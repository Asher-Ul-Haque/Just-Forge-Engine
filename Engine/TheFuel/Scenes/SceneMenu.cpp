#include <fstream>
#include "../../TheMachine/Scenes/SceneMenu.h"
#include "../../TheMachine/GameEngine.h"
#include "../../TheMachine/Scenes/ScenePlay.h"
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
    mMenuTitle.setOutlineThickness(9);
    mMenuTitle.setOutlineColor(sf::Color(0, 0, 0));
    mMenuTitle.setLetterSpacing(3);
    mMenuTitle.setCharacterSize(70);
    mMenuTitle.setFillColor(sf::Color(255, 100, 100));
    mMenuTitle.setOrigin(mMenuTitle.getGlobalBounds().width/2, mMenuTitle.getGlobalBounds().height/2);
//    mMenuTitle.setPosition(sceneGameEngine->getWindow().getSize().x/2 -200, sceneGameEngine->getWindow().getSize().y/2 -600);
    mMenuTitle.setPosition(sceneGameEngine->getWindow().getSize().x/2, 330);

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
    mMenuOptions.setPosition(sceneGameEngine->getWindow().getSize().x/2, 430);

    mBackgroundTexture.loadFromFile(R"(..\\Assets\\Textures\\pixil-frame-0.png)"); //This is for a sample game, change it to your own path using file dialog
    mBackgroundTexture.setSmooth(true);
    mBackground.setTexture(mBackgroundTexture);
    mBackground.setScale(1, 1);
    mBackground.setPosition(0, 0);
    mBackground.setTextureRect(sf::IntRect(0, 276, sceneGameEngine->getWindow().getSize().x, sceneGameEngine->getWindow().getSize().y));

    registerAction(sf::Keyboard::Enter, "START_LEVEL");
    registerAction(sf::Keyboard::Escape, "QUIT");
    registerAction(sf::Keyboard::Left, "PREVIOUS_LEVEL_SELECT");
    registerAction(sf::Keyboard::Right, "NEXT_LEVEL_SELECT");


}

void SceneMenu::registerAction(int INPUTKEY, const std::string &ACTIONNAME)
{
    sceneActionMap[INPUTKEY] = ACTIONNAME;
}

void SceneMenu::sDoAction(const Action &ACTION)
{
    const std::string name = ACTION.getName();
    std::cout << "Action: " << name << std::endl;
    if (name == "START_LEVEL")
    {
        std::string controlFile = "Controls.txt";
        sceneGameEngine->changeScene("PLAY", std::make_shared<ScenePlay>(mLevelPaths[mSelectedMenuIndex], controlFile,sceneGameEngine));
    }
    if (name == "PREVIOUS_LEVEL_SELECT")
    {
        if (mSelectedMenuIndex == 0)
        {
            mSelectedMenuIndex = mTotalLevels-1;
        }
        else
        {
            mSelectedMenuIndex--;
        }
        std::cout << "Selected index: " << mSelectedMenuIndex << std::endl;
        mLevelOptions = "Level " + std::to_string(mSelectedMenuIndex + 1) + "\n";
        std::cout << mLevelOptions << std::endl;
    }
    if (name == "NEXT_LEVEL_SELECT")
    {
        mSelectedMenuIndex++;
        if (mSelectedMenuIndex >= mTotalLevels)
        {
            mSelectedMenuIndex = 0;
        }
        std::cout << "Selected index: " << mSelectedMenuIndex << std::endl;
        mLevelOptions = "Level " + std::to_string(mSelectedMenuIndex + 1) + "\n";
        std::cout << mLevelOptions << std::endl;
    }
    else if (name == "QUIT")
    {
        onEnd();
    }
    mMenuOptions.setString(mLevelOptions);

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
    sceneGameEngine->getWindow().clear(sf::Color(4, 156, 216));
    sceneGameEngine->getWindow().draw(mBackground);
    sceneGameEngine->getWindow().draw(mMenuTitle);
    sceneGameEngine->getWindow().draw(mMenuOptions);
    sceneGameEngine->getWindow().display();
}