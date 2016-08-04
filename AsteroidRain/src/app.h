#ifndef _APP_
#define _APP_

#include <SFML/Graphics.hpp>

// App class hadnling the game loop and all application objects
class App
{
public:
	App();
	void Run();
private:
	void Init();
	void Update(float delta_time);
	void Render();
	void End();
	sf::RenderWindow window;
};

#endif