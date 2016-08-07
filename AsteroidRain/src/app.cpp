#include "app.h"
#include "to_string.h"

// Nikolay Panayotov, 2016

App::App()
{
}


// ---
void App::RunApp()
{
	// create the main window
	m_window.create(sf::VideoMode(1024, 576), "AsteroidsControl Rain", sf::Style::Titlebar | sf::Style::Close);

	// load main font
	m_font.loadFromFile("res/BebasNeue.otf");
	
	#ifdef _DEBUG
		// fps text for debug
		m_fps_text.setFont(m_font);
		m_fps_text.setColor(sf::Color::White);
		m_fps_text.setPosition(m_window.getSize().x - 100.f, 10.f);
	#endif // _DEBUG


	// game time prepare
	sf::Clock frame_clock;
	sf::Clock seconds_clock;
	double delta_time = 0;
	int frame_count = 0;
	m_fps = 0;

	seconds_clock.restart();

	// change to first game state
	m_current_game_state = GAME_INTRO;
	// call initialization of the first state
	InitState();

	// Game Loop
    while (m_window.isOpen())
	{
		// handle delta time
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
	// nothing needed for this particular app so far
}


// ---
void App::ExitState()
{
	switch (m_current_game_state)
	{
	case GAME_INTRO:
		break;

	case GAME_PLAY:
		m_asteroids_control.CleanUp();
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
		// start button init
		m_start_game_button_texture.loadFromFile("res/start_game_button.png");
		m_start_game_button.setTexture(m_start_game_button_texture);
		m_start_game_button.setPosition(m_window.getSize().x/2 - m_start_game_button.getLocalBounds().width/2, m_window.getSize().y/2 - m_start_game_button.getLocalBounds().height/2);
		
		// intial game properties
		m_high_score = 0;
		break;

	case GAME_PLAY:
		// Game Objects Init
		// asteroids
		m_asteroids_control.Init(&m_window);

		// flash
		m_flash.setSize(sf::Vector2f(m_window.getSize()));
		m_flash.setPosition(0.f, 0.f);
		m_flash.setFillColor(sf::Color(255, 0, 0, 0));

		// Text Interfaces Init
		// player lives setup
		m_lives = 5;
		m_lives_text.setFont(m_font);
		m_lives_text.setColor(sf::Color::Red);
		m_lives_text.setString("Lives: " + to_string<int>(m_lives,std::dec));
		m_lives_text.setPosition(10.f, m_window.getSize().y - 40.f);	

		// current score setup
		m_score = 0;
		m_score_text.setFont(m_font);
		m_score_text.setColor(sf::Color::Red);	
		m_score_text.setString("Score: " + to_string<int>(m_score,std::dec));	
		m_score_text.setPosition(10.f, m_window.getSize().y - 80.f);

		// high score setup
		m_high_score_text.setFont(m_font);
		m_high_score_text.setColor(sf::Color::Red);
		m_high_score_text.setString("High Score: " + to_string<int>(m_high_score, std::dec));
		m_high_score_text.setPosition(10.f, m_window.getSize().y - 120.f);

		// game timer
		m_game_timer.restart();
		m_game_timer_text.setFont(m_font);
		m_game_timer_text.setColor(sf::Color::Red);
		m_game_timer_text.setString("Time Left: " + to_string(60,std::dec));
		m_game_timer_text.setPosition(m_window.getSize().x - 140.f, m_window.getSize().y - 40.f);
		break;

	case GAME_OVER:
		// play again button init
		m_play_again_button_texture.loadFromFile("res/play_again_button.png");
		m_play_again_button.setTexture(m_play_again_button_texture);
		m_play_again_button.setPosition(m_window.getSize().x/2 - m_play_again_button.getLocalBounds().width/2, m_window.getSize().y/2 - m_play_again_button.getLocalBounds().height/2);

		// current score
		m_score_text.setColor(sf::Color::White);
		m_score_text.setString("Score: " + to_string<int>(m_score, std::dec));
		m_score_text.setPosition(m_window.getSize().x/2 - m_score_text.getLocalBounds().width/2, m_window.getSize().y/8 - m_score_text.getLocalBounds().height/2);
		
		// high score
		m_high_score_text.setColor(sf::Color::White);
		m_high_score_text.setString("High Score: "+ to_string<int>(m_high_score, std::dec));
		m_high_score_text.setPosition(m_window.getSize().x/2 - m_high_score_text.getLocalBounds().width/2, m_window.getSize().y/4 - m_high_score_text.getLocalBounds().height/2);		
		break;
	}
}


// ---
void App::UpdateState(double delta_time)
{
	switch (m_current_game_state)
	{
	case GAME_INTRO:
		if (MouseClickedRectSprite(m_start_game_button))
		{
			ChangeState(GAME_PLAY);
		}
		break;

	case GAME_PLAY:	
		// update game objects
		UpdateAsteroids(delta_time);

		// keep track of red flash
		if (m_flash_timer.getElapsedTime() < sf::milliseconds(M_RED_FLASH_MILLISECS))
			m_flash.setFillColor(sf::Color(255, 0, 0, sf::Uint8(255 - 255*(m_flash_timer.getElapsedTime().asMilliseconds()/float(M_RED_FLASH_MILLISECS))) ));

		// update high score
		if (m_score > m_high_score)
			m_high_score = m_score;

		// text interface
		UpdateHUD();
		
		// end game conditions
		if ((m_game_timer.getElapsedTime().asSeconds() >= M_TIME_LIMIT) || (m_lives <= 0))
			ChangeState(GAME_OVER);
		break;

	case GAME_OVER:
		if (MouseClickedRectSprite(m_play_again_button))
		{
			ChangeState(GAME_PLAY);
		}
		break;
	}
}


// ---
void App::RenderState()
{
    m_window.clear(sf::Color(0, 0, 50, 255));	// clear to "space blue" colour

	switch (m_current_game_state)
	{
	case GAME_INTRO:
		m_window.draw(m_start_game_button);
		break;

	case GAME_PLAY:
		// game objects
		m_asteroids_control.Render();
		// text interface
		m_window.draw(m_game_timer_text);
		m_window.draw(m_score_text);
		m_window.draw(m_high_score_text);
		m_window.draw(m_lives_text);
		// flash can cover everything
		m_window.draw(m_flash);
		break;

	case GAME_OVER:
		m_window.draw(m_play_again_button);
		m_window.draw(m_high_score_text);
		m_window.draw(m_score_text);
		break;
	}

	#ifdef _DEBUG
		// display frame rate only in debug mode
		m_fps_text.setString("FPS: " + to_string<int>(m_fps,std::dec));
		m_window.draw(m_fps_text);
	#endif // _DEBUG

    m_window.display();	// display final scene
}


// ---
void App::ChangeState(GAME_STATES new_game_state)
{
	// call exit of current state
	ExitState();
	// change to new state
	m_current_game_state = new_game_state;
	// call initialization of new state
	InitState();
}


// ---
bool App::MouseClickedRectSprite(sf::Sprite& sprite)
{
	// check if the mouse clicked a given sprite within its square boundary
	if (m_mouse_clicked)
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(m_window);

		if (sprite.getGlobalBounds().contains(float(mouse_pos.x), float(mouse_pos.y)))
			return true;
	}
	return false;
}


