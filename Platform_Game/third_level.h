#pragma once
#include "level.h"

class ThirdLevel : public Level
{
	graphics::Brush m_brush_bus;
	graphics::Brush m_brush_university;

	void spawnGameObjects(float dt) override;
public:
	void update(float dt);
	void init();
	void draw();
	ThirdLevel(const std::string& name, const int& max_seconds, const float& max_num_of_widths) :
		Level("third_level_" + name, max_seconds, max_num_of_widths) { m_current_level = 3; }
	~ThirdLevel();
};
