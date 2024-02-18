#include "ScenePlay.h"
#include "Physics.h"
#include "Assets.h"
#include "GameEngine.h"
#include "Components.h"
#include "Action.h"
#include "Animation.h"
#include "Scene.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
// - - - - - - - - - -

ScenePlay::ScenePlay(GameEngine* GAMEENGINE, std::string LEVELPATH)
: Scene(GAMEENGINE), sceneLevelPath(LEVELPATH)
{
    init(sceneLevelPath);
}

// - - - - - - - - - - -

void ScenePlay::registerAction(int INPUTKEY, const std::string &ACTIONNAME)
{
    sceneActionMap[INPUTKEY] = ACTIONNAME;
}

// - - - - - - - - - - -

void ScenePlay::init(const std::string &LEVELPATH)
{
    sceneGridText.setCharacterSize(12);
    sf::Font gridTextFont;
    gridTextFont.loadFromFile(sceneGameEngine->getAssets().fAsset["BigPixel"].fPath);
    sceneGridText.setFont(gridTextFont);
    loadLevel(sceneLevelPath);

    registerAction(sf::Keyboard::F5, "TOGGLE_GRID");
    registerAction(sf::Keyboard::F6, "TOGGLE_HITBOXES");
    registerAction(sf::Keyboard::F7, "TOGGLE_TEXTURES");
    registerAction(sf::Keyboard::Escape, "QUIT");
}

// - - - - - - - - - - -

Vector2D ScenePlay::gridToMidPixel(int GRIDX, int GRIDY, std::shared_ptr<Entity> ENTITY)
{
    int totalTilesY = sceneGameEngine->getWindow().getSize().y / sceneGridSize.y;
    GRIDY = totalTilesY - GRIDY - 1;
    return Vector2D(GRIDX*64 + 32, GRIDY*64 + 32);
}

// - - - - - - - - - - -

void ScenePlay::loadLevel(const std::string &FILEPATH)
{
    //TODO: Do this after we have a format for the level file
    // and
    sceneEntityManager = EntityManager();
    std::ifstream assetsFile(FILEPATH);
    if (!assetsFile.is_open())
    {
        std::cerr << "Could not open file: " << FILEPATH << std::endl;
        return;
    }
    std::string line;
    while (std::getline(assetsFile, line))
    {
        std::istringstream iss(line);
        std::string blockType;
        std::string name;
        int GX, GY;
        iss >> blockType >> name >> GX >> GY;
        switch (blockType[0])
        {
            case 'T':
                auto tile = sceneEntityManager.createEntity(name);
                tile->addComponent<CTexture>(sceneGameEngine->getAssets().aAsset);

            case 'P':
                auto player = sceneEntityManager.createEntity(name);
                player->addComponent<CTexture>(sceneGameEngine->getAssets().aAsset);
                player->addComponent<CTransform>(gridToMidPixel(GX, GY, player));
                player->addComponent<CHitBox>(Vector2D(48, 48));
                player->addComponent<CGravity>(0.1f);
                player->addComponent<CState>("stand");
                player->addComponent<CInput>();
                break;

            case 'E':
                auto enemy = sceneEntityManager.createEntity(name);
                enemy->addComponent<CTexture>(sceneGameEngine->getAssets().aAsset);
                enemy->addComponent<CTransform>(gridToMidPixel(GX, GY, enemy));
                enemy->addComponent<CHitBox>(Vector2D(48, 48));
                enemy->addComponent<CGravity>(0.1f);
                enemy->addComponent<CState>("stand");
                enemy->addComponent<CInput>();
                break;

            case 'B':
                auto brick = sceneEntityManager.createEntity(name);
                brick->addComponent<CTexture>(sceneGameEngine->getAssets().aAsset);
                brick->addComponent<CTransform>(gridToMidPixel(GX, GY, brick));
                brick->addComponent<CHitBox>(Vector2D(48, 48));
                brick->addComponent<CGravity>(0.1f);
                brick->addComponent<CState>("stand");
                brick->addComponent<CInput>();
                break;

            case 'C':
                auto coin = sceneEntityManager.createEntity(name);
                coin->addComponent<CTexture>(sceneGameEngine->getAssets().aAsset);
                coin->addComponent<CTransform>(gridToMidPixel(GX, GY, coin));
                coin->addComponent<CHitBox>(Vector2D(48, 48));
                coin->addComponent<CGravity>(0.1f);
                coin->addComponent<CState>("stand");
                coin->addComponent<CInput>();
                break;

            case 'F':
                auto fireball = sceneEntityManager.createEntity(name);
                fireball->addComponent<CTexture>(sceneGameEngine->getAssets().aAsset);
                fireball->addComponent<CTransform>(gridToMidPixel(GX, GY, fireball));
                fireball->addComponent<CHitBox>(Vector2D(48, 48));
                fireball->addComponent<CGravity>(0.1f);
                fireball->addComponent<CState>("stand");
                fireball->addComponent<CInput>();
                break;
        }
    }

    spawnPlayer();
}

