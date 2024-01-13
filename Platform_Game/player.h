#pragma once
#include <vector>
#include <list>
#include <sgg/graphics.h>
#include "game_state.h"
#include "character.h"
#include "ammo.h"

class Player : public Character
{
	bool m_is_pushed = false;
	bool m_is_accelerating = true;

	void finishPushing() {
		m_is_pushed = false;
		m_is_accelerating = true;
		m_vx = 0;
	}

	/* Gun */
	std::list<Ammo*> m_gun;
	int m_shots_left = 10;
	void shootGun();
	void moveCharacter(float dt) override;
public:
	Player(std::string name, float speed) : Character(name, speed, 10, 30.0f) {}

	void update(float dt);
	void init();
	void draw();
	float getCharacterPosX() override { return m_pos_x + m_state->m_background_global_offset_x + m_state->getCanvasWidth() / 2.0f; }

	void pushPlayer(int mass) {
		m_is_pushed = true;
		m_accel_horizontal = mass / 2.0f;
	}
	std::list<Ammo*>* getGun() { return &m_gun; }
};
