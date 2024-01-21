#include <iostream>
#include <cmath>
#include "cop.h"
#include "player.h"

void Cop::moveCharacter(float dt)
{
	float delta_time = dt / 10.0f;
	m_pos_x += followCharacter(m_state->getPlayer(), m_chasing_speed) * delta_time;
}

void Cop::update(float dt) { Character::update(dt); }

void Cop::init()
{
	m_pos_x = m_state->getPlayer()->m_pos_x - 2.0f * m_state->getCanvasWidth();
	m_asset_full_path = m_state->getAssetPath() + "cop.png";
	m_height_to_width = 1.98f;
	Character::init();
}

void Cop::draw() { Character::draw(); }