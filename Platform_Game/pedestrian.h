#pragma once
#include <sgg/graphics.h>
#include "game_state.h"
#include "character.h"
#include "config.h"

class Pedestrian: public Character
{
	float m_height_to_width_ratios[3] = {1.2f, 1.4f, 1.44f};
	float getCharacterPosX() override { return m_pos_x + m_state->m_background_global_offset_x + m_state->getCanvasWidth() / 2.0f; }
	void moveCharacter(float dt) override;
public:
	Pedestrian(std::string name) :
		Character(name, sample_int_uniform(1, 3), sample_int_uniform(1, 20), sample_uniform(30.0f, 45.0f)) {}

	void update(float dt);
	void init();
	void draw();
};
