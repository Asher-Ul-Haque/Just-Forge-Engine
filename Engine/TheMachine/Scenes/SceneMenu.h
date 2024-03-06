#ifndef SCENEMENU_H
#define SCENEMENU_H
#include "Scene.h"
#include "../GameEngine.h"
#include "../Management/Action.h"
#include "ScenePlay.h"
#include <map>
#include <memory>
#include "../Entities/EntityManager.h"
//---------------------------------

class SceneMenu : public Scene
{
protected:
    std::vector<std::string> mLevelPaths;
    size_t mSelectedMenuIndex = 0;
    size_t mTotalLevels;
    std::string mTitle, mLevelOptions;
    sf::Text mMenuTitle, mMenuOptions;
    sf::Font mFont;
    sf::Texture mBackgroundTexture;
    sf::Sprite mBackground;
    unsigned int currentFrame;
    short direction;

    void collectAnimationAssets(std::vector<std::string> ASSETS) override;
    void collectFontAssets(std::vector<std::string> ASSETS) override;
    void registerAction(int INPUTKEY, const std::string& ACTIONNAME) override;
    void sDoAction(const Action& ACTION) override;
    void update() override;
    void onEnd() override;
    std::string mAnimationName;
    std::string mAnimationPath;
    Animation* mAnimation;
// - - - - - - - - - - - - - - - - - - - - - -
public:
    SceneMenu(GameEngine* GAMEENGINE = nullptr);
    void sRender() override;
    void init() override;
    ~SceneMenu();

};
//---------------------------------

#endif //SCENEMENU_H