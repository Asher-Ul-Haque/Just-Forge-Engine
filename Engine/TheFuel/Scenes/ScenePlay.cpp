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
    std::cout << "Beginning Level" << std::endl;
    sceneGameEngine = GAMEENGINE;
    setControls(CONTROLSPECIFICATIONFILE);
    std::cout << "Controls set" << std::endl;
    setPath(SCENELEVELPATH);
//    init();
}

// - - - - - - - - - - -

void ScenePlay::registerAction(int INPUTKEY, const std::string &ACTIONNAME)
{
    sceneActionMap[INPUTKEY] = ACTIONNAME;
}

// - - - - - - - - - - -

void ScenePlay::setPath(const std::string &LEVELPATH)
{
    sceneLevelPath = LEVELPATH;
}

// - - - - - - - - - - -

void ScenePlay::setControls(std::string& CONTROLSPECIFICATIONFILE)
{
    std::ifstream controlsFile(CONTROLSPECIFICATIONFILE);
    if (!controlsFile.is_open())
    {
        std::cerr << "Could not open file: " << CONTROLSPECIFICATIONFILE << std::endl;
        return;
    }
    std::string line;
    while (std::getline(controlsFile, line))
    {
        std::istringstream iss(line);
        std::string controlName;
        int controlKey;
        iss >> controlName >> controlKey;
        if (controlName == "Jump")
        {
            registerAction(controlKey, "UP");
        }
        else if (controlName == "Left")
        {
            registerAction(controlKey, "LEFT");
        }
        else if (controlName == "Right")
        {
            registerAction(controlKey, "RIGHT");
        }
        else if (controlName == "Shoot")
        {
            registerAction(controlKey, "SHOOT");
        }
    }
}

// - - - - - - - - - - -

void ScenePlay::init()
{
    sceneGridText.setCharacterSize(12);
    sf::Font gridTextFont;
    gridTextFont.loadFromFile(R"(..\\Assets\\Fonts\\)" + sceneGameEngine->getAssets().fAsset["PixeloidMono"].fPath);
    sceneGridText.setFont(gridTextFont);
    std::cout << "_ _ _ _ _ SCENE PLAY MESSAGE _ _ _ _ _" << std::endl;
    loadLevel(sceneLevelPath);
    std::cout << "Level loaded" << std::endl;
    std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _" << std::endl << std::endl;

    registerAction(sf::Keyboard::F5, "TOGGLE_GRID");
    registerAction(sf::Keyboard::F6, "TOGGLE_HITBOXES");
    registerAction(sf::Keyboard::F7, "TOGGLE_TEXTURES");
    registerAction(sf::Keyboard::Escape, "QUIT");
}

// - - - - - - - - - - -

Vector2D ScenePlay::gridToMidPixel(int GRIDX, int GRIDY)
{
    int totalTilesY = sceneGameEngine->getWindow().getSize().y / sceneGridSize.y;
    GRIDY = totalTilesY - GRIDY - 1;
    return Vector2D(GRIDX*64 + 32, GRIDY*64 + 32);
}

// - - - - - - - - - - -

