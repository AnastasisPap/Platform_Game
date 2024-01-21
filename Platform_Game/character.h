#pragma once
#include <list>
#include <sgg/graphics.h>
#include "game_state.h"
#include "game_object.h"
#include "box.h"

class Character : public GameObject, public Box
{
	graphics::Brush m_brush_character;
	graphics::Brush m_brush_character_debugging;
protected:
	const float m_gravity = 1 / 10.0f;
	const float m_accel_vertical = -3.7f;
	const float m_max_speed = 7.0f;
	const int m_mass;

	float m_accel_horizontal = 0.5f;
	float m_height_to_width = 1.0f;
	float m_speed_horizontal;
	bool m_is_ascending = false;
	int m_shots_left;
	int m_initial_shots;

	std::string m_asset_full_path = "";
	std::list<class Ammo*> m_gun;

	virtual void shootGun(float direction = 1.0f);
	float followCharacter(Character* character, float following_speed);
	virtual void moveCharacter(float dt) {}
public:
	float m_vy = 0.0f;
	float m_vx = 0.0f;
	Character(std::string name, float speed, int mass, float width, int shots_left = 10) :
		GameObject(name), m_speed_horizontal(speed), m_mass(mass), m_shots_left(shots_left), m_initial_shots(shots_left) {
		m_width = width;
		m_height = width;
	}

	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
	void toggleAscending(bool is_ascending) { m_is_ascending = is_ascending; }
	void resetGun() { m_shots_left = m_initial_shots; }
	int getCharacterMass() { return m_mass; }
	bool isCharacterGrounded() { return (m_pos_y >= m_state->getFloorLevel() - m_height / 2.0f); }
	bool isOut() { return m_pos_x <= -m_state->getCanvasWidth() / 2.0f; }
	std::list<class Ammo*>* getGun() { return &m_gun; }

	float getCharacterPosX() { return m_pos_x + m_state->m_background_global_offset_x + m_state->getCanvasWidth() / 2.0f; }
	virtual float getCharacterPosY() { return m_pos_y; }
};
