#include "second_level.h"
#include "criminal.h"
#include "pedestrian.h"

void SecondLevel::spawnGameObjects(float dt)
{
	spawnCharacters<Pedestrian>(dt, 5000);
	spawnCharacters<Criminal>(dt, 7000);

	Level::spawnGameObjects(dt);
}

void SecondLevel::update(float dt)
{
	for (Character* p_character : m_characters)
	{
		Criminal* criminal = dynamic_cast<Criminal*>(p_character);
		if (criminal != nullptr)
			criminal->checkCriminalShot();
	}

	spawnGameObjects(dt);
	Level::update(dt);
}

void SecondLevel::init()
{
	m_brush_train.outline_opacity = 0.0f;
	m_brush_train.texture = m_state->getAssetPath() + "train.png";
	m_brush_bus.outline_opacity = 0.0f;
	m_brush_bus.texture = m_state->getAssetPath() + "bus.png";

	Level::init();
}

void SecondLevel::draw()
{
	drawBackground();
	float train_width = 1667.0f;
	float train_height = 150.0f;

	graphics::drawRect(m_state->m_background_global_offset_x, m_state->getFloorLevel() - train_height / 2.0f,
		train_width, train_height, m_brush_train);

	float bus_width = 423.0f;
	float bus_height = 175.0f;
	graphics::drawRect(getLevelFinishPosX() + 1.2f * bus_width + m_state->m_background_global_offset_x,
		m_state->getFloorLevel() - bus_height / 2.0f, bus_width, bus_height, m_brush_bus);

	Level::draw();
}

SecondLevel::~SecondLevel()
{
}