void ScenePlay::loadLevel(const std::string &FILEPATH)
{
    std::cout << "Loading level" << std::endl;
    sceneEntityManager = EntityManager();
    std::cout << "Entity Manager created" << std::endl;
    std::ifstream assetsFile(FILEPATH);
    if (!assetsFile.is_open())
    {
        std::cerr << "Could not open file: " << FILEPATH << std::endl;
        return;
    }
    std::cout << "File opened" << std::endl;
    std::cout << "Beginning to read file" << std::endl;
    std::string line;
    gPlayer = sceneEntityManager.createEntity("player");
    while (std::getline(assetsFile, line))
    {
        std::istringstream iss(line);
        std::string blockType;
        std::string name;
        int GX, GY;
        iss >> blockType;
        if (blockType[0] == 'P')
        {
            iss >> scenePlayerConfigurations.x >> scenePlayerConfigurations.y >> scenePlayerConfigurations.cX >> scenePlayerConfigurations.cY >> scenePlayerConfigurations.speed >> scenePlayerConfigurations.maxSpeed >> scenePlayerConfigurations.jump >> scenePlayerConfigurations.gravity >> scenePlayerConfigurations.WEAPON;
            std::cout << "Player data read" << std::endl;
            break;
        }
        iss >> name >> GX >> GY;
        auto creation = sceneEntityManager.createEntity(name);
        std::cout << "Entity created" << std::endl;
        switch (blockType[0])
        {
            case 'T':
                creation->addComponent<CSprite>();
                creation->addComponent<CTransform>(gridToMidPixel(GX, GY), Vector2D(0, 0), 0);
                creation->addComponent<CTexture>(std::make_shared<Assets::AnimationAsset>(sceneGameEngine->getAssets().aAsset[name]));
                creation->eAnimation = new Animation(name, &creation->getComponent<CSprite>().sprite, sceneGameEngine->getAssets().aAsset[name].aSpriteSheetPath, sceneGameEngine->getAssets().aAsset[name].aFrameCount, sceneGameEngine->getAssets().aAsset[name].aSpeed, creation->getComponent<CTransform>().scale);
                std::cout << "Adding Tile" << std::endl;

            /*case 'P':
                //add stuff to PlayerConfig
                scenePlayerConfigurations.x = GX;
                scenePlayerConfigurations.y = GY;
                scenePlayerConfigurations.cX = 48;
                scenePlayerConfigurations.cY = 48;
                scenePlayerConfigurations.speed = 1;
                scenePlayerConfigurations.maxSpeed = 3;
                scenePlayerConfigurations.jump = 3;
                scenePlayerConfigurations.gravity = 0.1f;
                scenePlayerConfigurations.WEAPON = "Fireball";
//

                gPlayer->addComponent<CHitBox>(creation->getComponent<CTransform>().position ,Vector2D(48, 48));
                gPlayer->addComponent<CGravity>(0.1f);
                gPlayer->addComponent<CState>("stand");
                gPlayer->addComponent<CInput>();
                std::cout << "Adding Player data" << std::endl;
                break;
                */

            case 'E':
                creation->addComponent<CTexture>(std::make_shared<Assets::AnimationAsset>(sceneGameEngine->getAssets().aAsset[name]));
                creation->addComponent<CTransform>(gridToMidPixel(GX, GY), Vector2D(0, 0), 0);
                creation->addComponent<CHitBox>(creation->getComponent<CTransform>().position ,Vector2D(48, 48));
                creation->addComponent<CGravity>(0.1f);
                creation->addComponent<CState>("stand");
                creation->addComponent<CSprite>();
                creation->addComponent<CInput>();
                std::cout << "Adding Enemy data" << std::endl;
                break;

            case 'B':
                creation->addComponent<CTexture>(std::make_shared<Assets::AnimationAsset>(sceneGameEngine->getAssets().aAsset[name]));
                creation->addComponent<CTransform>(gridToMidPixel(GX, GY), Vector2D(0, 0), 0);
                creation->addComponent<CHitBox>(creation->getComponent<CTransform>().position ,Vector2D(48, 48));
                creation->addComponent<CGravity>(0.1f);
                creation->addComponent<CState>("stand");
                creation->addComponent<CSprite>();
                creation->addComponent<CInput>();
                std::cout << "Adding Block data" << std::endl;
                break;

            case 'C':
                creation->addComponent<CTexture>(std::make_shared<Assets::AnimationAsset>(sceneGameEngine->getAssets().aAsset[name]));
                creation->addComponent<CTransform>(gridToMidPixel(GX, GY), Vector2D(0, 0), 0);
                creation->addComponent<CHitBox>(creation->getComponent<CTransform>().position ,Vector2D(48, 48));
                creation->addComponent<CSprite>();
                creation->addComponent<CInput>();
                std::cout << "Adding Coin data" << std::endl;
                break;

            case 'F':
                creation->addComponent<CTexture>(std::make_shared<Assets::AnimationAsset>(sceneGameEngine->getAssets().aAsset[name]));
                creation->addComponent<CTransform>(gridToMidPixel(GX, GY), Vector2D(0, 0), 0);
                creation->addComponent<CHitBox>(creation->getComponent<CTransform>().position ,Vector2D(48, 48));
                creation->addComponent<CGravity>(0.1f);
                creation->addComponent<CState>("stand");
                creation->addComponent<CSprite>();
                creation->addComponent<CInput>();
                std::cout << "Adding Fireball data" << std::endl;
                break;
        }
    }
    spawnPlayer();
    std::cout << "Player created" << std::endl;
}

// - - - - - - - - - - -

