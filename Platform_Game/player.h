#pragma once
#include <vector>
#include <list>
#include <sgg/graphics.h>
#include "game_state.h"
#include "game_object.h"
#include "box.h"
#include "ammo.h"

class Player : public GameObject, public Box
{
	graphics::Brush m_brush_player;
	graphics::Brush m_brush_player_debugging;
	float m_player_width = 50.0f;
	float m_player_height = 50.0f;
	bool m_is_pushed = false;
	bool m_is_accelerating = true;

	const float m_gravity = 1 / 10.0f;
	const float m_accel_vertical = -3.1f;
	const float m_speed_horizontal = 1.5f;
	const float m_max_speed = 4.0f;
	float m_accel_horizontal = 0.5f;

	int m_shots_left = 10;

	void movePlayer(float dt);
	void shootGun();
	void finishPushing() {
		m_is_pushed = false;
		m_is_accelerating = true;
		m_vx = 0;
	}
	float getCurrentPosX() { return m_pos_x + m_state->m_background_global_offset_x + m_state->getCanvasWidth() / 2.0f; }

	std::list<Ammo*> m_gun;
public:
	float m_vy = 0.0f;
	float m_vx = 0.0f;
	Player(std::string name) : GameObject(name) {}

	void update(float dt) override;
	void init() override;
	void draw() override;
	void pushPlayer(int mass) {
		m_is_pushed = true;
		m_accel_horizontal = mass / 2.0f;
	}
	float getPlayerWidth() { return m_player_width; }
	float getPlayerHeight() { return m_player_height; }
	bool isPlayerGrounded() { return (m_pos_y >= m_state->getFloorLevel() - m_player_height / 2.0f); }
	std::list<Ammo*>* getGun() { return &m_gun; }
};
