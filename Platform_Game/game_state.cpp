#include <iostream>
#include <thread>
#include <chrono>
#include "game_state.h"
#include "player.h"
#include "level.h"

GameState::GameState() {}

GameState::~GameState()
{
	if (m_player) delete m_player;
	if (m_current_level) delete m_current_level;
}

void GameState::init()
{
    m_current_level = new Level();
    m_current_level->init();

    m_player = new Player("Player", 1.5f);
    m_player->init();

    graphics::preloadBitmaps(getAssetPath());
}

void GameState::draw()
{
    if (!m_current_level)
        return;

    m_current_level->draw();
}

void GameState::update(float dt)
{
    if (dt > 500)
        return;

    float sleep_time = std::max(0.0f, 17.0f - dt);
    std::this_thread::sleep_for(std::chrono::duration<float,std::milli>(sleep_time));

    if (!m_current_level)
        return;

    m_current_level->update(dt);
    m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
}

GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr)
		m_unique_instance = new GameState();

	return m_unique_instance;
}

GameState* GameState::m_unique_instance = nullptr;
