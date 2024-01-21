#include "third_level.h"
#include "criminal.h"
#include "pedestrian.h"
#include "dapites.h"

void ThirdLevel::spawnGameObjects(float dt)
{
	spawnCharacters<Dapites>(dt, 1000);
	spawnCharacters<Pedestrian>(dt, 5000);
	Level::spawnGameObjects(dt);
}

void ThirdLevel::update(float dt)
{
	spawnGameObjects(dt);
	Level::update(dt);
}

void ThirdLevel::init()
{
	m_brush_bus.outline_opacity = 0.0f;
	m_brush_bus.texture = m_state->getAssetPath() + "bus.png";
	m_brush_university.outline_opacity = 0.0f;
	m_brush_university.texture = m_state->getAssetPath() + "uni.png";

	Level::init();
}

void ThirdLevel::draw()
{
	drawBackground();

	float bus_width = 423.0f;
	float bus_height = 175.0f;
	graphics::drawRect(m_state->m_background_global_offset_x + 1.2f * bus_width,
		m_state->getFloorLevel() - bus_height / 2.0f, bus_width, bus_height, m_brush_bus);

	float uni_width = 502.0f;
	float uni_height = 386.0f;
	graphics::drawRect(getLevelFinishPosX() + 1.3f * uni_width + m_state->m_background_global_offset_x,
		m_state->getFloorLevel() - uni_height / 2.0f, uni_width, uni_height, m_brush_university);

	Level::draw();
}

ThirdLevel::~ThirdLevel()
{
}
