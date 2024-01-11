#pragma once
#include <stdlib.h>
#include <time.h>
#include <sgg/graphics.h>
#include "game_state.h"
#include "game_object.h"
#include "box.h"

class Pedestrian: public GameObject, public Box
{
	graphics::Brush m_brush_pedestrian;
	graphics::Brush m_brush_pedestrian_debugging;
	float m_pedestrian_width = 50.0f;
	float m_pedestrian_height = 50.0f;
	int m_mass;

	float m_speed_horizontal = 1.5f;

	void movePedestrian(float dt);
public:
	Pedestrian(std::string name) : GameObject(name) {
		srand(time(NULL));
		m_mass = rand() % 20 + 1;
		m_speed_horizontal = rand() % 3 + 1;
	}

	void update(float dt) override;
	void init() override;
	void draw() override;
	float getPedestrianWidth() { return m_pedestrian_width; }
	float getPedestrianHeight() { return m_pedestrian_height; }
	int getPedestrianMass() { return m_mass * m_speed_horizontal; }
	bool isOut() { return m_pos_x <= -m_state->getCanvasWidth() / 2.0f; }
};
