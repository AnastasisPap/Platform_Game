#pragma once
#include <sgg/graphics.h>
#include "game_state.h"
#include "character.h"
#include "config.h"

class Cop : public Character
{
	float getCharacterPosX() override { return m_pos_x + m_state->m_background_global_offset_x + m_state->getCanvasWidth() / 2.0f; }
	void moveCharacter(float dt) override;
	float getCopMove();

	const float m_chasing_speed = 3.5f;
	const float m_walking_speed = 1.5f;
public:
	Cop(std::string name) : Character(name, 0.0f, sample_int_uniform(1, 20), 45.0f) {}

	void update(float dt);
	void init();
	void draw();
};