/* state_machine.h */

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "state.h"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

// needed for unique_ptr
#include <memory>
// needed to store stack of game states
#include <stack>
// TODO: why is this here?
#include <string>

class State;

namespace sf
{
	class RenderWindow;
}

class StateMachine
{
	public:
		StateMachine();

		void				run( std::unique_ptr <State> state );

		void				nextState();
		void				lastState();

		void				update();
		void				draw();

		bool running() { return m_running; }

		void quit() { m_running = false; }

		template<typename T>
		static std::unique_ptr <T>	build( StateMachine &	machine,
		sf::RenderWindow &					window,
		bool							replace = true );

	private:
		// The stack of states
		std::stack <std::unique_ptr <State> >	m_states;

		bool					m_resume;
		bool					m_running;
};

template<typename T>
std::unique_ptr <T> StateMachine::build( StateMachine & machine,
	sf::RenderWindow &				window,
	bool						replace )
{
	return std::unique_ptr <T> ( new T( machine, window, replace ) );
}

#endif	// STATE_MACHINE_H

/* EOF */

