#pragma once
#include <sgg/graphics.h>
#include <list>
#include "game_object.h"
#include "box.h"

class Ammo : public GameObject, public Box
{
	graphics::Brush m_brush_ammo;
	const int m_ammo_height = 4;
	const int m_ammo_width = 10;
	const float m_ammo_velocity = 5.0f;
	const float m_max_distance = 0.75 * m_state->getCanvasWidth();
public:
	void update(float dt) override;
	void init() override;
	void draw() override;
	float getMaxDistance() { return m_max_distance; }
	Ammo(float pos_x, float pos_y) { m_pos_x = pos_x; m_pos_y = pos_y; }
};
