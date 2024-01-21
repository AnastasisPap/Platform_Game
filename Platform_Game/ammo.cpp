#include <iostream>
#include "game_state.h"
#include "ammo.h"
#include "character.h"

void Ammo::update(float dt)
{
	float delta_time = dt / 5.0f;
	m_pos_x += m_direction * delta_time * m_ammo_velocity;

	GameObject::update(dt);
}

bool Ammo::checkShotCharacter(Character* p_character)
{
	return std::abs(m_pos_x - m_state->getCanvasWidth() / 2.0f - m_state->m_background_global_offset_x - p_character->m_pos_x) <= p_character->m_width / 2.0f &&
		std::abs(m_pos_y - p_character->m_pos_y) <= p_character->m_height / 2.0f;
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
