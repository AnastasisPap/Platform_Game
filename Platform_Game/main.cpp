#include <string>
#include <cmath>
#include <iostream>
#include "sgg\graphics.h"
#include "sgg\scancodes.h"
#include "game_state.h"
#include "player.h"

/* --------------- PROJECT OUTLINE ---------------
Project deadline: 11/2/2024 at 23:00

TODO:
 - Better spawning
 - Spawn cop not too far behind
 - Add intro text at the start of each level
 - Replace random spawning with pre-spawn for a predefined amount of items in random positions
 - After all the functionality is finished, refactor code with inheritance and polymorphism

Levels:
 - Level 2: from metro to bus stop (31/1/2024)
     - Have a probability that a validator is present and if the player doesn't have the ticket they lose
 - Level 3: from bus stop to University (31/1/2024)
     - Have a probability that a validator is present and if the player doesn't have the ticket they lose

Characters:
 - Policemen: chaces the player if they shoot too many times, they can't chace if they get in bus/uni (31/1/2024)
     - Cops despawn at the end of each level
 - Criminals: they try to shoot the main character to steal their stuff, they appear from the bus stop to the uni (31/1/2024)
 - Dapites: when the main character arrives at the university they try to talk to it and make it late (31/1/2024)

OOP Structure:
 - The characters know information about each other
   - The pedestrian needs to know if they get shot
   - The policeman needs to know the position of the player, if they are in the bus/uni, how many times the player has killed
   - The criminals need to know position of the player and whether they are being shot or not
   - The dapites need to know the position of the player and whether they are being shot or not
   - Ticket validators need to know if the player has a ticket or not
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
    graphics::createWindow(1200, 700, "I am late Stage 1");

    init();

    graphics::setFont("assets\\roboto.ttf");
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::startMessageLoop();
    return 0;
}
