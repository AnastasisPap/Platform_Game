#include <iostream>
#include <algorithm>
#include <cmath>
#include <sgg/graphics.h>
#include "character.h"
#include "config.h"

void Character::moveCharacter(float dt) {}

void Character::update(float dt)
{
	moveCharacter(dt);
	GameObject::update(dt);
}

void Character::init()
{
	m_pos_y = m_state->getFloorLevel() - getCharacterHeight() / 2.0f;
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
	m_pos_y = std::min(m_state->getFloorLevel() - m_character_height / 2.0f, m_pos_y);
	graphics::drawRect(getCharacterPosX(), getCharacterPosY(), m_character_width, m_character_height, m_brush_character);

	if (m_state->m_debugging)
		graphics::drawRect(getCharacterPosX(), getCharacterPosY(), m_character_width, m_character_height, m_brush_character_debugging);
}
