#include <iostream>
#include "Backend/Game.h"
#include "Backend/Vector2D.h"
#include "Backend/EntityManager.h"

int main() {
    try
    {
        Game g;
        g.run();
        return 0;
    }
    catch (std::exception e){
        return -1;
    }

    /*Vector2D v1(5, 100);
    std::cout << v1.x << ", " << v1.y << std::endl;
    Vector2D v2(5, 101);
    std::cout << v2.x << ", " << v2.y << std::endl;
    std::cout << v1.getAngle(v2) << std::endl;*/

    /*EntityManager gEntityManager;
    auto bullet = gEntityManager.createEntity("bullet");
    bullet->cTransform = std::make_shared<CTransform>(Vector2D(100, 100), Vector2D(50.f, 50.f), 0);
    Vector2D mySize(100, 100);
    //ADD A BULLET IMAGE
    bullet->cSprite = std::make_shared<CSprite>(R"(../Assets/Images/Bullet.png)", mySize);
    //ASK THIS DOUBT FROM T.A.

    gEntityManager.update();
    gEntityManager.getEntities();*/
}
