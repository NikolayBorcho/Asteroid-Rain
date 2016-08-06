#include "asteroid.h"
#include "to_string.h"

Asteroid::Asteroid()
{
}

void Asteroid::Init()
{
	// asteroids
	m_small_asteroid_texture.loadFromFile("res/small_asteroid.png");
	sf::Sprite asteroid;
	asteroid.setTexture(m_small_asteroid_texture);
	asteroid.setPosition(100, 100);
	m_asteroids.push_back(asteroid);
	asteroid.setPosition(300, 120);
	m_asteroids.push_back(asteroid);
}

void Asteroid::Update(double delta_time)
{
	// itearate asteroids
	for (std::vector<sf::Sprite>::iterator it = m_asteroids.begin(); it != m_asteroids.end(); ++it)
	{
		it->move(0.f,.1f*delta_time);
	}
}

void Asteroid::Render(sf::RenderWindow* window)
{
	// draw asteroids
	for (std::vector<sf::Sprite>::iterator it = m_asteroids.begin(); it != m_asteroids.end(); ++it)
	{
		window->draw(*it);
	}
}