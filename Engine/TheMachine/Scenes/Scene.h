#ifndef SUPERMARIO_SCENE_H
#define SUPERMARIO_SCENE_H
#include "../Management/Action.h"
#include "../Entities/EntityManager.h"
#include <memory>
#include <map>
#include <string>
//---------------------------------

class GameEngine;
typedef std::map<int, std::string> ActionMap;

//---------------------------------

class Scene
{
    friend class GameEngine;

protected:
    GameEngine* sceneGameEngine = nullptr;
    EntityManager sceneEntityManager;
    size_t sceneCurrentFrame = 0;
    size_t simulationSpeed = 0;
    bool sceneHasEnded = false;
    bool scenePaused = false;
    ActionMap sceneActionMap;

    void setPaused(bool PAUSED);
    // - - - - - - - - - - - - - - - - - - - -
public:
    Scene(){};
    Scene(GameEngine * SCENEGAMEENGINE): sceneGameEngine(SCENEGAMEENGINE){};
    Scene(GameEngine * SCENEGAMEENGINE, const std::string& LEVELPATH): sceneGameEngine(SCENEGAMEENGINE){};

    virtual void onEnd() = 0;

    virtual void init() = 0;

    virtual void sDoAction(const Action& ACTION) = 0;

    virtual void sRender() = 0;

    virtual void update() = 0;

    virtual void registerAction(int INPUTKEY, const std::string& ACTIONNAME) = 0;

    virtual void drawLine(const Vector2D& POINT1, const Vector2D& POINT2){};

    size_t currentFrame() const { return sceneCurrentFrame; };

    const ActionMap& getActionMap() const { return sceneActionMap; };
    bool hasEnded() const {return scenePaused; };
};
//---------------------------------

#endif //SUPERMARIO_SCENE_H
