#pragma once
#include <vector>
#include <sgg/graphics.h>
#include "level.h"
#include "stairs.h"
#include "box.h"

class FirstLevel : public Level
{
	graphics::Brush m_brush_house;
	graphics::Brush m_brush_train;

	/* Objects */
	std::vector<Stairs*> m_stairs;
	void spawnGameObjects(float dt);

	/* Characters */
	int m_pedestrians_left = 20;
	void checkShot();

	/* Probabilities */
	const float m_pedestrian_spawn_probability = 0.2f;
	const float m_stairs_spawn_probability = 0.1f;
	float sampleStairsPosX();
protected:
	void checkCollisions();
public:
	void update(float dt);
	void init();
	void draw();
	FirstLevel(const std::string& name, const int& max_seconds, const float& max_num_of_widths) : Level(name, max_seconds, max_num_of_widths) {}
	~FirstLevel();
};
