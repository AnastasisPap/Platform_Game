#pragma once
#include <sgg/graphics.h>
#include "character.h"
#include "config.h"

class Cop : public Character
{
	void moveCharacter(float dt) override;

	const float m_chasing_speed = 3.5f;
public:
	Cop(std::string name) : Character("cop_" + name, 1.5f, 50, 45.0f) {}

	void update(float dt) override;
	void init() override;
	void draw() override;
};