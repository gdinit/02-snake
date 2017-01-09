/* pausestate.h */

#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include <include/state.h>
#include <include/state_machine.h>
#include <include/config.h>
#include <include/globals.h>
// needed for centerOrigin
#include <include/utility.h>
#include <include/game_objects.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

// for FPS text
#include <string>

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class PauseState : public State
{
	public:
		PauseState( StateMachine &machine, sf::RenderWindow &window, bool replace = true );
		void	initializeState();
		void	processEvents();
		void	update();
		void	draw();
		void	pause();
		void	resume();

	private:
		sf::Font	m_fontPressToContinue;
		sf::Text	m_textPressToContinue;
		sf::Font	m_fontPressToContinueLine2;
		sf::Text	m_textPressToContinueLine2;
};

#endif	// PAUSE_STATE_H

/* EOF */