void ScenePlay::spawnPlayer()
{
    std::cout << " _ _ _ _ _ _ SCENE PLAY MESSAGE _ _ _ _ _ _" << std::endl;
    std::cout << "Spawning player" << std::endl;
    gPlayer = sceneEntityManager.createEntity("player");
    std::cout << "Texture added" << std::endl;
    gPlayer->addComponent<CTransform>(Vector2D(scenePlayerConfigurations.x, scenePlayerConfigurations.y), Vector2D(0, 0), 0);
    std::cout << "Transform added" << std::endl;
    gPlayer->addComponent<CSprite>();
    std::cout << "Sprite added" << std::endl;
    gPlayer->addComponent<CTexture>(std::make_shared<Assets::AnimationAsset>(sceneGameEngine->getAssets().aAsset["Stand"]));
    std::cout << "Texture added" << std::endl;
    gPlayer->addComponent<CHitBox>(gPlayer->getComponent<CTransform>().position, Vector2D(scenePlayerConfigurations.cX, scenePlayerConfigurations.cY));
    std::cout << "Hitbox added" << std::endl;
    gPlayer->addComponent<CGravity>(scenePlayerConfigurations.gravity);
    std::cout << "Gravity added" << std::endl;
    gPlayer->addComponent<CState>("stand");
    std::cout << "State added" << std::endl;
    gPlayer->addComponent<CInput>();
    std::cout << "Input added" << std::endl;
    std::cout << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ __ _ _ _ _ _" << std::endl << std::endl;
}

// - - - - - - - - - - -

void ScenePlay::update()
{
    sceneEntityManager.update();
    sRender();
    if (!scenePaused)
    {
        sMovement();
        sLifespan();
        sCollision();
        sAnimation();
    }
}

// - - - - - - - - - - -

void ScenePlay::sMovement()
{
    Vector2D playerVelocity(0, gPlayer->getComponent<CTransform>().velocity.y);
    if (gPlayer->getComponent<CInput>().up)
    {
        gPlayer->getComponent<CState>().state = "jump";
        playerVelocity.y = -3;
    }
    if (gPlayer->getComponent<CInput>().left)
    {
        gPlayer->getComponent<CTransform>().velocity.x = -1;
        gPlayer->getComponent<CTransform>().scale.x = -1;
        gPlayer->getComponent<CState>().state = "running";
    }
    if (gPlayer->getComponent<CInput>().right)
    {
        gPlayer->getComponent<CTransform>().velocity.x = 1;
        gPlayer->getComponent<CTransform>().scale.x = 1;
        gPlayer->getComponent<CState>().state = "running";
    }
    if (gPlayer->getComponent<CInput>().shoot)
    {
        spawnFireBall();
        gPlayer->getComponent<CState>().state = "shooting";
    }
    if (std::abs(gPlayer->getComponent<CTransform>().velocity.x) < 0.1f && std::abs(gPlayer->getComponent<CTransform>().velocity.y) < 0.1f)
    {
        gPlayer->getComponent<CState>().state = "stand";
    }

    if (gPlayer->getComponent<CTransform>().velocity.y > scenePlayerConfigurations.maxSpeed)
    {
        gPlayer->getComponent<CTransform>().velocity.y = scenePlayerConfigurations.maxSpeed;
    }
    if (gPlayer->getComponent<CTransform>().velocity.y < -scenePlayerConfigurations.maxSpeed)
    {
        gPlayer->getComponent<CTransform>().velocity.y = -scenePlayerConfigurations.maxSpeed;
    }
    if (gPlayer->getComponent<CTransform>().velocity.x > scenePlayerConfigurations.maxSpeed)
    {
        gPlayer->getComponent<CTransform>().velocity.x = scenePlayerConfigurations.maxSpeed;
    }
    if (gPlayer->getComponent<CTransform>().velocity.x < -scenePlayerConfigurations.maxSpeed)
    {
        gPlayer->getComponent<CTransform>().velocity.x = -scenePlayerConfigurations.maxSpeed;
    }

    gPlayer->getComponent<CTransform>().velocity = playerVelocity;

    for (auto e :sceneEntityManager.getEntities())
    {
        if (e->hasComponent<CGravity>())
        {
            e->getComponent<CTransform>().velocity.y += e->getComponent<CGravity>().gravity;
        }
        e->getComponent<CTransform>().position += e->getComponent<CTransform>().velocity;
    }
}

// - - - - - - - - - - -

