#include "dapites.h"
#include "game_state.h"
#include "player.h"

void Dapites::moveCharacter(float dt)
{
	float delta_time = dt / 10.0f;

	m_pos_x -= m_speed_horizontal * delta_time;
}

void Dapites::update(float dt) { Character::update(dt); }

void Dapites::init()
{
	float width = m_state->getCanvasWidth();
	float min_pos_x = -1 * m_state->m_background_global_offset_x / width + 1;
	m_pos_x = sample_uniform(min_pos_x * width, (min_pos_x + 2) * width);

	m_asset_full_path = m_state->getAssetPath() + "dapitis.png";
	m_height_to_width = 2.9f;
	Character::init();
}

void Dapites::draw() { Character::draw(); }
