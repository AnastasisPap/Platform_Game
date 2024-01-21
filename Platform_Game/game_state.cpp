#include <iostream>
#include <thread>
#include <chrono>
#include "game_state.h"
#include "player.h"
#include "first_level.h"
#include "second_level.h"
#include "third_level.h"
#include "cop.h"
#include "config.h"

GameState::GameState() {}

GameState::~GameState()
{
    if (m_player) delete m_player;
    if (m_cop) delete m_cop;
    if (m_current_level) delete m_current_level;
}

void GameState::init()
{
    m_brush_text.outline_opacity = 0.0f;
    m_brush_text.fill_color[0] = 1.0f;
    m_brush_text.fill_color[1] = 1.0f;
    m_brush_text.fill_color[2] = 1.0f;

    m_brush_text_important.outline_opacity = 0.0f;
    m_brush_text_important.fill_color[0] = 1.0f;
    m_brush_text_important.fill_color[1] = 0.5f;
    m_brush_text_important.fill_color[2] = 0.5f;

    m_current_level = new FirstLevel("first level", 60, 8.0f);
    m_current_level->init();

    m_player = new Player("Player", 1.5f);
    m_player->init();

    graphics::preloadBitmaps(getAssetPath());
}

void GameState::draw()
{
    if (!m_current_level)
        return;

    if (!m_has_game_started) drawStartText();
    else if (m_has_won) graphics::drawText(0.28f * m_canvas_width,
        0.4f * m_canvas_height, 45.0f, "You Won!! Press ESC to exit.", m_brush_text_important);
    else if (m_has_game_finished) 
    {
		graphics::drawText(0.45f * m_canvas_width, 0.4f * m_canvas_height, 45.0f, "You Lost.",
            m_brush_text_important);
		graphics::drawText(0.4f * m_canvas_width, 0.5f * m_canvas_height, 45.0f, m_lost_reason,
            m_brush_text_important);
		graphics::drawText(0.4f * m_canvas_width, 0.6f * m_canvas_height, 45.0f, "Press ESC to exit.",
            m_brush_text_important);
    }
    else if (!m_has_game_finished) m_current_level->draw();
}

void GameState::drawStartText()
{
    float starting_pos_y = 0.3f * m_canvas_height;
    float starting_pos_x = 0.15f * m_canvas_width;
    float font_size = 20.0f;

    graphics::drawText(starting_pos_x, starting_pos_y, font_size, " 1. Hurry up, the train will leave in 1.5 minutes (top-left timer). If you miss it, you miss your exam!", m_brush_text);
    graphics::drawText(starting_pos_x, starting_pos_y + 50.0f, font_size, " 2. Try to avoid pedestrians by jumping over them (pressing up arrow) or standing on ladders.", m_brush_text);
    graphics::drawText(starting_pos_x, starting_pos_y + 85.0f, font_size, "     If you don't they get angry and push you!", m_brush_text);
    graphics::drawText(starting_pos_x, starting_pos_y + 135.0f, font_size, " 3. You can also shoot pedestrians with your gun (left mouse click)", m_brush_text);
    graphics::drawText(starting_pos_x, starting_pos_y + 170.0f, font_size, "     Watch out though: shooting can result into cops chasing you! (top right star)", m_brush_text);
    graphics::drawText(starting_pos_x, starting_pos_y + 220.0f, font_size, " 4. On top of a ladder you will see a ticket. You need to collect it so you can safely get into the train.", m_brush_text);
    graphics::drawText(starting_pos_x, starting_pos_y + 255.0f, font_size, "     Otherwise if the train inspector catches you, you lose. However they are not always on the train :)", m_brush_text);

    graphics::drawText(0.4f * m_canvas_width, starting_pos_y + 320.0f, 30.0f, "Press space to start", m_brush_text_important);
}

void GameState::update(float dt)
{
    if (dt > 500)
        return;

    float sleep_time = std::max(0.0f, 17.0f - dt);
    std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));

    if (m_player->m_pos_x >= m_current_level->getLevelFinishPosX() && !m_has_game_finished)
    {
        int curr_level_num = m_current_level->getCurrentLevel();
        if (sample_uniform() <= m_validator_prob && !m_player->hasTicket())
        {
            m_has_game_finished = true;
            m_lost_reason = "No ticket";
            return;
        }

        m_player->updateTicket(false);
        m_player->resetGun();

        if (curr_level_num == 1)
        {
            delete m_current_level;
            m_current_level = new SecondLevel("second level", 100, 8.0f);
            m_current_level->init();
        }
        else if (curr_level_num == 2)
        {
            delete m_current_level;
            m_current_level = new ThirdLevel("third level", 100, 8.0f);
            m_current_level->init();
        }
        else if (curr_level_num == 3)
        {
            m_has_game_finished = true;
            m_has_won = true;
            return;
        }
    }

    if (!m_current_level)
        return;

    if (!m_has_game_started)
    {
        if (graphics::getKeyState(graphics::SCANCODE_SPACE))
        {
            m_has_game_started = true;
            int time = graphics::getGlobalTime() / 1000;
            m_current_level->startTimer(time);
        }
        return;
    }

    if (!m_has_game_finished) m_current_level->update(dt);
    else if (graphics::getKeyState(graphics::SCANCODE_ESCAPE))
    {
        delete this;
        exit(0);
    }
    m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
}

GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr)
		m_unique_instance = new GameState();

	return m_unique_instance;
}

GameState* GameState::m_unique_instance = nullptr;

float GameState::getLevelMaxWidth() { return m_current_level->getLevelFinishPosX(); }

void GameState::spawnCop()
{
    if (!m_cop)
    {
        m_cop = new Cop("cop");
        m_cop->init();
    }
}

void GameState::stopCop()
{
    if (m_cop)
    {
        delete m_cop;
        m_cop = nullptr;
    }
}
