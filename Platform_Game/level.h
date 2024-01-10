#pragma once
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "game_object.h"
#include "player.h"

class Level : public GameObject
{
	graphics::Brush m_brush_background;

	int m_center_x = 0;

	std::vector<GameObject*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;
	int m_num_of_tiles = 2;

	std::vector<Box> m_blocks;
	std::vector<std::string> m_block_names;
	const float m_block_size = 20.0f;
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;
	void drawBlock(int i);
	void checkCollisions();
	void drawBackground();

public:
	void update(float dt) override;
	void init() override;
	void draw() override;
	Level(const std::string& name = "Level 0");
	~Level();
};