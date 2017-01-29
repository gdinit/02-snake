/* main_menu_state.cc */

#include "main_menu_state.h"

extern std::unique_ptr <Globals> GLOBALS;

MainMenuState::MainMenuState( StateMachine &machine, sf::RenderWindow &window, bool replace )
	: State{ machine, window, replace }
{
	initializeState();
}

void MainMenuState::initializeState()
{
	restartStateClock();

	GLOBALS->mustMainMenu = false;

	m_worldView = m_window.getDefaultView();
	m_urgentUpdateNeeded = 10;

	// debug overlay font
	m_font.loadFromFile( "assets/fonts/sansation.ttf" );
	m_statisticsText.setFont( m_font );
	m_statisticsText.setPosition( 5.f, 5.f );
	m_statisticsText.setCharacterSize( 12u );
	m_statisticsText.setFillColor( sf::Color::White );
	updateDebugOverlayTextIfEnabled( true );

	// ButtonsSharedResources ==============
	m_textureWhite.loadFromFile( "assets/textures/16x16_white.png" );

	if ( !m_sbMouseOver.loadFromFile( "assets/sounds/mouse_over1.wav" ) ) {
	}
	m_sMouseOver.setBuffer( m_sbMouseOver );

	if ( !m_sbMouseClicked.loadFromFile( "assets/sounds/button_clicked1.wav" ) ) {
	}
	m_sMouseClicked.setBuffer( m_sbMouseClicked );
	// =====================================

	// PlayMenuButton ======================
	m_sprPlay.setTexture( m_textureWhite );
	m_sprPlay.setTextureRect( sf::IntRect( 0, 0, static_cast <short int> ( CONFIG_MENU_BOX_WIDTH ), static_cast <short int> ( CONFIG_MENU_BOX_HEIGHT ) ) );
	m_sprPlay.setOrigin( CONFIG_MENU_BOX_WIDTH / 2.f, CONFIG_MENU_BOX_HEIGHT / 2.f );
	m_sprPlay.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y * CONFIG_MENU_BUTTON_1 ) );
	m_sprPlayNeedSFX = true;
	m_sprPlayButtonHot = false;
	m_fontPlayText.loadFromFile( "assets/fonts/sansation.ttf" );
	m_textPlay.setFont( m_fontPlayText );
	m_textPlay.setCharacterSize( 28u );
	m_textPlay.setFillColor( sf::Color::Black );
	m_textPlay.setString( "play   (space)" );
	centerOrigin( m_textPlay );
	m_textPlay.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y * CONFIG_MENU_BUTTON_1 ) );
	// =====================================

	// CreditsMenuButton ===================
	m_sprCredits.setTexture( m_textureWhite );
	m_sprCredits.setTextureRect( sf::IntRect( 0, 0, static_cast <short int> ( CONFIG_MENU_BOX_WIDTH ), static_cast <short int> ( CONFIG_MENU_BOX_HEIGHT ) ) );
	m_sprCredits.setOrigin( CONFIG_MENU_BOX_WIDTH / 2.f, CONFIG_MENU_BOX_HEIGHT / 2.f );
	m_sprCredits.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y * CONFIG_MENU_BUTTON_2 ) );
	m_sprCreditsNeedSFX = true;
	m_sprCreditsButtonHot = false;
	m_fontCreditsText.loadFromFile( "assets/fonts/sansation.ttf" );
	m_textCredits.setFont( m_fontCreditsText );
	m_textCredits.setCharacterSize( 28u );
	m_textCredits.setFillColor( sf::Color::Black );
	m_textCredits.setString( "credits   (C)" );
	centerOrigin( m_textCredits );
	m_textCredits.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y * CONFIG_MENU_BUTTON_2 ) );
	// =====================================

	// QuitMenuButton ======================
	m_sprQuit.setTexture( m_textureWhite );
	m_sprQuit.setTextureRect( sf::IntRect( 0, 0, static_cast <short int> ( CONFIG_MENU_BOX_WIDTH ), static_cast <short int> ( CONFIG_MENU_BOX_HEIGHT ) ) );
	m_sprQuit.setOrigin( CONFIG_MENU_BOX_WIDTH / 2.f, CONFIG_MENU_BOX_HEIGHT / 2.f );
	m_sprQuit.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y * CONFIG_MENU_BUTTON_3 ) );
	m_sprQuitNeedSFX = true;
	m_sprQuitButtonHot = false;
	m_fontQuitText.loadFromFile( "assets/fonts/sansation.ttf" );
	m_textQuit.setFont( m_fontQuitText );
	m_textQuit.setCharacterSize( 28u );
	m_textQuit.setFillColor( sf::Color::Black );
	m_textQuit.setString( "quit   (Q)" );
	centerOrigin( m_textQuit );
	m_textQuit.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y * CONFIG_MENU_BUTTON_3 ) );
	// =====================================
}

void MainMenuState::pause()
{
}

void MainMenuState::resume()
{
	restartStateClock();
}

