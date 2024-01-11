#pragma once
#include <sgg/graphics.h>
#include "game_state.h"
#include "game_object.h"
#include "box.h"

class Character : public GameObject, public Box
{
	graphics::Brush m_brush_character;
	graphics::Brush m_brush_character_debugging;
	float m_character_width = 50.0f;
	float m_character_height = 50.0f;
protected:
	virtual void moveCharacter(float dt);
	float m_accel_horizontal = 0.5f;
	const float m_gravity = 1 / 10.0f;
	const float m_accel_vertical = -3.1f;
	const float m_speed_horizontal;
	const float m_max_speed = 7.0f;
	const int m_mass;
	std::string m_asset_full_path = "";
public:
	float m_vy = 0.0f;
	float m_vx = 0.0f;
	Character(std::string name, float speed, int mass) :
		GameObject(name), m_speed_horizontal(speed), m_mass(mass) {}

	void update(float dt) override;
	void init() override;
	void draw() override;
	float getCharacterWidth() { return m_character_width; }
	float getCharacterHeight() { return m_character_height; }
	int getCharacterMass() { return m_mass; }
	bool isCharacterGrounded() { return (m_pos_y >= m_state->getFloorLevel() - m_character_height / 2.0f); }
	bool isOut() { return m_pos_x <= -m_state->getCanvasWidth() / 2.0f; }

	virtual float getCharacterPosX() { return m_pos_x; }
	virtual float getCharacterPosY() { return m_pos_y; }
};
