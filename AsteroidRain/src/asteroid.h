#ifndef _ASTEROID_
#define _ASTEROID_

#include <SFML/Graphics.hpp>
#include <vector>

// Store and handle the asteroids in the game
class Asteroid : public sf::Sprite
{
public:
	Asteroid();
	void setSpeed(float speed) { m_speed = speed; }
	float getSpeed() { return m_speed; }

private:
	float m_speed;
};

#endif