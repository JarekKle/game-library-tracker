#include <iostream>
#include "model/game.h"
int main()
{
    Game myGame(
        1,
        "Example Game",
        "Example Developer",
        "Example Publisher",
        10,
        5,
        20.5f,
        85,
        90,
        {"Note 1", "Note 2"},
        {ACTION},
        STEAM,
        PC,
        COMPLETED,
        BOUGHT,
        true
    );
    Game myGame2(
        1,
        "Fajna gra"
    );
    std::cout << "Game ID: " << myGame2.getId() << std::endl;
}