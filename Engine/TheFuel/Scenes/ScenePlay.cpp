#include "../../TheMachine/Scenes/ScenePlay.h"
#include "../../TheMachine/PhysicsEngine/Physics.h"
#include "../../TheMachine/Management/Assets.h"
#include "../../TheMachine/GameEngine.h"
#include "../../TheMachine/Entities/Components.h"
#include "../../TheMachine/Management/Action.h"
#include "../../TheMachine/Management/Animation.h"
#include "../../TheMachine/Entities/EntityManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
// - - - - - - - - - -

ScenePlay::ScenePlay(std::string& SCENELEVELPATH, std::string& CONTROLSPECIFICATIONFILE, GameEngine *GAMEENGINE): sceneLevelPath(SCENELEVELPATH), sceneControls(CONTROLSPECIFICATIONFILE)
{
}

// - - - - - - - - - - -

void ScenePlay::registerAction(int INPUTKEY, const std::string &ACTIONNAME)
{
}

// - - - - - - - - - - -

void ScenePlay::setPath(const std::string &LEVELPATH)
{
}

// - - - - - - - - - - -

void ScenePlay::setControls(std::string& CONTROLSPECIFICATIONFILE)
{
}

// - - - - - - - - - - -

void ScenePlay::init()
{
}

// - - - - - - - - - - -

Vector2D ScenePlay::gridToMidPixel(int GRIDX, int GRIDY)
{
}

// - - - - - - - - - - -

void ScenePlay::loadLevel(const std::string &FILEPATH)
{
}

// - - - - - - - - - - -

void ScenePlay::spawnPlayer()
{
}

// - - - - - - - - - - -

void ScenePlay::update()
{
}

// - - - - - - - - - - -

void ScenePlay::sMovement()
{
}

// - - - - - - - - - - -

void ScenePlay::sLifespan()
{
}

// - - - - - - - - - - -

void ScenePlay::sCollision()
{
}

// - - - - - - - - - - -

void ScenePlay::sDoAction(const Action &ACTION)
{
}

// - - - - - - - - - - -

void ScenePlay::sAnimation()
{
}

// - - - - - - - - - - -

void ScenePlay::onEnd()
{
}

// - - - - - - - - - - -

void ScenePlay::spawnFireBall()
{
}

// - - - - - - - - - - -

void ScenePlay::drawLine(const Vector2D &V1, const Vector2D &V2)
{
}

// - - - - - - - - - - -

void ScenePlay::sRender()
{
}



