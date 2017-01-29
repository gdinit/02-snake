/* play_state.cc */

#include "play_state.h"

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Snake>		snake;
extern std::unique_ptr <Fruit>		fruit;
extern std::unique_ptr <Cell>		cell;
extern std::unique_ptr <Common>		common;

PlayState::PlayState( StateMachine &machine, sf::RenderWindow &window, bool replace ) : State{ machine, window, replace }
{
	initializeState();
}

void PlayState::initializeState()
{
	restartStateClock();
	m_justResumed = false;
	m_worldView = m_window.getDefaultView();
	m_urgentUpdateNeeded = 10;

	restartPregameAnimationClock();
	GLOBALS->preGameAnimationNeeded = true;

	// debug overlay font
	m_font.loadFromFile( "assets/fonts/sansation.ttf" );
	m_statisticsText.setFont( m_font );
	m_statisticsText.setPosition( 5.f, 5.f );
	m_statisticsText.setCharacterSize( 12u );
	m_statisticsText.setFillColor( sf::Color::White );
	updateDebugOverlayTextIfEnabled( true );

	// PREGAME ANIMATION
	// anim stage 1
	m_preGameAnimationStep1Text.setFont( m_font );
	m_preGameAnimationStep1Text.setCharacterSize( 60u );
	m_preGameAnimationStep1Text.setFillColor( sf::Color::White );
	m_preGameAnimationStep1Text.setString( "3" );
	centerOrigin( m_preGameAnimationStep1Text );
	m_preGameAnimationStep1Text.setPosition( CONFIG_PREGAME_ANIMATION_POS_X, CONFIG_PREGAME_ANIMATION_POS_Y );
	// anim stage 2
	m_preGameAnimationStep2Text.setFont( m_font );
	m_preGameAnimationStep2Text.setCharacterSize( 60u );
	m_preGameAnimationStep2Text.setFillColor( sf::Color::White );
	m_preGameAnimationStep2Text.setString( "2" );
	centerOrigin( m_preGameAnimationStep2Text );
	m_preGameAnimationStep2Text.setPosition( CONFIG_PREGAME_ANIMATION_POS_X, CONFIG_PREGAME_ANIMATION_POS_Y );
	// anim stage 3
	m_preGameAnimationStep3Text.setFont( m_font );
	m_preGameAnimationStep3Text.setCharacterSize( 60u );
	m_preGameAnimationStep3Text.setFillColor( sf::Color::White );
	m_preGameAnimationStep3Text.setString( "1" );
	centerOrigin( m_preGameAnimationStep3Text );
	m_preGameAnimationStep3Text.setPosition( CONFIG_PREGAME_ANIMATION_POS_X, CONFIG_PREGAME_ANIMATION_POS_Y );
	// anim stage 4
	m_preGameAnimationStep4Text.setFont( m_font );
	m_preGameAnimationStep4Text.setCharacterSize( 60u );
	m_preGameAnimationStep4Text.setFillColor( sf::Color::White );
	m_preGameAnimationStep4Text.setString( "Go!" );
	centerOrigin( m_preGameAnimationStep4Text );
	m_preGameAnimationStep4Text.setPosition( CONFIG_PREGAME_ANIMATION_POS_X, CONFIG_PREGAME_ANIMATION_POS_Y );

	// SOUNDS
	if ( !m_sbBlip2.loadFromFile( "assets/sounds/blip1.wav" ) ) {
	}
	m_sBlip2.setBuffer( m_sbBlip2 );

	// start a new game
	snake->startNewGame();
	// CELL WILL BE CALLED BY SNAKE // cell->newRound();
	// FRUIT WILL BE CALLED BY SNAKE // fruit->startFromZero();//keep at bottom
}

void PlayState::pause()
{
}

void PlayState::resume()
{
	restartStateClock();
	m_urgentUpdateNeeded = 10;
	// destroy the queue
	m_justResumed = true;
	// give me stats in the first frame, but first make up some plausible values
	updateDebugOverlayTextIfEnabled( true );
}

