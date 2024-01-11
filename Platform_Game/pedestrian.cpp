#include <iostream>
#include <algorithm>
#include <cmath>
#include "pedestrian.h"
#include <sgg/graphics.h>

void Pedestrian::movePedestrian(float dt)
{
	float delta_time = dt / 10.0f;

	m_pos_x -= m_speed_horizontal * delta_time;
}

void Pedestrian::update(float dt)
{
	movePedestrian(dt);
	GameObject::update(dt);
}

void Pedestrian::init()
{
	int width = m_state->getCanvasWidth();
	srand(time(NULL));
	int min_pos_x = -1 * m_state->m_background_global_offset_x / width + 1;
	m_pos_x = rand() % (min_pos_x + 2) * width + min_pos_x * width;
	m_pos_y = m_state->getFloorLevel() - m_pedestrian_height / 2.0f;

	m_brush_pedestrian.fill_opacity = 1.0f;
	m_brush_pedestrian.outline_opacity = 0.0f;
	int pedestrian_num = rand() % 3 + 1;
	m_brush_pedestrian.texture = m_state->getAssetPath() + "pedestrian_" + std::to_string(pedestrian_num) + ".png";

	m_brush_pedestrian_debugging.fill_opacity = 0.5f;
	m_brush_pedestrian_debugging.fill_color[0] = 1.0f;
	m_brush_pedestrian_debugging.fill_color[1] = 0.0f;
	m_brush_pedestrian_debugging.fill_color[2] = 0.0f;
}

void Pedestrian::draw()
{
	graphics::drawRect(m_pos_x + m_state->m_background_global_offset_x + m_state->getCanvasWidth() / 2.0f, m_pos_y, m_pedestrian_width, m_pedestrian_height, m_brush_pedestrian);

	if (m_state->m_debugging)
		graphics::drawRect(m_pos_x + m_state->m_background_global_offset_x + m_state->getCanvasWidth() / 2.0f, m_pos_y, m_pedestrian_width, m_pedestrian_height, m_brush_pedestrian_debugging);
}
