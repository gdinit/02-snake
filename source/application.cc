/* application.cc */

#include "application.h"

extern std::unique_ptr <Globals> GLOBALS;

Application::Application()
{
}

void Application::run()
{
	loadSettings();
	loadGlobals();

	// Create render window
	// TODO import the latest improved window creation code from my space-flight demo
	sf::ContextSettings windowSettings;
	windowSettings.antialiasingLevel = 8;
	m_window.create( sf::VideoMode { CONFIG_WIN_WIDTH, CONFIG_WIN_HEIGHT }, CONFIG_WINDOW_TITLE_TEXT, sf::Style::Default, windowSettings );
	m_window.setFramerateLimit( CONFIG_DESIRED_FPS_INT );
	m_window.setKeyRepeatEnabled( false );

	m_machine.run( StateMachine::build <IntroState> ( m_machine, m_window, true ) );

	// Main Loop
	while ( m_machine.running() ) {
		m_machine.nextState();
		m_machine.update();
		m_machine.draw();
	}
}

void Application::loadSettings()
{
	SETTINGS->inGameOverlay = CONFIG_DEBUG_SHOW_OVERLAY;
	SETTINGS->debugPrintToConsole = CONFIG_DEBUG_CONSOLE_OUTPUT;
	SETTINGS->debugPrintToConsoleFPS = CONFIG_DEBUG_DYNFPS_CONSOLE_OUTPUT;
	SETTINGS->playAreaTopLine = CONFIG_BORDER_THICKNESS;
	SETTINGS->playAreaBottomLine = CONFIG_WIN_HEIGHT - CONFIG_BORDER_THICKNESS;
	SETTINGS->playAreaLeftLine = CONFIG_BORDER_THICKNESS;
	SETTINGS->playAreaRightLine = CONFIG_WIN_WIDTH - CONFIG_BORDER_THICKNESS;
	SETTINGS->currentScreenSizeWidth = CONFIG_WIN_WIDTH;
	SETTINGS->currentScreenSizeHeight = CONFIG_WIN_HEIGHT;
	// NEW IN SNAKE
	SETTINGS->snakeSpeed = CONFIG_SNAKE_SPEED;
}

void Application::loadGlobals()
{
	GLOBALS->moveUpRequestActive = false;
	GLOBALS->moveDownRequestActive = false;
	// NEW IN SNAKE
	GLOBALS->livesLeft = CONFIG_SNAKE_MAX_LIVES;
	GLOBALS->currentScore = 0;
}

/* EOF */