void PlayState::update()
{
	if ( GLOBALS->mustDie ) {
		exit( EXIT_FAILURE );
		// m_machine.quit();
	}

	sf::Time m_elapsedTime = m_clock.restart();
	m_timeSinceLastUpdate += m_elapsedTime;

	// if returning from pause(), let's jump in time to prevent slow catchup process
	if ( m_justResumed ) {
		m_timeSinceLastUpdate = TimePerFrame;
	}

	while ( m_timeSinceLastUpdate > State::TimePerFrame ) {
		m_timeSinceLastUpdate -= State::TimePerFrame;

		processEvents();

		common->update( m_elapsedTime );
		snake->update( m_elapsedTime );
		fruit->update( m_elapsedTime );
		cell->update( m_elapsedTime );
		if ( GLOBALS->mustMainMenu == true ) {
			// go to main menu immediately (all lives lost)
			m_next = StateMachine::build <MainMenuState> ( m_machine, m_window, true );
		}

		// update statistics for the debug overlay
		m_statisticsUpdateTime += m_elapsedTime;
		m_statisticsNumFrames += 1;
		// update statsText only once a second
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
	m_justResumed = false;
}

void PlayState::processEvents()
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
				switch ( evt.key.code ) {
					case sf::Keyboard::Escape:
						// InGameMenuState is commented out for the time being and replaced with PauseState
						// m_next = StateMachine::build <InGameMenuState> ( m_machine, m_window, false );
						m_next = StateMachine::build <PauseState> ( m_machine, m_window, false );
						break;
					case sf::Keyboard::Pause:
					case sf::Keyboard::P:
						m_next = StateMachine::build <PauseState> ( m_machine, m_window, false );
						break;
					case sf::Keyboard::Q:
						std::cout << "Quitting on Q key press. Goodbye!\n";
						m_machine.quit();
						break;
					case sf::Keyboard::M:
						m_next = StateMachine::build <MainMenuState> ( m_machine, m_window, true );
						break;
					case sf::Keyboard::Left:
					case sf::Keyboard::A:
						if ( !GLOBALS->preGameAnimationRunning ) {
							GLOBALS->moveLeftRequestActive = true;
						}
						break;
					case sf::Keyboard::Right:
					case sf::Keyboard::D:
						if ( !GLOBALS->preGameAnimationRunning ) {
							GLOBALS->moveRightRequestActive = true;
						}
						break;
					case sf::Keyboard::Up:
					case sf::Keyboard::W:
						if ( !GLOBALS->preGameAnimationRunning ) {
							GLOBALS->moveUpRequestActive = true;
						}
						break;
					case sf::Keyboard::Down:
					case sf::Keyboard::S:
						if ( !GLOBALS->preGameAnimationRunning ) {
							GLOBALS->moveDownRequestActive = true;
						}
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
			case sf::Event::KeyReleased:
				switch ( evt.key.code ) {
					case sf::Keyboard::Left:
					case sf::Keyboard::A:
						GLOBALS->moveLeftRequestActive = false;
						break;
					case sf::Keyboard::Right:
					case sf::Keyboard::D:
						GLOBALS->moveRightRequestActive = false;
						break;
					case sf::Keyboard::Up:
					case sf::Keyboard::W:
						GLOBALS->moveUpRequestActive = false;
						break;
					case sf::Keyboard::Down:
					case sf::Keyboard::S:
						GLOBALS->moveDownRequestActive = false;
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

void PlayState::restartPregameAnimationClock()
{
	m_animationClock.restart();
	m_animationAge = m_animationClock.restart();
	// std::cout << "m_animationClock.restart() triggered!\t\tm_animationAge is:" << m_animationAge << "\n";	// TODO REMOVE THIS
}

float PlayState::getPreGameAnimationAgeAsSeconds()
{
	sf::Time	tmp = sf::Time::Zero;

	tmp = m_animationClock.getElapsedTime();
	float		val = -1.f;

	// we don't need this -- adding just to quiet cppcheck!
	val = val - 1;
	val = tmp.asSeconds();

	return val;
}

void PlayState::playPreGameAnimation()
{
	/*
	********************************************************************************
	Each step to be displayed for 1 second:
	preGameAnimationStep1Needed	"3"
	preGameAnimationStep2Needed	"2"
	preGameAnimationStep3Needed	"1"
	preGameAnimationStep4Needed	"Go!"
	********************************************************************************
	*/
	if ( getPreGameAnimationAgeAsSeconds() <= CONFIG_PREGAME_ANIMATION_STEP_DURATION * 1 ) {
		GLOBALS->preGameAnimationRunning = true;
		m_window.draw( m_preGameAnimationStep1Text );
		if ( GLOBALS->preGameAnimationStep1SFXNeeded ) {
			m_sBlip2.play();
			GLOBALS->preGameAnimationStep1SFXNeeded = false;
		}
		;
	} else if ( getPreGameAnimationAgeAsSeconds() <= CONFIG_PREGAME_ANIMATION_STEP_DURATION * 2 ) {
		m_window.draw( m_preGameAnimationStep2Text );
		if ( GLOBALS->preGameAnimationStep2SFXNeeded ) {
			m_sBlip2.play();
			GLOBALS->preGameAnimationStep2SFXNeeded = false;
		}
		;
	} else if ( getPreGameAnimationAgeAsSeconds() <= CONFIG_PREGAME_ANIMATION_STEP_DURATION * 3 ) {
		m_window.draw( m_preGameAnimationStep3Text );
		if ( GLOBALS->preGameAnimationStep3SFXNeeded ) {
			m_sBlip2.play();
			GLOBALS->preGameAnimationStep3SFXNeeded = false;
		}
		;
	} else if ( getPreGameAnimationAgeAsSeconds() <= CONFIG_PREGAME_ANIMATION_STEP_DURATION * 4 ) {
		GLOBALS->preGameAnimationRunning = false;
		m_window.draw( m_preGameAnimationStep4Text );
		if ( GLOBALS->preGameAnimationStep4SFXNeeded ) {
			m_sBlip2.play();
			GLOBALS->preGameAnimationStep4SFXNeeded = false;
		}
		;
	} else if ( getPreGameAnimationAgeAsSeconds() >= CONFIG_PREGAME_ANIMATION_STEP_DURATION * 5 ) {
		GLOBALS->preGameAnimationNeeded = false;

		// clear 'SFXNeeded's
		GLOBALS->preGameAnimationStep1SFXNeeded = true;
		GLOBALS->preGameAnimationStep2SFXNeeded = true;
		GLOBALS->preGameAnimationStep3SFXNeeded = true;
		GLOBALS->preGameAnimationStep4SFXNeeded = true;
	}
}

void PlayState::draw()
{
	m_window.clear();

	cell->draw( m_window, sf::RenderStates::Default );
	common->draw( m_window, sf::RenderStates::Default );
	snake->draw( m_window, sf::RenderStates::Default );
	fruit->draw( m_window, sf::RenderStates::Default );
	if ( GLOBALS->preGameAnimationNeeded ) {
		playPreGameAnimation();
	}
	if ( SETTINGS->inGameOverlay ) {
		m_window.draw( m_statisticsText );
	}

	m_window.display();
}

/* EOF */