// - - - - - - - - - - -

void ScenePlay::spawnPlayer()
{
    gPlayer->addComponent<CTransform>(Vector2D(224, 352));
    gPlayer->addComponent<CSprite>();
    gPlayer = sceneEntityManager.createEntity("player");
    gPlayer->addComponent<CTexture>(sceneGameEngine->getAssets().aAsset["Stand"]);
    gPlayer->addComponent<CHitBox>(Vector2D(48, 48));
    gPlayer->addComponent<CGravity>(0.1f);
    gPlayer->addComponent<CState>("stand");
    gPlayer->addComponent<CInput>();
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
    if (gPlayer->getComponent<CTransform>().position.y > getHeight())
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
        gPlayer->addComponent<CTexture>(sceneGameEngine->getAssets().aAsset["Jump"], true);
    }
    else if (gPlayer->getComponent<CState>().state == "stand")
    {
        gPlayer->addComponent<CTexture>(sceneGameEngine->getAssets().aAsset["Stand"], true);
    }
    else if (gPlayer->getComponent<CState>().state == "running")
    {
        gPlayer->addComponent<CTexture>(sceneGameEngine->getAssets().aAsset["Run"], true);
    }
}

// - - - - - - - - - - -

void ScenePlay::onEnd()
{
    sceneGameEngine->changeScene("Menu", sceneGameEngine->gSceneMap["Menu"]);
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
        for (auto e : sceneEntityManager.getEntities())
        {
            auto& transform = e->getComponent<CTransform>();

            if (e->hasComponent<CTexture>())
            {
                sf::Sprite currentSprite;
                currentSprite = e->getComponent<CSprite>().sprite;
                auto& animation = e->getComponent<CTexture>();
                Animation animator(animation.getName(), currentSprite, animation.spriteSheetPath, animation.frameCount, animation.speed);
                currentSprite.setPosition(transform.position.x, transform.position.y);
                currentSprite.setScale(transform.scale.x, transform.scale.y);
                currentSprite.setOrigin(animator.getSize().x/2.f, animator.getSize().y/2.f);
                currentSprite.setTexture(animation.texture);
                sceneGameEngine->getWindow().draw(currentSprite);
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
        float leftX = sceneGameEngine->getWindow().getView().getCenter().x - getWidth()/2;
        float rightX = leftX + getWidth() + sceneGridSize.x;
        float nextGridX = leftX - ((int)leftX % (int)sceneGridSize.x);

        for (float x = nextGridX; x < rightX; x += sceneGridSize.x)
        {
            drawLine(Vector2D(x, 0), Vector2D(x, getHeight()));
        }

        for (float y = 0; y < getHeight(); y+= sceneGridSize.y)
        {
            drawLine(Vector2D(leftX, getHeight()), Vector2D(rightX, getHeight()));

            for (float x = nextGridX; x < rightX; x+= sceneGridSize.x)
            {
                std::string xCell = std::to_string((int)x / (int) sceneGridSize.x);
                std::string yCell = std::to_string((int)y / (int) sceneGridSize.y);
                sceneGridText.setString("(" + xCell + ", " + yCell + ")");
                sceneGridText.setPosition(x + 3, getHeight() - y - sceneGridSize.y + 2);
                sceneGameEngine->getWindow().draw(sceneGridText);
            }
        }
    }
}
