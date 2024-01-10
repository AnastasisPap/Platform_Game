#pragma once
#include <string>
#include <sgg/graphics.h>

class GameState
{
private:
	std::string m_asset_path = "assets\\";

	int m_canvas_width = 1200;
	int m_canvas_height = 700;

	float m_floor_level = m_canvas_height / 1.27f;
    static GameState* m_unique_instance;
	class Player* m_player = 0;
	class Level* m_current_level = 0;
    GameState();

// Make this private/protected and use player class as friend or add setter/getter to access this
public:
	float m_background_global_offset_x = 0.0f;
    float m_player_global_offset_y = 0.0f;
	bool m_debugging = false;

	void init();
	void draw();
	void update(float dt);

    static GameState* getInstance();
	~GameState();

	std::string getAssetPath() { return m_asset_path; }
	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }

	class Player* getPlayer() { return m_player; }
	float getFloorLevel() { return m_floor_level; }
};