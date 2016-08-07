#include "asteroids_control.h"

// Nikolay Panayotov, 2016

// Constants
const int AsteroidsControl::M_GENERATION_TIME_INTERVAL = 900;
const float AsteroidsControl::M_SMALL_ASTEROID_MIN_SPEED = 0.1f;
const float AsteroidsControl::M_SMALL_ASTEROID_MAX_SPEED = 0.9f;
const float AsteroidsControl::M_SUPER_ASTEROID_MIN_SPEED = 0.05f;
const float AsteroidsControl::M_SUPER_ASTEROID_MAX_SPEED = 0.5f;
const int AsteroidsControl::M_ASTEROID_SPEED_LEVELS = 5;

AsteroidsControl::AsteroidsControl()
{
}


AsteroidsControl::~AsteroidsControl()
{
	m_window = 0;
	m_asteroids.clear();
}

// ---
void AsteroidsControl::Init(sf::RenderWindow* window)
{
	m_window = window;	// get render window
	// load textures
	m_small_asteroid_texture.loadFromFile("res/small_asteroid.png");
	m_super_asteroid_texture.loadFromFile("res/super_asteroid.png");

	srand(time(NULL));	// new random seed each time
	m_generator_timer.restart();	// reset timer for generating new asteroids
}


// ---
void AsteroidsControl::Update(double delta_time)
{
	// delete dead asteroids
	for (std::vector<Asteroid>::iterator it = m_asteroids.begin(); it != m_asteroids.end(); )
	{
		if (it->isDead)
			it = m_asteroids.erase(it);
		else
			it++;
	}

	// create any asteroids in the creation queue
	while (m_new_asteroids.size() > 0)
	{
		m_asteroids.push_back(m_new_asteroids.front());
		m_new_asteroids.pop();
	}

	// generate new asteroids on even time intervals
	if (m_generator_timer.getElapsedTime() > sf::milliseconds(M_GENERATION_TIME_INTERVAL) )
	{
		Asteroid asteroid;
		if (rand()%3)	// create a small asteroid 2/3 of the time
		{
			// create small asteroid
			asteroid.setType(Asteroid::ASTEROID_TYPE::SMALL);
			asteroid.setTexture(m_small_asteroid_texture);
			asteroid.setOrigin(asteroid.getLocalBounds().width/2, asteroid.getLocalBounds().height/2);
			asteroid.setPosition(rand()%(m_window->getSize().x - int(asteroid.getLocalBounds().width)), -asteroid.getLocalBounds().height);	
			asteroid.setSpeed(M_SMALL_ASTEROID_MIN_SPEED + (M_SMALL_ASTEROID_MAX_SPEED - M_SMALL_ASTEROID_MIN_SPEED) * ( (rand()%M_ASTEROID_SPEED_LEVELS) / float(M_ASTEROID_SPEED_LEVELS)) );
		}
		else
		{
			// create super asteroid
			asteroid.setType(Asteroid::ASTEROID_TYPE::SUPER);
			asteroid.setTexture(m_super_asteroid_texture);
			asteroid.setOrigin(asteroid.getLocalBounds().width/2, asteroid.getLocalBounds().height/2);
			asteroid.setPosition(rand()%(m_window->getSize().x - int(asteroid.getLocalBounds().width)), -asteroid.getLocalBounds().height);	
			asteroid.setSpeed(M_SUPER_ASTEROID_MIN_SPEED + (M_SUPER_ASTEROID_MAX_SPEED - M_SUPER_ASTEROID_MIN_SPEED) * ( (rand()%M_ASTEROID_SPEED_LEVELS) / float(M_ASTEROID_SPEED_LEVELS)) );	
		}
		m_asteroids.push_back(asteroid);
		m_generator_timer.restart();
	}

	// move and rotate asteroids
	for (std::vector<Asteroid>::iterator it = m_asteroids.begin(); it != m_asteroids.end(); ++it)
	{
		it->move(0.f,it->getSpeed()*delta_time);
		it->rotate(it->getSpeed()*delta_time);
	}
}


// ---
void AsteroidsControl::Render()
{
	// draw all asteroids
	for (std::vector<Asteroid>::iterator it = m_asteroids.begin(); it != m_asteroids.end(); ++it)
	{
		m_window->draw(*it);
	}
}


// ---
void AsteroidsControl::CleanUp()
{
	m_window = 0;
	m_asteroids.clear();
}


//---
void AsteroidsControl::SplitAsteroid(Asteroid asteroid)
{
	Asteroid split_asteroid;
	// create a small asteroid to the left side
	split_asteroid.setType(Asteroid::ASTEROID_TYPE::SMALL);
	split_asteroid.setTexture(m_small_asteroid_texture);
	split_asteroid.setOrigin(split_asteroid.getLocalBounds().width/2, split_asteroid.getLocalBounds().height/2);
	split_asteroid.setPosition(asteroid.getPosition().x - split_asteroid.getLocalBounds().width/2, asteroid.getPosition().y);	
	split_asteroid.setSpeed(0.1f + 0.1f*(rand()%5));
	m_new_asteroids.push(split_asteroid);
	// and a second one to the right side
	split_asteroid.setPosition(asteroid.getPosition().x + split_asteroid.getLocalBounds().width/2, asteroid.getPosition().y);	
	split_asteroid.setSpeed(0.1f + 0.1f*(rand()%5));
	m_new_asteroids.push(split_asteroid);
}