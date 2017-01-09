/* application.h */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <include/intro_state.h>
#include <include/state_machine.h>
#include <include/config.h>
#include <include/globals.h>

#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
	public:
		Application();
		void	loadSettings();
		void	loadGlobals();
		void	run();

	private:
		StateMachine		m_machine;
		sf::RenderWindow	m_window;
};

#endif	// APPLICATION_H

/* EOF */

