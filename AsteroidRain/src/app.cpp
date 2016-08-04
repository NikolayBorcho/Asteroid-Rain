#include "app.h"

App::App()
{
}

void App::Run()
{
	// initalize properties
	Init();

	// game time
	sf::Clock clock;
	float delta_time;

	// Game Loop
    while (window.isOpen())
	{
		// handle time
		sf::Time elapsed = clock.restart();		
		delta_time = elapsed.asSeconds();

		// handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
			// closing event
            if (event.type == sf::Event::Closed)
			{
                window.close();
			}
        }

		Update(delta_time);
		Render();
	}

	// clean up and exit
	End();
}


// Initialize Game Properties
void App::Init()
{
	// load font
	sf::Font font;
	font.loadFromFile("res/BebasNeue.otf");

	// create the main window
	window.create(sf::VideoMode(1024, 576), "Asteroid Rain");
}


// Clean up and Exit
void App::End()
{

}


// Game Logic
void App::Update(float delta_time)
{
		
}


// Drawing the Scene
void App::Render()
{
    window.clear(sf::Color(255,255,255,255));
	// render the scene


    window.display();
}