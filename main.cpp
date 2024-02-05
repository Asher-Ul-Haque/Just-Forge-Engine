#include <iostream>
#include "Backend/Game.h"

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
}
