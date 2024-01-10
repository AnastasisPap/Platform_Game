#include <iostream>
#include <algorithm>
#include <cmath>
#include "player.h"
#include <sgg/graphics.h>

void Player::movePlayer(float dt)
{
	float delta_time = dt / 5.0f;
	float move = 0.0f;

	if (graphics::getKeyState(graphics::SCANCODE_LEFT))
		move -= 1.0f;
	if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
		move += 1.0f;
	m_pos_x += delta_time * move;

	if (graphics::getKeyState(graphics::SCANCODE_UP) && isPlayerGrounded())
		m_vy = m_accel_vertical;
	m_pos_y += delta_time * m_vy;
	delta_time /= 300.0f;
	m_vy += m_gravity * delta_time;
}

void Player::update(float dt)
{
	movePlayer(dt);
	m_state->m_player_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;
	m_state->m_background_global_offset_x = - m_pos_x;

	GameObject::update(dt);
}

void Player::init()
{
	m_pos_x = 0;
	m_pos_y = m_state->getFloorLevel() - m_player_height / 2.0f;

	m_state->m_player_global_offset_y = 0;

	m_brush_player.fill_opacity = 1.0f;
	m_brush_player.outline_opacity = 0.0f;
	m_brush_player.texture = m_state->getAssetPath() + "character.png";

	m_brush_player_debugging.fill_opacity = 0.5f;
	m_brush_player_debugging.fill_color[0] = 1.0f;
	m_brush_player_debugging.fill_color[1] = 0.0f;
	m_brush_player_debugging.fill_color[2] = 0.0f;
}

void Player::draw()
{
	m_pos_y = std::min(m_state->getFloorLevel() - m_player_height / 2.0f, m_pos_y);
	graphics::drawRect(m_state->getCanvasWidth() / 2, m_pos_y, m_player_width, m_player_height, m_brush_player);

	if (m_state->m_debugging)
		graphics::drawRect(m_state->getCanvasWidth() / 2, m_pos_y, m_player_width / 2, m_player_height, m_brush_player_debugging);
}