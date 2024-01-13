#include <cmath>
#include "stairs.h"
#include "game_state.h"

void Stairs::update(float dt)
{
	float delta_time = dt / 50.0f;

	Character* character = (Character*)m_state->getPlayer();
	bool is_character_ascending = isAscending(character);
	if (is_character_ascending)	character->m_pos_y -= delta_time * m_ascending_speed;
	GameObject::update(dt);
}

void Stairs::init() {
	m_brush.fill_opacity = 1.0f;
	m_brush.outline_opacity = 1.0f;
	m_brush.outline_color[0] = 0.0f;
	m_brush.outline_color[1] = 0.0f;
	m_brush.outline_color[2] = 0.0f;
	m_brush.fill_color[0] = 210/255.0f;
	m_brush.fill_color[1] = 105/255.0f;
	m_brush.fill_color[2] = 30/255.0f;

	m_brush_debugging.fill_opacity = 0.5f;
	m_brush_debugging.fill_color[0] = 1.0f;
	m_brush_debugging.fill_color[1] = 0.0f;
	m_brush_debugging.fill_color[2] = 0.0f;
	m_pos_y = m_state->getFloorLevel() - m_height / 2.0f - 100;

	m_num_of_gaps = std::floor(m_height / (m_horizontal_stick_height + m_stick_gap));
	bool extra_stick = (m_horizontal_stick_height + m_stick_gap) * m_num_of_gaps + m_horizontal_stick_height <= m_height;
	m_num_of_gaps -= !extra_stick;
	
	m_horizontal_stick_width = m_width - 2 * m_vertical_stick_width;
	m_vertical_stick_height = (m_num_of_gaps + 1) * m_horizontal_stick_height + m_num_of_gaps * m_stick_gap + 2 * m_vertical_stick_extra_height;
	m_width = m_horizontal_stick_width + 2 * m_vertical_stick_width;
	m_height = m_vertical_stick_height;
}

void Stairs::draw()
{
	/* Draw vertical sticks */
	graphics::drawRect(m_pos_x + m_state->m_background_global_offset_x - (m_vertical_stick_width / 2.0f + m_horizontal_stick_width / 2.0f), m_pos_y, m_vertical_stick_width, m_vertical_stick_height, m_brush);
	graphics::drawRect(m_pos_x + m_state->m_background_global_offset_x + (m_vertical_stick_width / 2.0f + m_horizontal_stick_width / 2.0f), m_pos_y, m_vertical_stick_width, m_vertical_stick_height, m_brush);

	/* Draw horizontal sticks */
	for (int i = 1; i <= m_num_of_gaps/2; i++)
	{
		graphics::drawRect(m_pos_x + m_state->m_background_global_offset_x, m_pos_y - i * (m_horizontal_stick_height + m_stick_gap), m_horizontal_stick_width, m_horizontal_stick_height, m_brush);
		graphics::drawRect(m_pos_x + m_state->m_background_global_offset_x, m_pos_y + i * (m_horizontal_stick_height + m_stick_gap), m_horizontal_stick_width, m_horizontal_stick_height, m_brush);
	}
	graphics::drawRect(m_pos_x + m_state->m_background_global_offset_x, m_pos_y, m_horizontal_stick_width, m_horizontal_stick_height, m_brush);

	if (m_state->m_debugging)
		graphics::drawRect(m_pos_x + m_state->m_background_global_offset_x, m_pos_y, m_width, m_height, m_brush_debugging);
}

bool Stairs::isAscending(Character* character)
{
	float p_pos_x = character->m_pos_x + m_state->getCanvasWidth() / 2.0f;
	float p_pos_y = character->m_pos_y;
	float p_width = character->m_width;
	float p_height = character->m_height;

	return graphics::getKeyState(graphics::SCANCODE_UP) &&
		std::abs(p_pos_x - m_pos_x) <= (m_width / 2.0f + p_width / 2.0f) &&
		std::abs(p_pos_y - m_pos_y) <= (m_height / 2.0f + p_height / 2.0f);
}
