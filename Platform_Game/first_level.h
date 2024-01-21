#pragma once
#include <vector>
#include "level.h"
#include "stairs.h"

class FirstLevel : public Level
{
	graphics::Brush m_brush_house;
	graphics::Brush m_brush_train;

	void spawnGameObjects(float dt) override;
public:
	void update(float dt);
	void init();
	void draw();
	FirstLevel(const std::string& name, const int& max_seconds, const float& max_num_of_widths) :
		Level("first_level_" + name, max_seconds, max_num_of_widths) {}
	~FirstLevel();
};