void ScenePlay::sLifespan()
{
    for (auto e : sceneEntityManager.getEntities())
    {
        if (e->hasComponent<CLifespan>())
        {
            e->getComponent<CLifespan>().remaining--;
            if (e->getComponent<CLifespan>().remaining <= 0)
            {
                sceneEntityManager.killEntity(e);
            }
        }
    }
}

// - - - - - - - - - - -

void ScenePlay::sCollision()
{
    for (auto e : sceneEntityManager.getEntities())
    {
        if (e->hasComponent<CHitBox>())
        {
            auto& hitBox = e->getComponent<CHitBox>();
            hitBox.previousPosition = hitBox.position;
            hitBox.position = e->getComponent<CTransform>().position;
        }
    }
    for (auto e: sceneEntityManager.getEntities("tile"))
    {
        Vector2D currentOverlap = Physics::getOverlap(gPlayer, e);
        Vector2D previousOverlap = Physics::getPreviousOverlap(gPlayer, e);
        if (currentOverlap.x > 0 && currentOverlap.y > 0)
        {
            if (previousOverlap.y > 0)
            {
                gPlayer->getComponent<CTransform>().position.x += currentOverlap.x;
                break;
            }
            if (previousOverlap.x > 0)
            {
                gPlayer->getComponent<CTransform>().position.y += currentOverlap.y;
                break;
            }
        }
    }
    if (gPlayer->getComponent<CTransform>().position.y > sceneGameEngine->getWindow().getSize().y)
    {
        onEnd();
    }
}

// - - - - - - - - - - -

void ScenePlay::sDoAction(const Action &ACTION)
{
    const std::string type = ACTION.getType();
    const std::string name = ACTION.getName();
    if (type == "START")
    {
        if (name == "UP")
        {
            gPlayer->getComponent<CInput>().up = true;
        }
        if (name == "DOWN")
        {
            gPlayer->getComponent<CInput>().down = true;
        }
        if (name == "LEFT")
        {
            gPlayer->getComponent<CInput>().left = true;
        }
        if (name == "RIGHT")
        {
            gPlayer->getComponent<CInput>().right = true;
        }
        else if (name == "PAUSE")
        {
            setPaused(!scenePaused);
        }
        else if (name == "QUIT")
        {
            onEnd();
        }
        else if (name == "TOGGLE_TEXTURES")
        {
            sceneDrawTextures = !sceneDrawTextures;
        }
        else if (name == "TOGGLE_HITBOXES")
        {
            sceneDrawHitboxes = !sceneDrawHitboxes;
        }
        else if (name == "TOGGLE_GRID")
        {
            sceneDrawGrid = !sceneDrawGrid;
        }
    }
    else if (type == "END")
    {
        if (name == "UP")
        {
            gPlayer->getComponent<CInput>().up = false;
        }
        if (name == "DOWN")
        {
            gPlayer->getComponent<CInput>().down = false;
        }
        if (name == "LEFT")
        {
            gPlayer->getComponent<CInput>().left = false;
        }
        if (name == "RIGHT")
        {
            gPlayer->getComponent<CInput>().right = false;
        }
    }
}

// - - - - - - - - - - -

void ScenePlay::sAnimation()
{
    if (gPlayer->getComponent<CState>().state == "jumping")
    {
        gPlayer->addComponent<CTexture>(std::make_shared<Assets::AnimationAsset>((sceneGameEngine->getAssets().aAsset["Jump"])));
    }
    else if (gPlayer->getComponent<CState>().state == "stand")
    {
        gPlayer->addComponent<CTexture>(std::make_shared<Assets::AnimationAsset>((sceneGameEngine->getAssets().aAsset["Stand"])));
    }
    else if (gPlayer->getComponent<CState>().state == "running")
    {
        gPlayer->addComponent<CTexture>(std::make_shared<Assets::AnimationAsset>((sceneGameEngine->getAssets().aAsset["Run"])));
    }
}

// - - - - - - - - - - -

void ScenePlay::onEnd()
{
    sceneGameEngine->changeScene("MENU", sceneGameEngine->gSceneMap["MENU"], "MENU", true, true);
}

// - - - - - - - - - - -

void ScenePlay::spawnFireBall()
{
    auto fireBall = sceneEntityManager.createEntity("fireball");
    fireBall->addComponent<CTransform>(gPlayer->getComponent<CTransform>().position, Vector2D(0, 0), 0);
    fireBall->addComponent<CTexture>(std::make_shared<Assets::AnimationAsset>(sceneGameEngine->getAssets().aAsset["Fireball"]));
    fireBall->addComponent<CHitBox>(fireBall->getComponent<CTransform>().position, Vector2D(48, 48));
    fireBall->addComponent<CLifespan>(100);
    fireBall->addComponent<CInput>();
    fireBall->getComponent<CTransform>().velocity.x = 1;
}

