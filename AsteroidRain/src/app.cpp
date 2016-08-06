#include "app.h"
#include "to_string.h"

App::App()
{
}


// ---
void App::RunApp()
{
	// load font
	m_font.loadFromFile("res/BebasNeue.otf");
	
	// create the main window
	m_window.create(sf::VideoMode(1024, 576), "Asteroid Rain");

	// fps text
	m_fps_text.setFont(m_font);
	m_fps_text.setColor(sf::Color::Black);
	m_fps_text.setPosition(m_window.getSize().x - 100.f, 10.f);
	
	// high score
	m_high_score = 0;
	m_high_score_text.setFont(m_font);
	m_high_score_text.setColor(sf::Color::Blue);
	m_high_score_text.setPosition(m_window.getSize().x/2, m_window.getSize().y/2);
	m_high_score_text.setString("High Score: ");
	
	// game time
	sf::Clock frame_clock;
	sf::Clock seconds_clock;
	seconds_clock.restart();
	double delta_time;
	int frame_count = 0;
	m_fps = 0;

	ChangeState(GAME_INTRO);

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
		UpdateState(delta_time);
		RenderState();

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
	CloseApp();
}


// ---
void App::CloseApp()
{

}


// ---
void App::ExitState()
{
	switch (m_current_game_state)
	{
	case GAME_INTRO:

		break;
	case GAME_PLAY:

		break;

	case GAME_OVER:

		break;
	}
}


// ---
void App::InitState()
{
	switch (m_current_game_state)
	{
	case GAME_INTRO:
		// sprites
		m_start_button_texture.loadFromFile("res/start_button.png");
		m_start_button.setTexture(m_start_button_texture);
		m_start_button.setPosition(m_window.getSize().x/2 - m_start_button.getLocalBounds().width/2, m_window.getSize().y/2 - m_start_button.getLocalBounds().height/2);

		break;
	case GAME_PLAY:
		// timer
		{
		// player lives
		m_lives = 5;
		m_lives_text.setFont(m_font);
		m_lives_text.setColor(sf::Color::Red);
		m_lives_text.setPosition(10.f, m_window.getSize().y - 40.f);
		m_lives_text.setString("Lives: ");
		// current score
		m_score = 0;
		m_score_text.setFont(m_font);
		m_score_text.setColor(sf::Color::Red);
		m_score_text.setPosition(10.f, m_window.getSize().y - 80.f);
		m_score_text.setString("Score: ");


		m_game_timer.restart();
		m_game_timer_text.setFont(m_font);
		m_game_timer_text.setColor(sf::Color::Red);
		m_game_timer_text.setPosition(m_window.getSize().x - 160.f, m_window.getSize().y - 40.f);
		m_game_timer_text.setString("Time left: " + to_string(60,std::dec));
		
		m_asteroids.Init();
		}
		break;

	case GAME_OVER:

		break;
	}
}


// ---
void App::UpdateState(double delta_time)
{
	switch (m_current_game_state)
	{
	case GAME_INTRO:
		if (MouseClickedSprite(m_start_button))
		{
			ChangeState(GAME_PLAY);
		}
		break;
	case GAME_PLAY:
		// stopwatch countdown
		m_game_timer_text.setString("Time left: " + to_string<int>(10 - m_game_timer.getElapsedTime().asSeconds(),std::dec));
		if (m_game_timer.getElapsedTime().asSeconds() >= 10)
		{
			ChangeState(GAME_INTRO);
		}
		
		// itearate asteroids
		m_asteroids.Update(delta_time);
		for (std::vector<sf::Sprite>::iterator it = m_asteroids.m_asteroids.begin(); it != m_asteroids.m_asteroids.end(); /*++it*/)
		{
			if (MouseClickedSprite(*it))
			{
				it = m_asteroids.m_asteroids.erase(it);
				m_score++;
			}
			else if (it->getPosition().y > m_window.getSize().y)
			{
				it = m_asteroids.m_asteroids.erase(it);
				m_lives--;
			}
			else
				it++;
		}
		break;

	case GAME_OVER:

		break;
	}
}


// ---
void App::RenderState()
{
    m_window.clear(sf::Color(255,255,255,255));

	// render the scene according to state
	switch (m_current_game_state)
	{
	case GAME_INTRO:
		m_window.draw(m_start_button);
		break;
	case GAME_PLAY:
		m_asteroids.Render(&m_window);
		m_window.draw(m_game_timer_text);
		m_score_text.setString("Score: " + to_string<int>(m_score,std::dec));
		m_window.draw(m_score_text);
		m_lives_text.setString("Lives: " + to_string<int>(m_lives,std::dec));
		m_window.draw(m_lives_text);

		break;

	case GAME_OVER:
		m_window.draw(m_high_score_text);
		break;
	}

	#ifdef _DEBUG
		// display frame rate only in debug mode
		m_fps_text.setString("FPS: " + to_string<int>(m_fps,std::dec));
		m_window.draw(m_fps_text);
	#endif // _DEBUG

    m_window.display();
}


// ---
void App::ChangeState(GAME_STATES new_game_state)
{
	// call exit of current state
	ExitState();
	// change to new state
	m_current_game_state = new_game_state;
	// call init of new state
	InitState();
}


// ---
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
