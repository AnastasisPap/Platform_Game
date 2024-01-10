#include <algorithm>
#include <iostream>
#include "level.h"
#include "game_state.h"
#include "player.h"

void Level::update(float dt)
{
	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->update(dt);

	if (m_state->getPlayer()->m_pos_x >= (m_num_of_tiles - 1) * m_state->getCanvasWidth())
	{
		m_num_of_tiles++;
		m_blocks.push_back(Box((m_num_of_tiles-1) * m_state->getCanvasWidth() + m_state->getCanvasWidth() / 2.0f,
			m_state->getFloorLevel(), m_state->getCanvasWidth(), 1));
	}

	checkCollisions();
	GameObject::update(dt);
}

void Level::init()
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getAssetPath() + "landscape_1.png";

	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->init();
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->init();

	for (int i = 0; i < m_num_of_tiles; i++)
		m_blocks.push_back(Box((i + 1/2.0f) * m_state->getCanvasWidth(), m_state->getFloorLevel(),
			m_state->getCanvasWidth(), 1));
	m_block_names.push_back("floor");
	m_block_brush.outline_opacity = 0.0f;
	m_block_brush.fill_opacity = 0.0f;

	m_block_brush_debug.fill_opacity = 0.5f;
	m_block_brush_debug.fill_color[0] = 1.0f;
	m_block_brush_debug.fill_color[1] = 0.1f;
	m_block_brush_debug.fill_color[2] = 0.1f;
}

void Level::draw()
{
	drawBackground();

	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();

	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->draw();
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->draw();

	for (int i = 0; i < m_blocks.size(); i++)
		drawBlock(i);
}

void Level::drawBackground()
{
	float width = m_state->getCanvasWidth();
	float height = m_state->getCanvasHeight();

	for (int i = 0; i < m_num_of_tiles; i++)
		graphics::drawRect(i * width + width / 2.0f + m_state->m_background_global_offset_x,
			height / 2.0f, width, height, m_brush_background);
}

void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	float x = box.m_pos_x;
	float y = box.m_pos_y;

	graphics::drawRect(x, y, m_state->getCanvasWidth(), 1, m_block_brush);

	if (m_state->m_debugging) {
		graphics::drawRect(x, y, m_state->getCanvasWidth(), 1, m_block_brush_debug);
	}
}

void Level::checkCollisions()
{
	/*
	for (auto& box : m_blocks)
	{
		float offset = 0.0f;
		std::cout << m_state->getPlayer()->m_pos_y << " " << box.m_pos_y << std::endl;
		if (offset = m_state->getPlayer()->m_pos_y - box.m_pos_y > 0)
		{
			std::cout << "OK" << std::endl;
			m_state->getPlayer()->m_pos_y
		}
	}
	*/
}

Level::Level(const std::string& name)
{
}

Level::~Level()
{
	for (auto p_gob : m_static_objects)
		if (p_gob) delete p_gob;
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) delete p_gob;
}
