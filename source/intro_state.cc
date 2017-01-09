/* intro_state.cc */

#include <include/intro_state.h>

IntroState::IntroState( StateMachine &	machine,
	sf::RenderWindow &		window,
	bool				replace )
	: State{ machine, window, replace }
{
	initializeState();
}

void IntroState::initializeState()
{
	restartStateClock();

	m_worldView = m_window.getDefaultView();

	// background
	m_bgTex.loadFromFile( "assets/textures/640x480_title_screen.png" );
	m_bg.setTexture( m_bgTex, true );
	// m_bg.setOrigin( sf::Vector2f( 0,0 ) );
	// m_bg.setPosition( sf::Vector2f( CONFIG_WIN_WIDTH / 2, CONFIG_WIN_HEIGHT / 2 ) );

	// debug overlay font
	m_font.loadFromFile( "assets/fonts/sansation.ttf" );
	m_statisticsText.setFont( m_font );
	m_statisticsText.setPosition( 5.f, 5.f );
	m_statisticsText.setCharacterSize( 12u );
	m_statisticsText.setFillColor( sf::Color::White );
	updateDebugOverlayTextIfEnabled( true );// give me stats in the first frame, but first make up some plausible values

	// PressToContinue Text
	m_fontPressToContinue.loadFromFile( "assets/fonts/sansation.ttf" );
	m_textPressToContinue.setFont( m_fontPressToContinue );
	m_textPressToContinue.setCharacterSize( 24u );
	m_textPressToContinue.setFillColor( sf::Color::White );
	m_textPressToContinue.setString( "Press Space Bar to Continue" );
	centerOrigin( m_textPressToContinue );
	m_textPressToContinue.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y * .85f ) );

	// Start off opaque
	m_alpha = sf::Color { 0, 0, 0, 255 };
	// Fill the fader surface with black
	m_fader.setFillColor( m_alpha );
	m_fader.setSize( static_cast <sf::Vector2f> ( m_bgTex.getSize() ) );
}

void IntroState::pause()
{
}

void IntroState::resume()
{
	restartStateClock();
}

void IntroState::update()
{
	sf::Time m_elapsedTime = m_clock.restart();
	m_timeSinceLastUpdate += m_elapsedTime;

	while ( m_timeSinceLastUpdate > State::TimePerFrame ) {
		m_timeSinceLastUpdate -= State::TimePerFrame;
		processEvents();
		// update statistics for the debug overlay
		m_statisticsUpdateTime += m_elapsedTime;
		m_statisticsNumFrames += 1;
		// update statsText only once a second
		if ( m_statisticsUpdateTime >= sf::seconds( 1.0f ) ) {
			if ( m_statisticsNumFrames <= 1 ) {
				break;	// if we're playing catchup, don't bother with debugOverlayText
			}

			recordObservedFPS();
			dynamicallyAdjustFPSLimit();
			updateDebugOverlayTextIfEnabled();
			printConsoleDebugIfEnabled();

			m_statisticsUpdateTime -= sf::seconds( 1.0f );
			m_statisticsNumFrames = 0;
		}// exiting update statsText only once a second
	}// exiting "m_timeSinceLastUpdate > State::TimePerFrame". -- draw() will execute now.
	if ( m_alpha.a != 0 ) {
		m_alpha.a--;
	}
	m_fader.setFillColor( m_alpha );

	// TODO: add delay timer here & when timer is out, automatically continue to the main menu
}// exiting update()

void IntroState::draw()
{
	// Clear the previous drawing
	m_window.clear();
	m_window.	draw(	m_bg );
	m_window.	draw(	m_statisticsText );
	// No need to draw if it's transparent
	if ( m_alpha.a != 0 ) {
		m_window.draw( m_fader );
	}
	m_window.draw( m_textPressToContinue );
	m_window.display();
}

void IntroState::processEvents()
{
	// fetch events
	sf::Event evt;

	// process events
	while ( m_window.pollEvent( evt ) ) {
		switch ( evt.type ) {
			case sf::Event::Closed:
				m_machine.quit();
				break;

			case sf::Event::KeyPressed:
				// NOTE: Intro should not have pause state (no user input = already paused state!)
				switch ( evt.key.code ) {
					case sf::Keyboard::Escape:
					case sf::Keyboard::Space:
					case sf::Keyboard::Return:
						m_next = StateMachine::build <MainMenuState> ( m_machine, m_window, true );
						break;
					case sf::Keyboard::Q:
						m_machine.quit();
						break;
					case sf::Keyboard::F2:
						this->toggleDebugShowOverlay();
						break;
					case sf::Keyboard::F3:
						this->toggleDebugConsoleOutput();
						break;
					case sf::Keyboard::F4:
						this->toggleDebugDynFPSConsoleOutput();
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}

/* EOF */

