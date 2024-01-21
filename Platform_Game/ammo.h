#pragma once
#include <sgg/graphics.h>
#include "game_object.h"
#include "box.h"

class Ammo : public GameObject, public Box
{
	graphics::Brush m_brush_ammo;
	float m_direction;
	const int m_ammo_height = 4;
	const int m_ammo_width = 10;
	const float m_ammo_velocity = 5.0f;
	const float m_max_distance = m_state->getCanvasWidth() / 1.5f;
public:
	void update(float dt) override;
	void init() override;
	void draw() override;
	float getMaxDistance() { return m_max_distance; }
	bool checkShotCharacter(class Character* p_character);
	Ammo(float pos_x, float pos_y, float direction = 1.0f) : m_direction(direction) { m_pos_x = pos_x; m_pos_y = pos_y; }
};
