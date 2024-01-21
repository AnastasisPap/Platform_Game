#pragma once
#include "config.h"
#include "character.h"

class Dapites : public Character
{
	void moveCharacter(float dt) override;
public:
	Dapites(std::string name) :
		Character("dapites_" + name, 4.0f, 4, 18.0f) {}

	void update(float dt) override;
	void init() override;
	void draw() override;
};