// - - - - - - - - - - -

void ScenePlay::drawLine(const Vector2D &V1, const Vector2D &V2)
{
    sf::Vertex line[] = {sf::Vertex(sf::Vector2f(V1.x, V1.y)), sf::Vertex(sf::Vector2f(V2.x, V2.y))};
    sceneGameEngine->getWindow().draw(line, 2, sf::Lines);
}

// - - - - - - - - - - -

void ScenePlay::sRender()
{
    if (!scenePaused)
    {
        sceneGameEngine->getWindow().clear(sf::Color(100, 100, 255));
    }
    else
    {
        sceneGameEngine->getWindow().clear(sf::Color(50, 50, 255));
    }

    auto& pPos = gPlayer->getComponent<CTransform>().position;
    float windowCenterX = std::max(sceneGameEngine->getWindow().getSize().x / 2.0f, pPos.x);
    sf::View camera = sceneGameEngine->getWindow().getView();
    camera.setCenter(windowCenterX, sceneGameEngine->getWindow().getSize().y - camera.getCenter().y);
    sceneGameEngine->getWindow().setView(camera);

    if (sceneDrawTextures)
    {
        std::cout << "Rendering textures" << std::endl;
        for (auto e : sceneEntityManager.getEntities())
        {
            auto& transform = e->getComponent<CTransform>();

            if (e->hasComponent<CTexture>())
            {
                sf::Sprite currentSprite;
                currentSprite = e->getComponent<CSprite>().sprite;
                auto& animation = e->getComponent<CTexture>();
                std::string currentAnimation = animation.getName();
                Animation animator(currentAnimation, &currentSprite, animation.spriteSheetPath, animation.frameCount, animation.speed, e->getComponent<CTransform>().scale);
                currentSprite.setPosition(transform.position.x, transform.position.y);
                currentSprite.setScale(transform.scale.x, transform.scale.y);
                currentSprite.setOrigin(animator.getSize().x/2.f, animator.getSize().y/2.f);
                currentSprite.setTexture(animation.texture);
                sceneGameEngine->getWindow().draw(currentSprite);
                std::cout << "Texture rendered" << std::endl;
            }
        }
    }

    if (sceneDrawHitboxes)
    {
        for (auto e : sceneEntityManager.getEntities())
        {
            if (e->hasComponent<CHitBox>())
            {
                auto& box = e->getComponent<CHitBox>();
                auto& transform = e->getComponent<CTransform>();
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(box.size.x-1, box.size.y-1));
                rect.setOrigin(sf::Vector2f(box.halfSize.x, box.halfSize.y));
                rect.setPosition(transform.position.x, transform.position.y);
                rect.setFillColor(sf::Color(0,0,0,0));
                rect.setOutlineColor(sf::Color(255, 255, 255, 255));
                rect.setOutlineThickness(1);
                sceneGameEngine->getWindow().draw(rect);
            }
        }
    }

    if (sceneDrawGrid)
    {
        float width = sceneGameEngine->getWindow().getSize().x;
        float height = sceneGameEngine->getWindow().getSize().y;
        float leftX = sceneGameEngine->getWindow().getView().getCenter().x - width/2;
        float rightX = leftX + width + sceneGridSize.x;
        float nextGridX = leftX - ((int)leftX % (int)sceneGridSize.x);

        for (float x = nextGridX; x < rightX; x += sceneGridSize.x)
        {
            drawLine(Vector2D(x, 0), Vector2D(x, height));
        }

        for (float y = 0; y < height; y+= sceneGridSize.y)
        {
            drawLine(Vector2D(leftX, height), Vector2D(rightX, height));

            for (float x = nextGridX; x < rightX; x+= sceneGridSize.x)
            {
                std::string xCell = std::to_string((int)x / (int) sceneGridSize.x);
                std::string yCell = std::to_string((int)y / (int) sceneGridSize.y);
                sceneGridText.setString("(" + xCell + ", " + yCell + ")");
                sceneGridText.setPosition(x + 3, height - y - sceneGridSize.y + 2);
                sceneGameEngine->getWindow().draw(sceneGridText);
            }
        }
    }
}



