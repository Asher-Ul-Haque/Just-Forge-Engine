#include "Game.h"
#include <cmath>
#include <string>
#include <random>
#include <iostream>
#include <unistd.h>

Game::Game()
{
    init();
}

void Game::init()
{
    gRoot.create(sf::VideoMode(1280, 720), "SPACE SHOOTER");
    gRoot.setFramerateLimit(60);
    spawnPlayer();
    gPlayer->cLifespan = std::make_shared<CLifespan>(5);
    gScore = 0;
    gFont.loadFromFile(R"(../Assets/Fonts/pixelFont.ttf)");
    gExplosionTexture.loadFromFile(R"(../Assets/Images/Explosion.png)");
    gLifeData.setFont(gFont);
    gLifeData.setCharacterSize(24);
    gLifeData.setFillColor(sf::Color(0,255, 0, 255));
    gLifeData.setOutlineColor(sf::Color(100,255, 100, 255));
    gScoreData.setFont(gFont);
    gScoreData.setCharacterSize(24);
    gScoreData.setFillColor(sf::Color(0,255, 0, 255));
    gScoreData.setOutlineColor(sf::Color(100,255, 100, 255));
    gScoreData.setPosition(100, 650);
    gLifeData.setPosition(1000, 650);
}

void Game::run()
{
    gPaused = false;
    gRunning = true;
    /*while (gRunning && !gPaused)
    {
        gEntityManager.update();
        if (!gPaused)
        {
            sEnemySpawner();
            sMovement();
            sCollision();
            sUserInput();
        }
        gCurrentFrame++;
        sRender();
    }*/
    while (gRunning)
    {
        sRender();
        gEntityManager.update();
        sUserInput();
        if (!gPaused)
        {
            sEnemySpawner();
            sMovement();
            sCollision();
            sDataDisplay();
            gCurrentFrame++;
        }
    }
}

void Game::spawnPlayer()
{
    auto player = gEntityManager.createEntity("player");
    player->cTransform = std::make_shared<CTransform>(Vector2D(590, 340), Vector2D(0.f, 0.f), 0);
    Vector2D mySize(100, 100);
    player->cSprite = std::make_shared<CSprite>(R"(../Assets/Images/SpaceShipStand.png)", mySize);
    //ASK THIS DOUBT FROM T.A.   WHY DOES THIS NOT WORK
    //player->cSprite = std::make_shared<CSprite>(R"(../Assets/Images/SpaceShipMove.png)", Vector2D(100, 100));
    player->cInput = std::make_shared<CInput>(R"(../Assets/Images/SpaceShipMove.png)");
    gPlayer = player;
}

void Game::spawnBullet(const Vector2D &POSITION)
{
    /*Vector2D mousePosition(sf::Mouse::getPosition(gRoot).x, sf::Mouse::getPosition(gRoot).y);
    float angle = atan2(mousePosition.y - gPlayer->cTransform->position.y, mousePosition.x - gPlayer->cTransform->position.x);*/
    auto bullet = gEntityManager.createEntity("bullet");
    float angle = gPlayer->cTransform->angle * 3.14159f/180.f;

    bullet->cTransform = std::make_shared<CTransform>(Vector2D(gPlayer->cTransform->position.x, gPlayer->cTransform->position.y), Vector2D(cos(angle), sin(angle)), angle * 180.f/3.14159f);
    Vector2D mySize(20, 20);
    //ADD A BULLET IMAGE
    bullet->cSprite = std::make_shared<CSprite>(R"(../Assets/Images/Bullet.png)", mySize);
    //ASK THIS DOUBT FROM T.A.
}

void Game::spawnEnemy()
{
    gLastEnemySpawnTime = gCurrentFrame;
    auto enemy = gEntityManager.createEntity("enemy");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> sizeRandomness(100, 500);
    std::uniform_real_distribution<float> scaleRandomness(0.5f, 2.f);
    std::uniform_real_distribution<float> speedRandomness(0.1f, 15.f + (30-gEnemySpawnMinWait));
    std::uniform_int_distribution<int> positionXRandomness(0, 1280);
    std::uniform_int_distribution<int> positionYRandomness(0, 720);

    int size = sizeRandomness(gen);
    float speed = speedRandomness(gen);
    float scale = scaleRandomness(gen);

    Vector2D mySize(size, size);
    enemy->cSprite = std::make_shared<CSprite>(R"(../Assets/Images/Asteroid.png)", mySize);
    enemy->cTransform = std::make_shared<CTransform>(Vector2D(gPlayer->cTransform->position.x, 0), Vector2D(0, 0), 0);
    float angle = atan2(gPlayer->cTransform->position.y, gPlayer->cTransform->position.x - positionXRandomness(gen));
    enemy->cTransform->velocity.x = speed * std::cos(angle);
    enemy->cTransform->velocity.y = speed * std::sin(angle);
    enemy->cTransform->angle = angle * 180.f/3.14159f;
    gEntityManager.setScale(scale, enemy);



    /*while (enemy->cTransform->position.x < 100 || enemy->cTransform->position.x > 1000 || enemy->cTransform->position.y < 100 || enemy->cTransform->position.y > 500)
    {
        enemy->cTransform->position.x = positionXRandomness(gen);
        enemy->cTransform->position.y = positionYRandomness(gen);
    }

    float angle = atan2(gPlayer->cTransform->position.y - positionXRandomness(gen), gPlayer->cTransform->position.x - positionYRandomness(gen));



    enemy->cTransform->angle = angle * 180.f/3.14159f;
    enemy->cTransform->position.x = 1000/std::cos(angle);
    enemy->cTransform->position.y = 500/std::sin(angle);
    enemy->cTransform->velocity.x = speed * std::cos(angle);
    enemy->cTransform->velocity.y = speed * std::sin(angle);
    std::cout << "Enemy position: " << enemy->cTransform->position.x << ", " << enemy->cTransform->position.y << std::endl;
    std::cout << "Enemy velocity: " << enemy->cTransform->velocity.x << ", " << enemy->cTransform->velocity.y << std::endl;
    std::cout << "Enemy angle: " << enemy->cTransform->angle << "cos:" << std::cos(angle) << " sin: " << std::sin(angle) << std::endl;*/

}

