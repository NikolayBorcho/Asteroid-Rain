#ifndef _ASTEROID_
#define _ASTEROID_

// Nikolay Panayotov, 2016

#include <SFML/Graphics.hpp>

// Represents an asteroid sprite. Has a type and speed, as well as an isDead flag.
class Asteroid : public sf::Sprite
{
public:
	Asteroid();

	enum ASTEROID_TYPE {SMALL, SUPER};

	bool isDead;

	// getters and setters
	void setType(ASTEROID_TYPE type) { m_type = type; }
	ASTEROID_TYPE getType() { return m_type; }
	void setSpeed(float speed) { m_speed = speed; }
	float getSpeed() { return m_speed; }
	
private:
	ASTEROID_TYPE m_type;
	float m_speed;
};

#endif