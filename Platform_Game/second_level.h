#pragma once
#include "level.h"

class SecondLevel : public Level
{
	graphics::Brush m_brush_train;
	graphics::Brush m_brush_bus;

	void spawnGameObjects(float dt) override;
public:
	void update(float dt);
	void init();
	void draw();
	SecondLevel(const std::string& name, const int& max_seconds, const float& max_num_of_widths) :
		Level("second_level_" + name, max_seconds, max_num_of_widths) { m_current_level = 2; }
	~SecondLevel();
};
