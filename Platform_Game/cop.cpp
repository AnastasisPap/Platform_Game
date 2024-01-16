#include <iostream>
#include <cmath>
#include "cop.h"
#include "player.h"

float Cop::getCopMove()
{
	Player* player = m_state->getPlayer();
	float dir = -1 * m_state->m_background_global_offset_x + player->getCharacterPosX() - m_state->getCanvasWidth() / 2.0f - m_pos_x;

	bool is_below_player = m_pos_y - m_state->getPlayer()->m_pos_y > m_height / 2.0f + m_state->getPlayer()->m_height / 2.0f;

	if (is_below_player) return -m_walking_speed;
	if (dir > 0) return m_chasing_speed;
	if (dir < 0) return -m_chasing_speed;
	return 0.0f;
}

void Cop::moveCharacter(float dt)
{
	float delta_time = dt / 10.0f;
	m_pos_x = m_pos_x + getCopMove() * delta_time;
}

void Cop::update(float dt) { Character::update(dt); }

void Cop::init()
{
	m_pos_x = -m_state->getCanvasWidth() / 2.0f;
	m_asset_full_path = m_state->getAssetPath() + "cop.png";
	m_height_to_width = 1.98f;
	Character::init();
}

void Cop::draw() { Character::draw(); }