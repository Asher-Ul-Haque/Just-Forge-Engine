#ifndef SUPERMARIO_SCENEMENU_H
#define SUPERMARIO_SCENEMENU_H
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
    size_t mTotalLevels = 3;
    std::string mTitle, mLevelOptions;
    sf::Text mMenuTitle, mMenuOptions;
    sf::Font mFont;
    sf::Texture mBackgroundTexture;
    sf::Sprite mBackground;
    unsigned int currentFrame;
    short direction;
    std::string mAnimationName = "Background";
    std::string mAnimationPath = R"(..\\Assets\\Textures\\background.png)";
    Animation* mAnimation;

    void registerAction(int INPUTKEY, const std::string& ACTIONNAME) override;
    void sDoAction(const Action& ACTION) override;
    void update() override;
    void onEnd() override;
    void init() override;
// - - - - - - - - - - - - - - - - - - - - - -
public:
    SceneMenu(GameEngine* GAMEENGINE = nullptr);
    void sRender() override;
};
//---------------------------------

#endif //SUPERMARIO_SCENEMENU_H
