#include "asteroids_control.h"
#include "to_string.h"

AsteroidsControl::AsteroidsControl()
{
}

void AsteroidsControl::Init(sf::RenderWindow* window)
{
	m_window = window;
	// textures
	m_small_asteroid_texture.loadFromFile("res/small_asteroid.png");
	m_super_asteroid_texture.loadFromFile("res/super_asteroid.png");

	srand(time(NULL));
	m_timer.restart();
}

void AsteroidsControl::Update(double delta_time)
{
	// split asteroids
	for (std::vector<Asteroid>::iterator it = m_asteroids.begin(); it != m_asteroids.end(); ++it)
	{
		if (it->isDead)
		{
			if (it->getType() == Asteroid::ASTEROID_TYPE::SUPER)
			{
				Asteroid split_asteroid;
				// create small asteroid
				split_asteroid.setType(Asteroid::ASTEROID_TYPE::SMALL);
				split_asteroid.setTexture(m_small_asteroid_texture);
				split_asteroid.setPosition(it->getPosition().x, it->getPosition().y);	
				split_asteroid.setSpeed(0.1f + 0.1f*(rand()%5));
				m_new_asteroids.push(split_asteroid);
				// second one
				split_asteroid.setPosition(it->getPosition().x + split_asteroid.getLocalBounds().width, it->getPosition().y);	
				split_asteroid.setSpeed(0.1f + 0.1f*(rand()%5));
				m_new_asteroids.push(split_asteroid);
			}
		}
	}

	while (m_new_asteroids.size() > 0)
	{
		m_asteroids.push_back(m_new_asteroids.front());
		m_new_asteroids.pop();
	}

	// delete dead asteroids
	for (std::vector<Asteroid>::iterator it = m_asteroids.begin(); it != m_asteroids.end(); )
	{
		if (it->isDead)
			it = m_asteroids.erase(it);
		else
			it++;
	}

	// generate new asteroids
	if (m_timer.getElapsedTime() > sf::milliseconds(900) )
	{
		Asteroid asteroid;
		if (rand()%2)
		{
			// create small asteroid
			asteroid.setType(Asteroid::ASTEROID_TYPE::SMALL);
			asteroid.setTexture(m_small_asteroid_texture);
			asteroid.setPosition(rand()%(m_window->getSize().x - int(asteroid.getLocalBounds().width)), -asteroid.getLocalBounds().height);	
			asteroid.setSpeed(0.1f + 0.1f*(rand()%5));
		}
		else
		{
			// create super asteroid
			asteroid.setType(Asteroid::ASTEROID_TYPE::SUPER);
			asteroid.setTexture(m_super_asteroid_texture);
			asteroid.setPosition(rand()%(m_window->getSize().x - int(asteroid.getLocalBounds().width)), -asteroid.getLocalBounds().height);	
			asteroid.setSpeed(0.05f + 0.1f*(rand()%4));
			
		}
		m_asteroids.push_back(asteroid);
		m_timer.restart();
	}

	// itearate asteroids
	for (std::vector<Asteroid>::iterator it = m_asteroids.begin(); it != m_asteroids.end(); ++it)
	{
		it->move(0.f,it->getSpeed()*delta_time);
	}
}


void AsteroidsControl::Render()
{
	// draw asteroids
	for (std::vector<Asteroid>::iterator it = m_asteroids.begin(); it != m_asteroids.end(); ++it)
	{
		m_window->draw(*it);
	}
}

void AsteroidsControl::CleanUp()
{
	m_window = 0;
	m_asteroids.clear();
}

AsteroidsControl::~AsteroidsControl()
{
	m_window = 0;
	m_asteroids.clear();
}