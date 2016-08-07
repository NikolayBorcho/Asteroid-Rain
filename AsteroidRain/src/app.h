#ifndef _APP_
#define _APP_

// Nikolay Panayotov, 2016

#include <SFML/Graphics.hpp>
#include "asteroids_control.h"

// App class handling the game loop and all application objects
class App
{
public:
	App();
	void RunApp();
	void CloseApp();
private:
	// APPLICATION ESSENTIALS
	// game states handling
	enum GAME_STATES {GAME_INTRO, GAME_PLAY, GAME_OVER};
	GAME_STATES m_current_game_state;
	void ChangeState(GAME_STATES new_game_state);

	// core functionality
	void InitState();
	void UpdateState(double delta_time);
	void RenderState();
	void ExitState();
	
	// main app window
	sf::RenderWindow m_window;

	// fps tracking
	int m_fps;
	sf::Text m_fps_text;
	
	// ---
	// ADDITIONAL METHODS
	// checks if a sprite is clicked
	bool MouseClickedRectSprite(sf::Sprite& sprite);
	bool MouseClickedCircleSprite(sf::Sprite& sprite);
	bool m_mouse_clicked;
	
	void UpdateHUD();
	void UpdateAsteroids(double delta_time);

	// ---
	// GAME OBJECTS AND PROPERTIES
	int m_score;
	int m_high_score;
	int m_lives;

	sf::Clock m_game_timer;

	sf::Clock m_flash_timer;
	sf::RectangleShape m_flash;
	
	// Interface text
	sf::Font m_font;

	sf::Text m_score_text;
	sf::Text m_high_score_text;
	sf::Text m_lives_text;
	sf::Text m_game_timer_text;

	sf::Text m_game_title_text;
	sf::Text m_game_over_text;

	// Sprites
	sf::Sprite m_start_game_button;
	sf::Texture m_start_game_button_texture;

	sf::Sprite m_play_again_button;
	sf::Texture m_play_again_button_texture;

	// Asteroids
	AsteroidsControl m_asteroids_control;

	// ---
	// CONSTANTS
	static const int M_TIME_LIMIT = 60;
	static const int M_RED_FLASH_MILLISECS = 1000;
};

#endif