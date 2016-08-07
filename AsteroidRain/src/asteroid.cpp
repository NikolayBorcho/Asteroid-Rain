#include "asteroid.h"
#include "to_string.h"

Asteroid::Asteroid()
{
}

void Asteroid::Init(sf::RenderWindow* window)
{
	m_window = window;
	// asteroids
	m_small_asteroid_texture.loadFromFile("res/small_asteroid.png");
	m_small_asteroid.setTexture(m_small_asteroid_texture);
	srand(time(NULL));
	m_timer.restart();
}

void Asteroid::Update(double delta_time)
{
	// generate new asteroids
	if (m_timer.getElapsedTime() > sf::milliseconds(900) )
	{
		m_small_asteroid.setPosition(rand()%(m_window->getSize().x - int(m_small_asteroid.getLocalBounds().width)), -m_small_asteroid.getLocalBounds().height);
		m_asteroids.push_back(m_small_asteroid);
		m_timer.restart();
	}

	// itearate asteroids
	for (std::vector<sf::Sprite>::iterator it = m_asteroids.begin(); it != m_asteroids.end(); ++it)
	{
		it->move(0.f,.1f*delta_time);
	}
}

void Asteroid::Render()
{
	// draw asteroids
	for (std::vector<sf::Sprite>::iterator it = m_asteroids.begin(); it != m_asteroids.end(); ++it)
	{
		m_window->draw(*it);
	}
}

void Asteroid::CleanUp()
{
	m_window = 0;
	m_asteroids.clear();
}

Asteroid::~Asteroid()
{
	m_window = 0;
	m_asteroids.clear();
}