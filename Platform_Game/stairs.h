#pragma once
#include <vector>
#include <sgg/graphics.h>
#include "game_object.h"
#include "character.h"
#include "config.h"
#include "box.h"

class Stairs : public GameObject, public Box
{
	graphics::Brush m_brush;
	graphics::Brush m_brush_debugging;

	const float m_horizontal_stick_height = 3.0f;
	const float m_vertical_stick_width = 5.0f;
	const float m_stick_gap = 15.0f;
	const float m_vertical_stick_extra_height = 10.0f;
	const float m_max_width = 55.0f;

	float m_horizontal_stick_width = 0.0f;
	float m_vertical_stick_height = 0.0f;
	int m_num_of_gaps = 0;
	const float m_ascending_speed;
public:
	Stairs(float pos_x, float pos_y) : GameObject("Stairs"), m_ascending_speed(sample_uniform(1.0f, 5.0f))
	{
		m_pos_x = pos_x;
		m_pos_y = pos_y;
		m_width = sample_uniform(15.0f, m_max_width);
		m_height = sample_uniform(40.0f, 100.0f);
	}
	~Stairs() {}
	void draw() override;
	void init() override;
	void update(float dt) override;
	bool isAscending(Character* character);
	int getMaxWidth() { return m_max_width; }
};
