#include <string>
#include <cmath>
#include <iostream>
#include "sgg\graphics.h"
#include "sgg\scancodes.h"
#include "game_state.h"
#include "player.h"

/*
Project deadline: 11/2/2024 at 23:00

TODO:
 - Add intro text at the start of each level
 - Comments
*/

void init() { if (GameState::getInstance()) GameState::getInstance()->init(); }

void draw() { if (GameState::getInstance()) GameState::getInstance()->draw(); }

void update(float dt)
{
    if (GameState::getInstance())
		GameState::getInstance()->update(dt);
}

int main()
{
    graphics::createWindow(1200, 700, "I am late");

    init();

    graphics::setFont("assets\\roboto.ttf");
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::startMessageLoop();
    return 0;
}
