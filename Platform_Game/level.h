#pragma once
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "game_object.h"
#include "player.h"
#include "character.h"
#include "stairs.h"

class Level : public GameObject
{
	graphics::Brush m_brush_background;
	graphics::Brush m_brush_debugging;
	graphics::Brush m_brush_ticket;
	graphics::Brush m_brush_star;
	graphics::Brush m_brush_text;

	void drawTicket();
	const int m_max_seconds;
	void checkShot();
protected:
	int m_current_level = 1;
	int m_center_x = 0;
	int m_num_of_tiles = 2;
	int m_starting_time = 0;

	const float m_max_num_of_widths;

	void checkTicketRetrieval();

	void checkCollisions();
	void drawBackground();
	virtual void spawnGameObjects(float dt);
	float sampleStairsPosX();

	Box* m_ticket = nullptr;
	std::list<Character*> m_characters;
	std::vector<Stairs*> m_stairs;

	template <class T>
	inline void spawnCharacters(float dt, int time_rate)
	{
		int time = (int)graphics::getGlobalTime();
		if (time % time_rate <= dt)
		{
			T* character = new T("character_" + std::to_string(m_characters.size()));
			character->init();
			m_characters.push_back(character);
		}
	}
public:
	Level(const std::string& name, const int& max_seconds, const float& max_num_of_widths) :
		GameObject(name), m_max_seconds(max_seconds), m_max_num_of_widths(max_num_of_widths) {
		m_state->stopCop();
		if (m_state->getPlayer()) m_state->getPlayer()->m_pos_x = 0.0f;
	};
	~Level();

	void update(float dt) override;
	void init() override;
	void draw() override;

	float getLevelFinishPosX() { return (m_max_num_of_widths - 0.5f) * m_state->getCanvasWidth(); }
	int getCurrentLevel() const { return m_current_level; }
	void startTimer(int starting_time) { m_starting_time = starting_time; }
};