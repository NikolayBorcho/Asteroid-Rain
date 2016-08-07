#ifndef _ASTEROID_
#define _ASTEROID_

#include <SFML/Graphics.hpp>
#include <vector>

// Store and handle the asteroids in the game
class Asteroid : public sf::Sprite
{
public:
	Asteroid();
	~Asteroid();
	void Init(sf::RenderWindow* window);
	void Update(double delta_time);
	void Render();
	void CleanUp();
	std::vector<sf::Sprite> m_asteroids;
private:
	sf::Sprite m_small_asteroid;
	sf::Texture m_small_asteroid_texture;
	sf::RenderWindow* m_window;
	sf::Clock m_timer;
};

#endif