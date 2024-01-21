#pragma once
#include <vector>
#include <list>
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

	bool m_has_ticket = false;

	void moveCharacter(float dt) override;
	void shootGun(float direction = 1.0f) override;
public:
	Player(std::string name, float speed) : Character("player_" + name, speed, 10, 30.0f) {}

	void update(float dt) override;
	void init() override;
	void draw() override;

	void pushPlayer(int mass) {
		m_is_pushed = true;
		m_accel_horizontal = mass / 2.0f;
	}

	bool hasCollidedWithCharacter(Character* p_character)
	{
		return std::abs(m_pos_x - p_character->m_pos_x) <=
			(m_width / 2.0f + p_character->m_width / 2.0f) &&
			(m_pos_y + m_height / 2.0f >=
				p_character->m_pos_y - m_height / 2.0f);
	};
	bool hasTicket() const { return m_has_ticket; }
	void updateTicket(bool state) { m_has_ticket = state; }
};
