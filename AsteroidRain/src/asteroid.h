#ifndef _ASTEROID_
#define _ASTEROID_

// Nikolay Panayotov, 2016

#include <SFML/Graphics.hpp>

// Represents an asteroid sprite. Has a type and speed, as well as an isDead flag.
class Asteroid : public sf::Sprite
{
public:
	Asteroid();

	enum ASTEROID_TYPE {SMALL, SUPER, PARTICLE};

	bool isDead;
	sf::Clock m_life_clock;

	// getters and setters
	void setType(ASTEROID_TYPE type) { m_type = type; }
	ASTEROID_TYPE getType() { return m_type; }
	void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
	sf::Vector2f getVelocity() { return m_velocity; }

private:
	ASTEROID_TYPE m_type;
	sf::Vector2f m_velocity;
};

#endif