#ifndef _ASTEROID_
#define _ASTEROID_

#include <SFML/Graphics.hpp>
#include <vector>

// Store and handle the asteroids in the game
class Asteroid : public sf::Sprite
{
public:
	Asteroid();

	enum ASTEROID_TYPE {SMALL, SUPER};

	void setSpeed(float speed) { m_speed = speed; }
	float getSpeed() { return m_speed; }
	void setType(ASTEROID_TYPE type) { m_type = type; }
	ASTEROID_TYPE getType() { return m_type; }
	bool isDead;
private:
	float m_speed;
	ASTEROID_TYPE m_type;
};

#endif