void Game::sRender()
{
    gRoot.clear();
    gPlayer->cSprite->sprite.setPosition(gPlayer->cTransform->position.x, gPlayer->cTransform->position.y);
    gPlayer->cSprite->sprite.setRotation(gPlayer->cTransform->angle);
    gRoot.draw(gPlayer->cSprite->sprite);
    gRoot.draw(gLifeData);
    gRoot.draw(gScoreData);
    gEntityManager.getEntities();
    int count = 0;
    for (auto e : gEntityManager.getEntities("bullet"))
    {
        e->cSprite->sprite.setPosition(e->cTransform->position.x, e->cTransform->position.y);
        e->cSprite->sprite.setRotation(e->cTransform->angle);
        gRoot.draw(e->cSprite->sprite);
    }
    for (auto e : gEntityManager.getEntities("enemy"))
    {
        e->cSprite->sprite.setPosition(e->cTransform->position.x, e->cTransform->position.y);
        e->cSprite->sprite.setRotation(e->cTransform->angle);
        gRoot.draw(e->cSprite->sprite);
    }
    gRoot.display();
}

void Game::sEnemySpawner()
{
    gEnemySpawnMinWait -= 0.f;
    if (gEnemySpawnMinWait < 0.1f)
    {
        gEnemySpawnMinWait = 0.1f;
    }
    if (gCurrentFrame - gLastEnemySpawnTime >= gEnemySpawnMinWait)
    {
        spawnEnemy();
        gLastEnemySpawnTime = gCurrentFrame;
    }
}

void Game::sUserInput()
{
    sf::Event event;

    while (gRoot.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            gRunning = false;
            gRoot.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            gPlayer->cSprite->textureAddress = R"(../Assets/Images/SpaceShipMove.png)";
            gPlayer->cSprite->texture.loadFromFile(gPlayer->cSprite->textureAddress, sf::IntRect(0 ,0 ,gPlayer->cSprite->size.x, gPlayer->cSprite->size.y));
            gPlayer->cSprite->sprite.setTexture(gPlayer->cSprite->texture);

            switch(event.key.code)
            {
                case sf::Keyboard::W:
                    std::cout << "W was pressed" << std::endl;
                    gPlayer->cInput->up = true;
                    break;

                case sf::Keyboard::S:
                    std::cout << "S was pressed" << std::endl;
                    gPlayer->cInput->down = true;
                    break;

                case sf::Keyboard::A:
                    std::cout << "A was pressed" << std::endl;
                    gPlayer->cInput->left = true;
                    break;

                case sf::Keyboard::D:
                    std::cout << "D was pressed" << std::endl;
                    gPlayer->cInput->right = true;
                    break;

                case sf::Keyboard::Space:
                    std::cout << "SpaceBar was Pressed" << std::endl;
                    gPlayer->cInput->shoot = true;
                    break;

                case sf::Keyboard::Escape:
                    gRunning = false;
                    break;

                case sf::Keyboard::P:
                    gPaused = !gPaused;
                    break;

                default:
                    break;
            }

        }

        if (event.type == sf::Event::KeyReleased)
        {
            gPlayer->cSprite->textureAddress = R"(../Assets/Images/SpaceShipStand.png)";
            gPlayer->cSprite->texture.loadFromFile(gPlayer->cSprite->textureAddress, sf::IntRect(0 ,0 ,gPlayer->cSprite->size.x, gPlayer->cSprite->size.y));
            gPlayer->cSprite->sprite.setTexture(gPlayer->cSprite->texture);

            switch(event.key.code)
            {
                case sf::Keyboard::W:
                    std::cout << "W was released" << std::endl;
                    gPlayer->cInput->up = false;
                    break;

                case sf::Keyboard::S:
                    std::cout << "S was released" << std::endl;
                    gPlayer->cInput->down = false;
                    break;

                case sf::Keyboard::A:
                    std::cout << "A was released" << std::endl;
                    gPlayer->cInput->left = false;
                    break;

                case sf::Keyboard::D:
                    std::cout << "D was released" << std::endl;
                    gPlayer->cInput->right = false;
                    break;

                case sf::Keyboard::Space:
                    std::cout << "SpaceBar was Released" << std::endl;
                    gPlayer->cInput->shoot = false;
                    break;

                default:
                    break;
            }

        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            gPlayer->cInput->shoot = true;
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {
            gPlayer->cInput->shoot = false;
        }
    }


}

