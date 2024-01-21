#include <iostream>
#include <algorithm>
#include <cmath>
#include <sgg/graphics.h>
#include "character.h"
#include "config.h"
#include "player.h"
#include "ammo.h"

float Character::followCharacter(Character* character, float following_speed)
{
	float dir = -1 * m_state->m_background_global_offset_x + character->getCharacterPosX() - m_state->getCanvasWidth() / 2.0f - m_pos_x;

	bool is_below_character = m_pos_y - character->m_pos_y > m_height / 2.0f + character->m_height / 2.0f;

	if (is_below_character) return -m_speed_horizontal;
	if (dir > 0) return following_speed;
	if (dir < 0) return -following_speed;
	return 0.0f;
}

void Character::shootGun(float direction)
{
	float curr_pos_y = std::min(m_state->getFloorLevel() - m_height / 2.0f, m_pos_y);
	Ammo* shot = new Ammo(getCharacterPosX(), curr_pos_y, direction);
	shot->init();
	m_gun.push_back(shot);
}

void Character::update(float dt)
{
	moveCharacter(dt);
	GameObject::update(dt);

	for (auto p_shot : m_gun)
		if (p_shot) p_shot->update(dt);

	if (m_gun.size() > 0 &&
		getCharacterPosX() - m_gun.back()->m_pos_x >= m_gun.back()->getMaxDistance())
	{
		delete m_gun.back();
		m_gun.pop_back();
	}
}

void Character::init()
{
	m_pos_y = m_state->getFloorLevel() - m_height / 2.0f;
	m_height = m_width * m_height_to_width;
	m_brush_character.fill_opacity = 1.0f;
	m_brush_character.outline_opacity = 0.0f;
	m_brush_character.texture = m_asset_full_path;

	m_brush_character_debugging.fill_opacity = 0.5f;
	m_brush_character_debugging.fill_color[0] = 1.0f;
	m_brush_character_debugging.fill_color[1] = 0.0f;
	m_brush_character_debugging.fill_color[2] = 0.0f;
}

void Character::draw()
{
	m_pos_y = std::min(m_state->getFloorLevel() - m_height / 2.0f, m_pos_y);
	graphics::drawRect(getCharacterPosX(), getCharacterPosY(), m_width, m_height, m_brush_character);

	if (m_state->m_debugging)
		graphics::drawRect(getCharacterPosX(), getCharacterPosY(), m_width, m_height, m_brush_character_debugging);

	for (auto p_shot : m_gun)
		if (p_shot) p_shot->draw();
}
