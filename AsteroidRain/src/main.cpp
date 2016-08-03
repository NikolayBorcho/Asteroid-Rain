// Asteroid Rain Game as defined by Mediatonic
// Using SFML C++ library
// Nikolay Panayotov
// 2016

#include <windows.h>
#include <SFML/Graphics.hpp>

void gameApp();

// application entry point
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	gameApp();
}

// Game Simulation
void gameApp()
{
	// load font
	sf::Font font;
	font.loadFromFile("res/BebasNeue.otf");

	// create a window
    sf::RenderWindow window(sf::VideoMode(1024, 576), "Asteroid Rain");
	
	// game Properties
	sf::Clock clock;
	float delta_time;

	// Game Loop
    while (window.isOpen())
	{
		// Handle Time
		sf::Time elapsed = clock.restart();		
		delta_time = elapsed.asSeconds();
		// Handle Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
			{
                window.close();
			}
        }

		// Drawing Scene
        window.clear(sf::Color(255,255,255,255));
        window.display();
    }
}