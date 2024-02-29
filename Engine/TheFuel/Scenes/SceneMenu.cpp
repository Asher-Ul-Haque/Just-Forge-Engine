#include <fstream>
#include "../../TheMachine/Scenes/SceneMenu.h"
#include "../../TheMachine/GameEngine.h"
#include "../../TheMachine/Scenes/ScenePlay.h"
#include "../../TheMachine/Management/Animation.h"
// - - - - - - - - - - -

SceneMenu::SceneMenu(GameEngine *GAMEENGINE) : Scene(GAMEENGINE)
{
}

void SceneMenu::collectAssets(std::vector<std::string> ASSETS)
{
    //Parse the asset for background
    //The format is this: Animation Background R"(..\\Assets\\Textures\\background.png)" 9 10 1000 800
    //Parse the string vector and print the values without using a for loop, we already know the format and that there are 7 values
    std::string mAnimationName = ASSETS[0];
    std::string mAnimationPath = ASSETS[1];
    int mAnimationFrames = std::stoi(ASSETS[2]);
    int mAnimationSpeed = std::stoi(ASSETS[3]);
    int mAnimationWidth = std::stoi(ASSETS[4]);
    int mAnimationHeight = std::stoi(ASSETS[5]);

    mAnimation = new Animation(mAnimationName, &mBackground, mAnimationPath, 9, 10, Vector2D(1000, 800));

}

void SceneMenu::init()
{
    currentFrame = 0;
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

//    mBackgroundTexture.loadFromFile(mAnimationPath); //This is for a sample game, change it to your own path using file dialog
//    mBackgroundTexture.setSmooth(true);
//    mBackground.setTexture(mBackgroundTexture);
    mBackground.setScale(1, 1);
    mBackground.setPosition(0, 0);
    mBackground.setTextureRect(sf::IntRect(0, 200, sceneGameEngine->getWindow().getSize().x, sceneGameEngine->getWindow().getSize().y));

    std::cout << "The sprite given is at: " << &mBackground << std::endl;
//    Animation mAnimation(mAnimationName, &mBackground, mAnimationPath, 6, 100);
//    mBackground.setTexture(mBackgroundTexture);

    registerAction(sf::Keyboard::Enter, "START_LEVEL");
    registerAction(sf::Keyboard::Escape, "QUIT");
    registerAction(sf::Keyboard::Left, "PREVIOUS_LEVEL_SELECT");
    registerAction(sf::Keyboard::Right, "NEXT_LEVEL_SELECT");
    registerAction(sf::Keyboard::Space, "NEXT_FRAME");


    mTotalLevels = mLevelPaths.size();
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
        if (mSelectedMenuIndex <= 0 || mTotalLevels == 0)
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
        std::cout << "Current frame and direction: " << currentFrame << " " << direction << std::endl;

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