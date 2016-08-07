#ifndef _ASTEROIDS_CONTROL_
#define _ASTEROIDS_CONTROL_

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include "asteroid.h"

// Store and handle the asteroids in the game
class AsteroidsControl
{
public:
	AsteroidsControl();
	~AsteroidsControl();
	void Init(sf::RenderWindow* window);
	void Update(double delta_time);
	void Render();
	void CleanUp();
	std::vector<Asteroid> m_asteroids;
private:
	sf::Texture m_small_asteroid_texture;
	sf::Texture m_super_asteroid_texture;
	sf::RenderWindow* m_window;
	sf::Clock m_timer;
	std::queue<Asteroid> m_new_asteroids;
};

#endif