#include <iostream>
#include "game_state.h"
#include "ammo.h"

void Ammo::update(float dt)
{
	float delta_time = dt / 10.0f;
	m_pos_x += delta_time * m_ammo_velocity;

	GameObject::update(dt);
}

void Ammo::draw()
{
	graphics::drawRect(m_pos_x, m_pos_y, m_ammo_width, m_ammo_height, m_brush_ammo);
}

void Ammo::init()
{
	m_brush_ammo.outline_opacity = 0.0f;
	m_brush_ammo.fill_color[0] = 0;
	m_brush_ammo.fill_color[1] = 0;
	m_brush_ammo.fill_color[2] = 0;
}
