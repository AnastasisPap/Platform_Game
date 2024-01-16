#pragma once
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "game_object.h"
#include "player.h"
#include "character.h"

class Level : public GameObject
{
	/* Brushes */
	graphics::Brush m_brush_background;
	graphics::Brush m_brush_debugging;
	graphics::Brush m_brush_ticket;
	graphics::Brush m_brush_star;
	graphics::Brush m_brush_text;

	void drawTicket();
	const int m_max_seconds;
	void checkShot();
protected:
	int m_center_x = 0;
	int m_num_of_tiles = 2;
	const float m_max_num_of_widths;
	void checkTicketRetrieval();
	bool hasCollidedWithPlayer(Character* character);
	void checkCollisions();
	void drawBackground();
	Box* m_ticket = nullptr;
	std::list<Character*> m_characters;
public:
	void update(float dt) override;
	void init() override;
	void draw() override;
	float getLevelFinishPosX() { return (m_max_num_of_widths - 0.5f) * m_state->getCanvasWidth(); }
	Level(const std::string& name, const int& max_seconds, const float& max_num_of_widths) :
		GameObject(name), m_max_seconds(max_seconds), m_max_num_of_widths(max_num_of_widths) {};
	~Level();
};