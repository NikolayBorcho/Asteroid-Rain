#ifndef _ASTEROIDS_CONTROL_
#define _ASTEROIDS_CONTROL_

// Nikolay Panayotov, 2016

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

	// core functionality
	void Init(sf::RenderWindow* window);
	void Update(double delta_time);
	void Render();
	void CleanUp();

	void SplitAsteroid(Asteroid asteroid);
	void CreateExplosion(sf::Vector2f position);

	std::vector<Asteroid> m_asteroids;
private:
	sf::RenderWindow* m_window;	// window to render asteroids
	sf::Clock m_generator_timer;	// timer for generating asteroids
	std::queue<Asteroid> m_new_asteroids;	// store newly created asteroids in a queue before processing

	// texture resources
	sf::Texture m_small_asteroid_texture;
	sf::Texture m_super_asteroid_texture;

	// ---
	// CONSTANTS
	static const int M_GENERATION_TIME_INTERVAL;
	static const float M_SMALL_ASTEROID_MIN_SPEED;
	static const float M_SMALL_ASTEROID_MAX_SPEED;
	static const float M_SUPER_ASTEROID_MIN_SPEED;
	static const float M_SUPER_ASTEROID_MAX_SPEED;
	static const int M_ASTEROID_SPEED_LEVELS;
	static const int M_PARTICLES_LIFE_TIME;
	static const int M_NUM_PARTICLES_PER_EXPLOSION;
	static const float M_PARTICLES_SPEED;
};

#endif