// ---
bool App::MouseClickedCircleSprite(sf::Sprite& sprite)
{
	// check if the mouse clicked a given sprite within a circle boundary
	if (m_mouse_clicked)
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(m_window);

		// first simple square test
		if (sprite.getGlobalBounds().contains(float(mouse_pos.x), float(mouse_pos.y)))
		{
			// more accurate circle test
			if ( (sprite.getPosition().x - mouse_pos.x)*(sprite.getPosition().x - mouse_pos.x)
				+ (sprite.getPosition().y - mouse_pos.y)*(sprite.getPosition().y - mouse_pos.y)
				< (sprite.getLocalBounds().width/2 * sprite.getLocalBounds().width/2) )
			return true;
		}
	}
	return false;
}


// ---
void App::UpdateHUD()
{
	// update text interface
	m_game_timer_text.setString("Time left: " + to_string<int>(int(M_TIME_LIMIT - m_game_timer.getElapsedTime().asSeconds()),std::dec));
	m_score_text.setString("Score: " + to_string<int>(m_score,std::dec));	
	m_lives_text.setString("Lives: " + to_string<int>(m_lives,std::dec));
	m_high_score_text.setString("High Score: "+ to_string<int>(m_high_score, std::dec));
}


// ---
void App::UpdateAsteroids(double delta_time)
{
	// clear, create and move asteroids
	m_asteroids_control.Update(delta_time);
	// interaction between asteroids and app
	for (std::vector<Asteroid>::iterator it = m_asteroids_control.m_asteroids.begin(); it != m_asteroids_control.m_asteroids.end(); ++it)
	{
		if (MouseClickedCircleSprite(*it))	// clicked on asteroid
		{
			if (it->getType() == Asteroid::ASTEROID_TYPE::SMALL)
			{
				it->isDead = true;
				m_score++;
			}
			else if (it->getType() == Asteroid::ASTEROID_TYPE::SUPER)
			{
				it->isDead = true;
				m_asteroids_control.SplitAsteroid(*it);
			}
		}
		else if (it->getPosition().y > m_window.getSize().y)	// reached bottom of screen
		{
			it->isDead = true;
			m_flash_timer.restart();	// flash screen red
			m_lives--;
		}
	}
}