void Game::sMovement()
{
    gPlayer->cTransform->velocity = {0.f, 0.f};
    if (gPlayer->cInput->up)
    {
        gPlayer->cTransform->velocity.x = 10 * std::cos(gPlayer->cTransform->angle * 3.14159f/180.f);
        gPlayer->cTransform->velocity.y = 10 * std::sin(gPlayer->cTransform->angle * 3.14159f/180.f);
    }
    if (gPlayer->cInput->down)
    {
        gPlayer->cTransform->velocity.x = - 10 * std::cos(gPlayer->cTransform->angle * 3.14159f/180.f);
        gPlayer->cTransform->velocity.y = - 10 * std::sin(gPlayer->cTransform->angle * 3.14159f/180.f);
    }
    if (gPlayer->cInput->left)
    {
        gPlayer->cTransform->velocity.x = - 10 * std::cos(gPlayer->cTransform->angle * 3.14159f/180.f);
    }
    if (gPlayer->cInput->right)
    {
        gPlayer->cTransform->velocity.x = 10 * std::cos(gPlayer->cTransform->angle * 3.14159f/180.f);
    }
    if (gPlayer->cInput->shoot)
    {
        spawnBullet(gPlayer->cTransform->position);
    }
    /*if (gEntityManager.getEntities("bullet").size() > 0)
    {
        gPlayer->cTransform->angle = gEntityManager.getEntities("bullet").back()->cTransform->angle;

    }*/
    Vector2D mousePosition(sf::Mouse::getPosition(gRoot).x, sf::Mouse::getPosition(gRoot).y);
    float angle = atan2(mousePosition.y - gPlayer->cTransform->position.y, mousePosition.x - gPlayer->cTransform->position.x);
    gPlayer->cTransform->angle = angle * 180.f/3.14159f;

    gPlayer->cTransform->position.x += gPlayer->cTransform->velocity.x;
    gPlayer->cTransform->position.y += gPlayer->cTransform->velocity.y;
    for (auto e : gEntityManager.getEntities("bullet"))
    {
        e->cTransform->position.x += 50 * e->cTransform->velocity.x;
        e->cTransform->position.y += 50 * e->cTransform->velocity.y;
    }
    for (auto e : gEntityManager.getEntities("enemy"))
    {
        e->cTransform->position.x += e->cTransform->velocity.x;
        e->cTransform->position.y += e->cTransform->velocity.y;
    }
}

void Game::sCollision()
{
    for (auto b : gEntityManager.getEntities("bullet"))
    {
        if (b->cTransform->position.x > 1280 || b->cTransform->position.x < 0 || b->cTransform->position.y > 720 || b->cTransform->position.y < 0)
        {
            gEntityManager.killEntity(b);
        }
    }
    for (auto e : gEntityManager.getEntities("enemy"))
    {
        if (e->cTransform->position.x > 1280 || e->cTransform->position.x < 0 || e->cTransform->position.y > 720 || e->cTransform->position.y < 0)
        {
            gScore++;
            e->cSprite->sprite.setTexture(gExplosionTexture);
            sleep(0.5);
            gEntityManager.killEntity(e);
        }

        if (gPlayer->cSprite->sprite.getGlobalBounds().intersects(e->cSprite->sprite.getGlobalBounds()) && e->getTag() == "enemy")
        {
            gScore++;
            e->cSprite->sprite.setTexture(gExplosionTexture);
            sleep(0.5);
            gEntityManager.killEntity(e);
            sleep(0.5);
            gPlayer->cLifespan->remaining--;
            if (gPlayer->cLifespan->remaining == 0)
            {
                gRunning = false;
            }
        }

        for (auto b : gEntityManager.getEntities("bullet"))
        {
            if (b->cTransform->position.x > e->cTransform->position.x && b->cTransform->position.x < e->cTransform->position.x + e->cSprite->size.x && b->cTransform->position.y > e->cTransform->position.y && b->cTransform->position.y < e->cTransform->position.y + e->cSprite->size.y)
            {
                gEntityManager.killEntity(b);
                e->cSprite->sprite.setTexture(gExplosionTexture);
                sleep(0.5);
                gEntityManager.killEntity(e);
            }
        }

    }

}

void Game::sDataDisplay()
{
    gScoreData.setString("Time survived: " + std::to_string(gCurrentFrame/60));
    gLifeData.setString("Lives Left: " + std::to_string(gPlayer->cLifespan->remaining));
}