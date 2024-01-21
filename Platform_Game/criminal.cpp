#include "criminal.h"
#include "player.h"

void Criminal::checkCriminalShot()
{
	std::list<Ammo*>::iterator it = m_gun.begin();
	Character* player = m_state->getPlayer();

	while (it != m_gun.end())
	{
		Ammo* shot = *it;
		if (shot->checkShotCharacter(player))
		{
			it = m_gun.erase(it);
			delete shot;
			m_state->finishGame("Got shot");
		}
		else ++it;
	}
}

void Criminal::moveCharacter(float dt)
{
	float delta_time = dt / 10.0f;
	m_pos_x -= m_speed_horizontal * delta_time;
}

void Criminal::update(float dt)
{
	Character::update(dt);

	int time = (int)graphics::getGlobalTime() % (1000 * m_shooting_time_frequency);
	if (time <= dt) shootGun(-1.0f);
}

void Criminal::init()
{
	float width = m_state->getCanvasWidth();
	float min_pos_x = -1 * m_state->m_background_global_offset_x / width + 1;
	m_pos_x = sample_uniform(min_pos_x * width, (min_pos_x + 2) * width);

	m_asset_full_path = m_state->getAssetPath() + "criminal.png";
	m_height_to_width = 1.44f;
	Character::init();
}

void Criminal::draw()
{
	Character::draw();
}
