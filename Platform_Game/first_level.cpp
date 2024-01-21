#include <list>
#include "first_level.h"
#include "pedestrian.h"
#include "ammo.h"


void FirstLevel::spawnGameObjects(float dt)
{
	spawnCharacters<Pedestrian>(dt, 3000);

	Level::spawnGameObjects(dt);
}

void FirstLevel::update(float dt)
{
	spawnGameObjects(dt);
	Level::update(dt);
}

void FirstLevel::init()
{
	m_brush_house.outline_opacity = 0.0f;
	m_brush_house.texture = m_state->getAssetPath() + "house.png";
	m_brush_train.outline_opacity = 0.0f;
	m_brush_train.texture = m_state->getAssetPath() + "train.png";

	Level::init();
}

void FirstLevel::draw()
{
	drawBackground();
	float width = m_state->getCanvasWidth();
	float house_width = 357.0f;
	float house_height = 303.0f;
	graphics::drawRect(width / 2.0f - house_width / 2.0f + m_state->m_background_global_offset_x, m_state->getFloorLevel() - house_height / 2.0f, house_width, house_height, m_brush_house);

	float train_width = 1667.0f;
	float train_height = 150.0f;
	graphics::drawRect(getLevelFinishPosX() + 0.66f * train_width + m_state->m_background_global_offset_x, m_state->getFloorLevel() - train_height / 2.0f, train_width, train_height, m_brush_train);

	Level::draw();
}

FirstLevel::~FirstLevel()
{
}
