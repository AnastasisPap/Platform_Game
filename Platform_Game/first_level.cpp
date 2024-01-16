#include <list>
#include "first_level.h"
#include "pedestrian.h"
#include "ammo.h"
#include "config.h"

float FirstLevel::sampleStairsPosX()
{
	float lb = -1 * m_state->m_background_global_offset_x + m_state->getCanvasWidth() / 2.0f;
	float up = -1 * m_state->m_background_global_offset_x + 1.5f * m_state->getCanvasWidth();
	float pos_x;
	int num_of_samples = 0;
	bool found_pos_x = false;

	while (!found_pos_x || num_of_samples > 15)
	{
		pos_x = sample_uniform(lb, up);
		found_pos_x = true;
		for (Stairs* stairs : m_stairs)
			if (std::abs(pos_x - stairs->m_pos_x) <= (stairs->getMaxWidth() / 2.0f + stairs->m_width / 2.0f))
				found_pos_x = false;
		++num_of_samples;
	}

	return pos_x;
}

void FirstLevel::spawnGameObjects(float dt)
{
	int time = (int)graphics::getGlobalTime();
	if (time % 1500 <= dt && m_pedestrians_left > 0)
	{
		if (sample_uniform() <= m_pedestrian_spawn_probability)
		{
			--m_pedestrians_left;
			Pedestrian* pedestrian = new Pedestrian("pedestrian_" + std::to_string(m_characters.size()));
			pedestrian->init();
			m_characters.push_back(pedestrian);
		}
	}

	if (time % 2000 <= dt)
	{
		if (sample_uniform() <= m_stairs_spawn_probability)
		{
			float pos_x = sampleStairsPosX();
			float pos_y = m_state->getFloorLevel() - 100;
			Stairs* stairs = new Stairs(pos_x, pos_y);
			stairs->init();
			m_stairs.push_back(stairs);

			if (!m_ticket)
				m_ticket = new Box(pos_x, pos_y - stairs->m_height - 8.0f, 24.0f, 17.0f);
		}
	}
}

void FirstLevel::update(float dt)
{
	bool is_player_ascending = false;
	for (auto stairs : m_stairs)
	{
		if (stairs)
		{
			stairs->update(dt);
			is_player_ascending = is_player_ascending || stairs->isAscending(m_state->getPlayer());
		}
	}
	m_state->getPlayer()->toggleAscending(is_player_ascending);

	spawnGameObjects(dt);
	checkCollisions();
	Level::update(dt);
}

void FirstLevel::init()
{
	m_brush_house.outline_opacity = 0.0f;
	m_brush_house.texture = m_state->getAssetPath() + "house.png";
	m_brush_train.outline_opacity = 0.0f;
	m_brush_train.texture = m_state->getAssetPath() + "train.png";

	Level::init();
}

void FirstLevel::draw()
{
	drawBackground();
	float width = m_state->getCanvasWidth();
	float house_width = 357.0f;
	float house_height = 303.0f;
	graphics::drawRect(width / 2.0f - house_width / 2.0f + m_state->m_background_global_offset_x, m_state->getFloorLevel() - house_height / 2.0f, house_width, house_height, m_brush_house);

	float train_width = 1667.0f;
	float train_height = 150.0f;
	graphics::drawRect(getLevelFinishPosX() + 0.66f * train_width + m_state->m_background_global_offset_x, m_state->getFloorLevel() - train_height / 2.0f, train_width, train_height, m_brush_train);

	for (auto stairs : m_stairs)
		if (stairs) stairs->draw();
	Level::draw();
}

void FirstLevel::checkCollisions()
{
	for (Character* character : m_characters)
	{
		if (hasCollidedWithPlayer(character))
			m_state->getPlayer()->pushPlayer(character->getCharacterMass());
	}
	Level::checkCollisions();
}

FirstLevel::~FirstLevel()
{
	for (auto stairs : m_stairs)
		if (stairs)
		{
			delete stairs;
			stairs = nullptr;
		}

	for (auto p_character : m_characters)
		if (p_character)
		{
			delete p_character;
			p_character = nullptr;
		}
}
