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
	bool m_has_won = false;
	std::string m_lost_reason = "";
    GameState();

	graphics::Brush m_brush_text;
	graphics::Brush m_brush_text_important;
	const float m_validator_prob = 0.7f;

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

	void spawnCop();
	void stopCop();

	class Player* getPlayer() { return m_player; }
	class Cop* getCop() { return (m_cop ? m_cop : nullptr); }
	void finishGame(std::string reason = "") { m_has_game_finished = true; m_lost_reason = reason; }

	float getLevelMaxWidth();
	float getFloorLevel() const { return m_floor_level; }
	bool hasGameFinished() const { return m_has_game_finished; }
	float getCanvasWidth() const { return m_canvas_width; }
	float getCanvasHeight() const { return m_canvas_height; }
};