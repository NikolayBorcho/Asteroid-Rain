#include "asteroids_control.h"
#include <cmath>

// Nikolay Panayotov, 2016

// Constants
const int AsteroidsControl::M_GENERATION_TIME_INTERVAL = 900;
const float AsteroidsControl::M_SMALL_ASTEROID_MIN_SPEED = 0.1f;
const float AsteroidsControl::M_SMALL_ASTEROID_MAX_SPEED = 0.9f;
const float AsteroidsControl::M_SUPER_ASTEROID_MIN_SPEED = 0.05f;
const float AsteroidsControl::M_SUPER_ASTEROID_MAX_SPEED = 0.5f;
const int AsteroidsControl::M_ASTEROID_SPEED_LEVELS = 5;
const int AsteroidsControl::M_PARTICLES_LIFE_TIME = 300;
const int AsteroidsControl::M_NUM_PARTICLES_PER_EXPLOSION = 12;
const float AsteroidsControl::M_PARTICLES_SPEED = 0.5f;

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
			asteroid.setVelocity(sf::Vector2f(0.f, M_SMALL_ASTEROID_MIN_SPEED + (M_SMALL_ASTEROID_MAX_SPEED - M_SMALL_ASTEROID_MIN_SPEED) * ( (rand()%M_ASTEROID_SPEED_LEVELS) / float(M_ASTEROID_SPEED_LEVELS))) );
		}
		else
		{
			// create super asteroid
			asteroid.setType(Asteroid::ASTEROID_TYPE::SUPER);
			asteroid.setTexture(m_super_asteroid_texture);
			asteroid.setOrigin(asteroid.getLocalBounds().width/2, asteroid.getLocalBounds().height/2);
			asteroid.setPosition(rand()%(m_window->getSize().x - int(asteroid.getLocalBounds().width)), -asteroid.getLocalBounds().height);	
			asteroid.setVelocity(sf::Vector2f(0.f, M_SUPER_ASTEROID_MIN_SPEED + (M_SUPER_ASTEROID_MAX_SPEED - M_SUPER_ASTEROID_MIN_SPEED) * ( (rand()%M_ASTEROID_SPEED_LEVELS) / float(M_ASTEROID_SPEED_LEVELS))) );	
		}
		m_asteroids.push_back(asteroid);
		m_generator_timer.restart();
	}

	// update properties of asteroids
	for (std::vector<Asteroid>::iterator it = m_asteroids.begin(); it != m_asteroids.end(); ++it)
	{
		// move and rotate asteroids
		it->move(it->getVelocity().x*delta_time,it->getVelocity().y*delta_time);
		it->rotate(it->getVelocity().y*delta_time);
		// check if particle explosions are done
		if ( (it->getType() == Asteroid::ASTEROID_TYPE::PARTICLE) && (it->m_life_clock.getElapsedTime() >= sf::milliseconds(M_PARTICLES_LIFE_TIME)) )
		{
			it->isDead = true;
		}
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
	split_asteroid.setVelocity(sf::Vector2f(0.f, M_SMALL_ASTEROID_MIN_SPEED + (M_SMALL_ASTEROID_MAX_SPEED - M_SMALL_ASTEROID_MIN_SPEED) * ( (rand()%M_ASTEROID_SPEED_LEVELS) / float(M_ASTEROID_SPEED_LEVELS))) );
	m_new_asteroids.push(split_asteroid);
	// and a second one to the right side
	split_asteroid.setPosition(asteroid.getPosition().x + split_asteroid.getLocalBounds().width/2, asteroid.getPosition().y);
	split_asteroid.setVelocity(sf::Vector2f(0.f, M_SMALL_ASTEROID_MIN_SPEED + (M_SMALL_ASTEROID_MAX_SPEED - M_SMALL_ASTEROID_MIN_SPEED) * ( (rand()%M_ASTEROID_SPEED_LEVELS) / float(M_ASTEROID_SPEED_LEVELS))) );
	m_new_asteroids.push(split_asteroid);
}


//---
void AsteroidsControl::CreateExplosion(sf::Vector2f position)
{
	// create an explosion paticle effect
	Asteroid particle;
	particle.setType(Asteroid::ASTEROID_TYPE::PARTICLE);
	particle.setTexture(m_small_asteroid_texture);
	particle.setOrigin(particle.getLocalBounds().width/2, particle.getLocalBounds().height/2);
	particle.setPosition(position);	
	particle.setScale(0.1f, 0.1f);
	// set velocities to all directions in a circle
	double angle = 0;
	for (int i = 0; i < M_NUM_PARTICLES_PER_EXPLOSION; ++i)
	{
		angle = i/float(M_NUM_PARTICLES_PER_EXPLOSION)*2*3.141569265;
		particle.setVelocity(sf::Vector2f(std::cos(angle)*M_PARTICLES_SPEED, std::sin(angle)*M_PARTICLES_SPEED));
		particle.m_life_clock.restart();
		m_new_asteroids.push(particle);
	}
}