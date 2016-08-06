#include "app.h"
#include "to_string.h"

App::App()
{
}

void App::Run()
{
	// initalize properties
	Init();

	// game time
	sf::Clock frame_clock;
	sf::Clock seconds_clock;
	seconds_clock.restart();
	double delta_time;
	int frame_count = 0;
	m_fps = 0;

	// Game Loop
    while (m_window.isOpen())
	{
		// handle time
		sf::Time elapsed = frame_clock.restart();		
		delta_time = elapsed.asMilliseconds();

		// reset mouse click
		m_mouse_clicked = false;

		// handle events
        sf::Event event;
        while (m_window.pollEvent(event))
        {
			// closing event
            if (event.type == sf::Event::Closed)
			{
                m_window.close();
			}

			// mouse input
			if (event.type == sf::Event::MouseButtonPressed)
			{
				// mouse click
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					m_mouse_clicked = true;
				}
			}
		}
		Update(delta_time);
		Render();

		// count frames per second
		if (seconds_clock.getElapsedTime().asSeconds() < 1.f)
		{
			frame_count++;
		}
		else
		{
			m_fps = frame_count;
			frame_count = 0;
			seconds_clock.restart();
		}
	}

	// clean up and exit
	End();
}


// Initialize Game Properties
void App::Init()
{
	// load font
	m_font.loadFromFile("res/BebasNeue.otf");
	
	// create the main window
	m_window.create(sf::VideoMode(1024, 576), "Asteroid Rain");

	// game timer text
	
	// fps text
	m_fps_text.setFont(m_font);
	m_fps_text.setColor(sf::Color::Black);
	m_fps_text.setPosition(m_window.getSize().x - 100.f, m_window.getSize().y - 40.f);
	
	// current score
	m_score = 0;
	m_score_text.setFont(m_font);
	m_score_text.setColor(sf::Color::Blue);
	m_score_text.setPosition(10.f, m_window.getSize().y - 40.f);
	m_score_text.setString("Score: ");
	// high score
	m_high_score = 0;
	m_high_score_text.setFont(m_font);
	m_high_score_text.setColor(sf::Color::Blue);
	m_high_score_text.setPosition(m_window.getSize().x/2, m_window.getSize().y/2);
	m_high_score_text.setString("High Score: ");
	// player lives
	m_lives = 5;

	// sprites
	m_start_button_texture.loadFromFile("res/start_button.png");
	m_start_button.setTexture(m_start_button_texture);
	m_start_button.setPosition(10.f,10.f);


	// set initial state
	m_game_state = GAME_INTRO;
}


// Clean up and Exit
void App::End()
{

}


// Game Logic
void App::Update(double delta_time)
{
	switch (m_game_state)
	{
	case GAME_INTRO:
		if (MouseClickedSprite(m_start_button))
		{
			m_game_state = GAME_PLAY;
		}
		m_start_button.move(0.1f*delta_time,0.f);
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
    m_window.clear(sf::Color(255,255,255,255));

	// render the scene according to state
	switch (m_game_state)
	{
	case GAME_INTRO:
		m_window.clear(sf::Color(0,255,0,255));
		m_window.draw(m_start_button);
		break;
	case GAME_PLAY:
		m_window.draw(m_score_text);
		break;

	case GAME_OVER:
		m_window.draw(m_high_score_text);
		break;
	}

	#ifdef _DEBUG
		m_fps_text.setString("FPS: " + to_string<int>(m_fps,std::dec));
		m_window.draw(m_fps_text);
	#endif // _DEBUG

    m_window.display();
}


// Collisions
bool App::MouseClickedSprite(sf::Sprite& sprite)
{
	if (m_mouse_clicked)
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(m_window);

		if (sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
			return true;
	}
	return false;
}
