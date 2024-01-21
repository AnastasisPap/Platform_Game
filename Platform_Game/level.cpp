#include <algorithm>
#include <iostream>
#include "level.h"
#include "game_state.h"
#include "config.h"
#include "cop.h"

void Level::spawnGameObjects(float dt)
{
	int time = (int)graphics::getGlobalTime();
	if (time % 14000 <= dt && m_stairs.size() > 0) m_stairs.erase(m_stairs.begin());

	if (time % 7000 <= dt)
	{
		float pos_x = sampleStairsPosX();
		float pos_y = m_state->getFloorLevel() - 100;
		Stairs* stairs = new Stairs(pos_x, pos_y);
		stairs->init();
		m_stairs.push_back(stairs);

		int total_time = graphics::getGlobalTime() / 1000 - m_starting_time;
		if (!m_ticket && total_time >= m_max_seconds / 2.0f)
			m_ticket = new Box(pos_x, pos_y - stairs->m_height - 8.0f, 24.0f, 17.0f);
	}
}

float Level::sampleStairsPosX()
{
	float lb = -1 * m_state->m_background_global_offset_x + m_state->getCanvasWidth() / 2.0f;
	float up = -1 * m_state->m_background_global_offset_x + 1.5f * m_state->getCanvasWidth();
	up = std::min(up, getLevelFinishPosX() - 50.0f);
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

void Level::checkShot()
{
	std::list<Ammo*>::iterator ammo_it = (*m_state->getPlayer()->getGun()).begin();

	while (ammo_it != (*m_state->getPlayer()->getGun()).end())
	{
		Ammo* ammo = *ammo_it;
		std::list<Character*>::iterator pedestrian_it = m_characters.begin();
		bool got_shot = false;
		while (pedestrian_it != m_characters.end())
		{
			Character* pedestrian = *pedestrian_it;
			if (ammo->checkShotCharacter(pedestrian))
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

void Level::update(float dt)
{
	checkCollisions();
	int time = graphics::getGlobalTime() / 1000;
	if (m_max_seconds - time + m_starting_time <= 0) m_state->finishGame("Time run out");

	if (m_state->getPlayer())
		m_state->getPlayer()->update(dt);

	if (m_state->getCop())
		m_state->getCop()->update(dt);

	checkTicketRetrieval();

	if (m_state->getPlayer()->m_pos_x >= (m_num_of_tiles - 1) * m_state->getCanvasWidth())
		m_num_of_tiles++;

	for (auto p_character : m_characters)
		if (p_character) p_character->update(dt);

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

	GameObject::update(dt);
}

void Level::init()
{
	m_brush_background.outline_opacity = 0.0f;
	m_brush_background.texture = m_state->getAssetPath() + "landscape.png";

	m_brush_ticket.outline_opacity = 0.0f;
	m_brush_ticket.texture = m_state->getAssetPath() + "ticket.png";

	m_brush_star.outline_opacity = 0.0f;
	m_brush_star.texture = m_state->getAssetPath() + "star.png";

	m_brush_debugging.fill_opacity = 0.5f;
	m_brush_debugging.fill_color[0] = 1.0f;
	m_brush_debugging.fill_color[1] = 0.0f;
	m_brush_debugging.fill_color[2] = 0.0f;

	m_brush_text.fill_color[0] = 1.0f;
	m_brush_text.fill_color[1] = 0.0f;
	m_brush_text.fill_color[2] = 1.0f;
	m_starting_time = (int)(graphics::getGlobalTime() / 1000);
}

void Level::draw()
{
	checkShot();

	if (m_state->getPlayer()->isActive())
		m_state->getPlayer()->draw();

	if (m_state->getCop())
		m_state->getCop()->draw();

	if (m_ticket)
		drawTicket();

	if (m_state->getCop())
		graphics::drawRect(m_state->getCanvasWidth() - 50, 50.0f, 50.0f, 40.0f, m_brush_star);

	std::list<Character*>::iterator it = m_characters.begin();
	while (it != m_characters.end())
	{
		Character* character = *it;
		if (character && character->isOut())
		{
			it = m_characters.erase(it);
			delete character;
		}
		else if (character)
		{
			character->draw();
			++it;
		}
		else ++it;
	}

	for (auto stairs : m_stairs)
		if (stairs) stairs->draw();

	int time = m_max_seconds - graphics::getGlobalTime() / 1000 + m_starting_time;
	graphics::drawText(30, 30, 20.0f, "Time left (sec): " + std::to_string(time), m_brush_text);
}

void Level::drawBackground()
{
	float width = m_state->getCanvasWidth();
	float height = m_state->getCanvasHeight();

	for (int i = 0; i < m_num_of_tiles; i++)
		graphics::drawRect(i * width + width / 2.0f + m_state->m_background_global_offset_x,
			height / 2.0f, width, height, m_brush_background);
}

void Level::checkCollisions()
{
	if (m_state->getCop() && m_state->getPlayer()->hasCollidedWithCharacter(m_state->getCop()))
		m_state->finishGame("Cop caught you");

	for (Character* character : m_characters)
	{
		if (m_state->getPlayer()->hasCollidedWithCharacter(character))
			m_state->getPlayer()->pushPlayer(character->getCharacterMass());
	}
}

void Level::drawTicket()
{
	if (!m_state->getPlayer()->hasTicket())
	{
		graphics::drawRect(m_ticket->m_pos_x + m_state->m_background_global_offset_x, m_ticket->m_pos_y, m_ticket->m_width, m_ticket->m_height, m_brush_ticket);

		if (m_state->m_debugging)
			graphics::drawRect(m_ticket->m_pos_x + m_state->m_background_global_offset_x, m_ticket->m_pos_y, m_ticket->m_width, m_ticket->m_height, m_brush_debugging);
	}
}

void Level::checkTicketRetrieval()
{
	if (!m_ticket) return;

	Player* player = m_state->getPlayer();
	if (std::abs(player->m_pos_x - m_ticket->m_pos_x + m_state->getCanvasWidth() / 2.0f) <= player->m_width / 2.0f + m_ticket->m_width / 2.0f &&
		player->m_pos_y - m_ticket->m_pos_y <= player->m_height / 2.0f + m_ticket->m_height / 2.0f)
		player->updateTicket(true);
}

Level::~Level()
{
	for (auto p_character : m_characters)
		if (p_character)
		{
			delete p_character;
			p_character = nullptr;
		}

	for (auto stairs : m_stairs)
		if (stairs)
		{
			delete stairs;
			stairs = nullptr;
		}
}
