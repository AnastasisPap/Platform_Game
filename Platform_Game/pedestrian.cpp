#include <algorithm>
#include <cmath>
#include "pedestrian.h"

void Pedestrian::moveCharacter(float dt)
{
	float delta_time = dt / 10.0f;
	m_pos_x -= m_speed_horizontal * delta_time;
}

void Pedestrian::update(float dt) { Character::update(dt); }

void Pedestrian::init()
{
	float width = m_state->getCanvasWidth();
	float min_pos_x = -1 * m_state->m_background_global_offset_x / width + 1;
	m_pos_x = sample_uniform(min_pos_x * width, (min_pos_x + 2) * width);

	int pedestrian_num = sample_int_uniform(1, 3);
	m_asset_full_path = m_state->getAssetPath() + "pedestrian_" + std::to_string(pedestrian_num) + ".png";
	m_height_to_width = m_height_to_width_ratios[pedestrian_num - 1];
	Character::init();
}

void Pedestrian::draw() { Character::draw(); }
