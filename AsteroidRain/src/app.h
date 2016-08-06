#ifndef _APP_
#define _APP_

#include <SFML/Graphics.hpp>
#include <vector>

// App class hadnling the game loop and all application objects
class App
{
public:
	App();
	void RunApp();
	void CloseApp();
private:
	enum GAME_STATES {GAME_INTRO, GAME_PLAY, GAME_OVER};
	GAME_STATES m_current_game_state;

	// core
	void InitState();
	void UpdateState(double delta_time);
	void RenderState();
	void ExitState();
	void ChangeState(GAME_STATES new_game_state);

	// collisions
	bool MouseClickedSprite(sf::Sprite& sprite);

	sf::Font m_font;
	sf::RenderWindow m_window;
	sf::Clock m_game_timer;
	int m_score;
	sf::Text m_score_text;
	sf::Text m_game_timer_text;
	sf::Text m_lives_text;
	sf::Text m_high_score_text;
	sf::Text m_game_title_text;
	sf::Text m_game_over_text;
	sf::Text m_button_text;
	int m_high_score;
	int m_lives;
	bool m_mouse_clicked;
	sf::Sprite m_start_button;
	sf::Texture m_start_button_texture;
	int m_fps;
	sf::Text m_fps_text;

	// asteroids
	std::vector<sf::Sprite> asteroids;
};

#endif