#pragma once
#include <vector>
#include <list>
#include <string>
#include <sgg/graphics.h>
#include "game_object.h"
#include "player.h"
#include "pedestrian.h"
#include "stairs.h"

class Level : public GameObject
{
	/* Background */
	graphics::Brush m_brush_background;
	int m_center_x = 0;
	int m_num_of_tiles = 2;
	void drawBackground();

	/* Objects */
	std::vector<Box> m_blocks;
	std::vector<std::string> m_block_names;
	const float m_block_size = 20.0f;
	graphics::Brush m_block_brush;
	graphics::Brush m_block_brush_debug;
	void drawBlock(int i);
	std::vector<Stairs*> m_stairs;

	/* Characters */
	std::list<Pedestrian*> m_characters;
	int m_pedestrians_left = 15;
	void checkShot();

	/* Level */
	void checkCollisions();

	/* Probabilities */
	const float m_pedestrian_spawn_probability = 0.25f;
	const float m_stairs_spawn_probability = 0.6f;
	void spawnGameObjects(float dt);
	float sampleStairsPosX();
public:
	void update(float dt) override;
	void init() override;
	void draw() override;
	Level(const std::string& name = "Going to the Metro");
	~Level();
};