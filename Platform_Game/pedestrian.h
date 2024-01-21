#pragma once
#include "character.h"
#include "config.h"

class Pedestrian: public Character
{
	float m_height_to_width_ratios[3] = {1.2f, 1.4f, 1.44f};
	void moveCharacter(float dt) override;
public:
	Pedestrian(std::string name) :
		Character("pedestrian_" + name, sample_uniform(1.0f, 3.0f), sample_int_uniform(1, 20), sample_uniform(30.0f, 45.0f)) {}

	void update(float dt) override;
	void init() override;
	void draw() override;
};