void MainMenuState::buttonCollisionDetectRespond( void ) noexcept
{
	// DETECT CURSOR & BUTTON COLLISION
	m_mousePos = sf::Mouse::getPosition( m_window );

	// MenuButton: Play ====================
	if ( sf::Mouse::getPosition( m_window ).x > m_sprPlay.getGlobalBounds().left
	     && sf::Mouse::getPosition( m_window ).x < ( m_sprPlay.getGlobalBounds().left + m_sprPlay.getGlobalBounds().width )
	     && sf::Mouse::getPosition( m_window ).y > m_sprPlay.getGlobalBounds().top
	     && sf::Mouse::getPosition( m_window ).y < ( m_sprPlay.getGlobalBounds().top + m_sprPlay.getGlobalBounds().height ) ) {
		m_textPlay.setCharacterSize( 36u );
		centerOrigin( m_textPlay );
		m_textPlay.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y * CONFIG_MENU_BUTTON_1 ) );
		m_sprPlayButtonHot = true;
		if ( m_sprPlayNeedSFX ) {
			m_sMouseOver.play();
			m_sprPlayNeedSFX = false;
		}
	} else {
		m_sprPlayButtonHot = false;
		m_sprPlayNeedSFX = true;
		m_textPlay.setCharacterSize( 28u );
		centerOrigin( m_textPlay );
		m_textPlay.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y * CONFIG_MENU_BUTTON_1 ) );
	}
	// =====================================

	// MenuButton: Credits =================
	if ( sf::Mouse::getPosition( m_window ).x > m_sprCredits.getGlobalBounds().left
	     && sf::Mouse::getPosition( m_window ).x < ( m_sprCredits.getGlobalBounds().left + m_sprCredits.getGlobalBounds().width )
	     && sf::Mouse::getPosition( m_window ).y > m_sprCredits.getGlobalBounds().top
	     && sf::Mouse::getPosition( m_window ).y < ( m_sprCredits.getGlobalBounds().top + m_sprCredits.getGlobalBounds().height ) ) {
		m_textCredits.setCharacterSize( 36u );
		centerOrigin( m_textCredits );
		m_textCredits.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y * CONFIG_MENU_BUTTON_2 ) );
		m_sprCreditsButtonHot = true;
		if ( m_sprCreditsNeedSFX ) {
			m_sMouseOver.play();
			m_sprCreditsNeedSFX = false;
		}
	} else {
		m_sprCreditsButtonHot = false;
		m_sprCreditsNeedSFX = true;
		m_textCredits.setCharacterSize( 28u );
		centerOrigin( m_textCredits );
		m_textCredits.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y * CONFIG_MENU_BUTTON_2 ) );
	}
	// =====================================

	// MenuButton: Quit ====================
	if ( sf::Mouse::getPosition( m_window ).x > m_sprQuit.getGlobalBounds().left
	     && sf::Mouse::getPosition( m_window ).x < ( m_sprQuit.getGlobalBounds().left + m_sprQuit.getGlobalBounds().width )
	     && sf::Mouse::getPosition( m_window ).y > m_sprQuit.getGlobalBounds().top
	     && sf::Mouse::getPosition( m_window ).y < ( m_sprQuit.getGlobalBounds().top + m_sprQuit.getGlobalBounds().height ) ) {
		m_textQuit.setCharacterSize( 36u );
		centerOrigin( m_textQuit );
		m_textQuit.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y * CONFIG_MENU_BUTTON_3 ) );
		m_sprQuitButtonHot = true;
		if ( m_sprQuitNeedSFX ) {
			m_sMouseOver.play();
			m_sprQuitNeedSFX = false;
		}
	} else {
		m_sprQuitButtonHot = false;
		m_sprQuitNeedSFX = true;
		m_textQuit.setCharacterSize( 28u );
		centerOrigin( m_textQuit );
		m_textQuit.setPosition( ( m_worldView.getSize().x / 2 ), ( m_worldView.getSize().y * CONFIG_MENU_BUTTON_3 ) );
	}
	// =====================================
}

void MainMenuState::update()
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
		// however, if just entered this state (i.e.: this is the 2nd updateStats), then immediately update
		if ( m_urgentUpdateNeeded > 0 ) {
			// update now!
			--m_urgentUpdateNeeded;
			updateDebugOverlayTextIfEnabled();
			printConsoleDebugIfEnabled();
			m_urgentUpdateNeeded = false;
		}
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
		}
	}
	this->buttonCollisionDetectRespond();
}

void MainMenuState::draw()
{
	m_window.clear();

	if ( SETTINGS->inGameOverlay ) {
		m_window.draw( m_statisticsText );
	}
	m_window.	draw(	m_sprPlay );
	m_window.	draw(	m_textPlay );
	m_window.	draw(	m_sprCredits );
	m_window.	draw(	m_textCredits );
	m_window.	draw(	m_sprQuit );
	m_window.	draw(	m_textQuit );

	m_window.display();
}

void MainMenuState::processEvents()
{
	// fetch events
	sf::Event evt;

	// process events
	while ( m_window.pollEvent( evt ) ) {
		switch ( evt.type ) {
			case sf::Event::Closed:
				std::cout << "Quitting on close event. Goodbye!\n";
				m_machine.quit();
			case sf::Event::MouseButtonPressed:
				if ( m_sprPlayButtonHot ) {
					m_sMouseClicked.play();
					m_next = StateMachine::build <PlayState> ( m_machine, m_window, true );
					break;
				} else if ( m_sprCreditsButtonHot ) {
					m_sMouseClicked.play();
					m_next = StateMachine::build <PlayState> ( m_machine, m_window, true );
					break;
				} else if ( m_sprQuitButtonHot ) {
					std::cout << "Quitting on mouse click. Goodbye!\n";
					m_sMouseClicked.play();
					m_machine.quit();
					break;
				}
				break;
			case sf::Event::KeyPressed:
				switch ( evt.key.code ) {
					case sf::Keyboard::Space:
						m_next = StateMachine::build <PlayState> ( m_machine, m_window, true );
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
					case sf::Keyboard::Q:
						std::cout << "Quitting on Q key press. Goodbye!\n";
						m_machine.quit();
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

