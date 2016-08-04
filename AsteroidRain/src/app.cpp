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

	// set initial state
	game_state = GAME_INTRO;
}


// Clean up and Exit
void App::End()
{

}


// Game Logic
void App::Update(float delta_time)
{
	switch (game_state)
	{
	case GAME_INTRO:

		break;
	case GAME_PLAY:

		break;

	case GAME_OVER:

		break;
	}
}


// Drawing the Scene
void App::Render()
{
    window.clear(sf::Color(255,255,255,255));

	// render the scene according to state
	switch (game_state)
	{
	case GAME_INTRO:

		break;
	case GAME_PLAY:

		break;

	case GAME_OVER:

		break;
	}

    window.display();
}