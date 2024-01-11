#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include "level.h"
#include "game_state.h"
#include "player.h"
#include "ammo.h"

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

	for (auto p_character : m_characters)
		if (p_character) p_character->update(dt);

	int time = graphics::getGlobalTime();
	if (time % 1000 <= dt && m_pedestrians_left > 0)
	{
		float uniform_distr_sample = (float)rand() / RAND_MAX;
		if (uniform_distr_sample <= m_pedestrian_spawn_probability) {
			--m_pedestrians_left;
			Pedestrian* pedestrian = new Pedestrian("pedestrian_" + std::to_string(m_characters.size()));
			pedestrian->init();
			m_characters.push_back(pedestrian);
		}
	}

	checkCollisions();
	GameObject::update(dt);
}

void Level::init()
{
	srand(time(NULL));
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
	checkShot();

	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();

	for (auto p_gob : m_static_objects)
		if (p_gob) p_gob->draw();
	for (auto p_gob : m_dynamic_objects)
		if (p_gob) p_gob->draw();

	std::list<Pedestrian*>::iterator it = m_characters.begin();
	while (it != m_characters.end())
	{
		Pedestrian* pedestrian = *it;
		if (pedestrian && pedestrian->isOut())
		{
			it = m_characters.erase(it);
			delete pedestrian;
		}
		else if (pedestrian)
		{
			pedestrian->draw();
			++it;
		}
		else ++it;
	}

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
	for (Pedestrian* character : m_characters)
	{
		if (std::abs(m_state->getPlayer()->m_pos_x - character->m_pos_x) <=
			std::max(m_state->getPlayer()->getPlayerWidth(), character->getPedestrianWidth()) &&
				m_state->getPlayer()->m_pos_y >= character->m_pos_y)
			m_state->getPlayer()->pushPlayer(character->getPedestrianMass());
	}
}

void Level::checkShot()
{
	std::list<Ammo*>::iterator ammo_it = (*m_state->getPlayer()->getGun()).begin();

	while (ammo_it != (*m_state->getPlayer()->getGun()).end())
	{
		Ammo* ammo = *ammo_it;
		std::list<Pedestrian*>::iterator pedestrian_it = m_characters.begin();
		bool got_shot = false;
		while (pedestrian_it != m_characters.end())
		{
			Pedestrian* pedestrian = *pedestrian_it;
			if (std::abs(ammo->m_pos_x - m_state->getCanvasWidth() / 2.0f - m_state->m_background_global_offset_x - pedestrian->m_pos_x) <= pedestrian->getPedestrianWidth() &&
				std::abs(ammo->m_pos_y - pedestrian->m_pos_y) <= pedestrian->getPedestrianHeight() / 2.0f)
			{
				got_shot = true;
				pedestrian_it = m_characters.erase(pedestrian_it);
				delete pedestrian;
			}
			else ++pedestrian_it;
		}
		if (got_shot) {
			ammo_it = (*m_state->getPlayer()->getGun()).erase(ammo_it);
			delete ammo;
		}
		else ++ammo_it;
	}
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
	for (auto p_character : m_characters)
		if (p_character) delete p_character;
}
