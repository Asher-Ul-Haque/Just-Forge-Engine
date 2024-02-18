#ifndef SUPERMARIO_SCENE_H
#define SUPERMARIO_SCENE_H
#include "Action.h"
#include "EntityManager.h"
#include "GameEngine.h"
#include <memory>

class GameEngine;

// = = = = = = = = = = = = = = = = = = = =

typedef std::map<int, std::string> ActionMap;

// = = = = = = = = = = = = = = = = = = = =

class Scene
{
    friend class GameEngine;

protected:
    GameEngine * sceneGameEngine = nullptr;
    EntityManager sceneEntityManager;
    size_t sceneCurrentFrame = 0;
    bool sceneHasEnded = false;
    bool scenePaused = false;
    ActionMap sceneActionMap;
    virtual void onEnd() = 0;
    virtual void init() = 0;

    void setPaused(bool PAUSED);
    // - - - - - - - - - - - - - - - - - - - -
public:
    Scene();
    Scene(GameEngine * SCENEGAMEENGINE): sceneGameEngine(SCENEGAMEENGINE){};
    Scene(GameEngine * SCENEGAMEENGINE, const std::string& LEVELPATH): sceneGameEngine(SCENEGAMEENGINE){};

    void sDoAction(const Action& ACTION);
    void sRender();
    void update();

    void registerAction(int INPUTKEY, const std::string& ACTIONNAME);
    void simulate(const size_t FRAMES);

    size_t currentFrame() const;
    size_t getHeight() const;
    size_t getWidth() const;

    void drawLine(const Vector2D& POINT1, const Vector2D& POINT2);
    const ActionMap& getActionMap() const;
    bool hasEnded() const;

};

#endif //SUPERMARIO_SCENE_H
