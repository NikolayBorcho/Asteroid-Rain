#ifndef _ASTEROID_
#define _ASTEROID_

#include <SFML/Graphics.hpp>
#include <vector>

// Store and handle the asteroids in the game
class Asteroid : public sf::Sprite
{
public:
	Asteroid();
	void Init();
	void Update(double delta_time);
	void Render(sf::RenderWindow* window);
	void CleanUp();
	std::vector<sf::Sprite> m_asteroids;
private:

	sf::Texture m_small_asteroid_texture;
	
};

#endif