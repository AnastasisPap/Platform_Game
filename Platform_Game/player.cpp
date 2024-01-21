#include <algorithm>
#include <cmath>
#include "player.h"
#include "config.h"

void Player::moveCharacter(float dt)
{
	float delta_time = dt / 5.0f;
	if (m_is_pushed)
	{
		 // update speed. If we are starting to slow down then we subtract this from the current speed. If we are still accelerating we add this
		float speed_update = m_accel_horizontal * delta_time / 20.0f;
		if (m_vx >= m_max_speed * delta_time / 1.5f || !m_is_accelerating) {
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
		m_pos_x = std::min(std::max(m_pos_x, 0.0f), m_state->getLevelMaxWidth());
	}
	if (!m_is_ascending)
	{
		if (graphics::getKeyState(graphics::SCANCODE_UP) && isCharacterGrounded())
			m_vy = m_accel_vertical;

		m_pos_y += delta_time * m_vy;
		m_vy += m_gravity * delta_time;
	}
}

void Player::shootGun(float direction)
{
	if (m_shots_left <= 0) return;

	if (sample_uniform() <= (10 - m_shots_left)/20.0f) m_state->spawnCop();
	--m_shots_left;
	Character::shootGun(direction);
}

void Player::update(float dt)
{
	Character::update(dt);

	m_state->m_background_global_offset_x = -m_pos_x;

	graphics::MouseState mouse;
	graphics::getMouseState(mouse);
	if (mouse.button_left_pressed) shootGun();
}

void Player::init()
{
	m_asset_full_path = m_state->getAssetPath() + "character.png";
	m_height_to_width = 1.8f;
	Character::init();
}

void Player::draw()
{
	Character::draw();
}