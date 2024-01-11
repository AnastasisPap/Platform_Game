#include <iostream>
#include <algorithm>
#include <cmath>
#include <sgg/graphics.h>
#include "player.h"

void Player::movePlayer(float dt)
{
	float delta_time = dt / 5.0f;
	if (m_is_pushed)
	{
		 // update speed. If we are starting to slow down then we subtract this from the current speed. If we are still accelerating we add this
		float speed_update = m_accel_horizontal * delta_time / 20.0f;
		if (m_vx >= m_max_speed * delta_time || !m_is_accelerating) {
			m_is_accelerating = false;
			m_vx -= speed_update;
			if (m_vx <= 0) finishPushing(); // we have reached zero velocity, so the pushing has stopped
		}
		else m_vx += speed_update;

		float new_pos_x= m_pos_x - delta_time * m_vx;
		if (new_pos_x <= 0.0f) finishPushing();
		m_pos_x = std::max(0.0f, new_pos_x);
	}
	else {
		float move = 0.0f;

		if (graphics::getKeyState(graphics::SCANCODE_LEFT))
			move -= m_speed_horizontal;
		if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
			move += m_speed_horizontal;
		m_pos_x += delta_time * move;
		m_pos_x = std::max(m_pos_x, 0.0f);

		if (graphics::getKeyState(graphics::SCANCODE_UP) && isPlayerGrounded())
			m_vy = m_accel_vertical;

		m_pos_y += delta_time * m_vy;
		m_vy += m_gravity * delta_time;
	}
}

void Player::shootGun()
{
	if (m_shots_left <= 0) return;

	--m_shots_left;
	float curr_pos_y = std::min(m_state->getFloorLevel() - m_player_height / 2.0f, m_pos_y);
	Ammo* shot = new Ammo(getCurrentPosX(), curr_pos_y);
	shot->init();
	m_gun.push_back(shot);
}

void Player::update(float dt)
{
	/* HANDLE PLAYER */
	movePlayer(dt);

	m_state->m_player_global_offset_y = m_state->getCanvasHeight() / 2.0f - m_pos_y;
	m_state->m_background_global_offset_x = -m_pos_x;

	/* HANDLE GUN */
	graphics::MouseState mouse;
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed) shootGun();

	for (auto shot : m_gun)
		if (shot) shot->update(dt);

	if (m_gun.size() > 0 &&
		std::abs(getCurrentPosX() - m_gun.back()->m_pos_x) >= m_gun.back()->getMaxDistance())
	{
		delete m_gun.back();
		m_gun.pop_back();
	}
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
	graphics::drawRect(getCurrentPosX(), m_pos_y, m_player_width, m_player_height, m_brush_player);

	if (m_state->m_debugging)
		graphics::drawRect(getCurrentPosX(), m_pos_y, m_player_width, m_player_height, m_brush_player_debugging);

	for (auto shot : m_gun)
		if (shot) shot->draw();
}