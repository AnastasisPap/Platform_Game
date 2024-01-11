#include "sgg\graphics.h"
#include "sgg\scancodes.h"
#include "game_state.h"
#include <string>
#include <cmath>
#include <iostream>

/* --------------- PROJECT OUTLINE ---------------
Project deadline: 11/2/2024 at 23:00

Help / Test:
 - Pedestrians are annoyed when you approach them and they push you away

Levels:
 - Level 1: from house to metro (31/1/2024)
 - Level 2: from metro to bus stop (31/1/2024)
 - Level 3: from bus stop to University (31/1/2024)

Characters:
 - Pedestrians: the aim of the pedestrians is to make the main characterbe late, e.g. by walking slow (15/1/2024)
     - Shoots them (if they do this more than once, police is called for example)
     - Finds buildings/stairs/etc. and jumps above them
 - Policemen: chaces the player if they shoot too many times, they can't chace if they get in bus/uni (31/1/2024)
 - Criminals: they try to shoot the main character to steal their stuff, they appear from the bus stop to the uni (31/1/2024)
 - Dapites: when the main character arrives at the university they try to talk to it and make it late (31/1/2024)
 - Ticket validators: with a small chance in the bus there are ticket validators and if that's the case they lose (and they don't have a ticket)
   - Some time in the game the player can collect a ticket (which will take some time to do so), if they get the ticket
    and there is a validator they don't lose (31/1/2024)

Objects:
 - Stairs: the main character uses them to get on a higher level and jump over pedestrians (16/1/2024)
 - Higher level roads: the main character can go there to jump over pedestrians (16/1/2024)

OOP Structure:
 - The characters know information about each other
   - The pedestrian needs to know if they get shot
   - The policeman needs to know the position of the player, if they are in the bus/uni, how many times the player has killed
   - The criminals need to know position of the player and whether they are being shot or not
   - The dapites need to know the position of the player and whether they are being shot or not
   - Ticket validators need to know if the player has a ticket or not

TODO(anastasis):
 - After all the functionality is finished, refactor code with inheritance and polymorphism
*/

void init() { GameState::getInstance()->init(); }

void draw() { GameState::getInstance()->draw(); }

void update(float dt) { GameState::getInstance()->update(dt); }

int main()
{
    graphics::createWindow(1200, 700, "I am late Stage 1");

    init();

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::startMessageLoop();
    return 0;
}
