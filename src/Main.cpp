/*
** File description:
** main indie
*/

#include "Engine.hpp"

int main(void)
{
    const int screenWidth = 1900;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Bomberman");
    Engine e;

    e.runGame();
    return 0;
}