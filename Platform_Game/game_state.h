#pragma once
#include <iostream>
#include <string>
#include <sgg/graphics.h>

class GameState
{
private:
	std::string m_asset_path = "assets\\";

	float m_canvas_width = 1200.0f;
	float m_canvas_height = 700.0f;

	float m_floor_level = m_canvas_height / 1.27f;
    static GameState* m_unique_instance;
	class Player* m_player = 0;
	class Level* m_current_level = nullptr;
	class Cop* m_cop = 0;
	bool m_has_game_finished = false;
	bool m_has_game_started = false;
    GameState();

	graphics::Brush m_brush_text;
	graphics::Brush m_brush_text_important;

// Make this private/protected and use player class as friend or add setter/getter to access this
public:
	float m_background_global_offset_x = 0.0f;
	bool m_debugging = false;

	void init();
	void draw();
	void update(float dt);
	void drawStartText();

    static GameState* getInstance();
	~GameState();

	std::string getAssetPath() { return m_asset_path; }
	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }

	void spawnCop();
	class Player* getPlayer() { return m_player; }
	class Cop* getCop() { return (m_cop ? m_cop : nullptr); }
	float getFloorLevel() { return m_floor_level; }
	float getLevelMaxWidth();
	void finishGame() { m_has_game_finished = true; }
	bool hasGameFinished() { return m_has_game_finished; }
};