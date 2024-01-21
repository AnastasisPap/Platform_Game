#pragma once
#include <list>
#include "character.h"
#include "config.h"
#include "ammo.h"

class Criminal : public Character
{
	const int m_shooting_time_frequency = 3;
	void moveCharacter(float dt) override;
public:
	Criminal(std::string name) :
		Character("criminal_" + name, sample_uniform(1.0f, 3.0f), sample_int_uniform(1, 20), sample_uniform(30.0f, 45.0f)) {}

	void checkCriminalShot();
	void update(float dt) override;
	void init() override;
	void draw() override;
};
