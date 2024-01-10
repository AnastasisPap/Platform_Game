#pragma once
#include <sgg/graphics.h>
#include "game_state.h"
#include "game_object.h"
#include "box.h"

class Player : public GameObject, public Box
{
	graphics::Brush m_brush_player;
	graphics::Brush m_brush_player_debugging;
	int m_player_width = 50;
	int m_player_height = 50;

	const float m_gravity = 10.0f;
	const float m_accel_vertical = -3.0f;

	void movePlayer(float dt);
public:
	float m_vy = 0.0f;
	Player(std::string name) : GameObject(name) {}

	void update(float dt) override;
	void init() override;
	void draw() override;
	int getPlayerWidth() { return m_player_width; }
	int getPlayerHeight() { return m_player_height; }
	bool isPlayerGrounded() { return (m_pos_y >= m_state->getFloorLevel() - m_player_height / 2.0f); }
};
