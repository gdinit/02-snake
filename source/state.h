/* state.h */

#ifndef STATE_H
#define STATE_H

// make configuration values to all derived classes
#include "config.h"
// forward declare Settings struct
#include "globals.h"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

// needed for consoleDebugOut cout
#include <iostream>
// needed for unique_ptr
#include <memory>
// container to store observedFPS last N values
#include <deque>
// needed for round()
#include <cmath>

// extern Settings	SETTINGS;
// extern Globals	GLOBALS;
// extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Settings> SETTINGS;

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class State
{
	public:
		State( StateMachine &machine
		, sf::RenderWindow &window,         bool replace = true );

		virtual ~State() = default;

		State( const State & ) = delete;

		State & operator	=( const State & ) = delete;
		std::unique_ptr <State> next();
		virtual void		update() = 0;
		virtual void		draw() = 0;
		virtual void		pause() = 0;
		virtual void		resume() = 0;
		bool			isReplacing();
		void			toggleDebugShowOverlay();
		void			toggleDebugConsoleOutput();
		void			toggleDebugDynFPSConsoleOutput();
		void			updateDebugOverlayTextIfEnabled( bool
		b );
		void			updateDebugOverlayTextIfEnabled();
		void			printConsoleDebugIfEnabled();
		void			recordObservedFPS();
		void			dynamicallyAdjustFPSLimit();
		unsigned short int	calcMedianFPS( std::deque <unsigned
			short int> records );
		void			restartStateClock();
		int			getStateAgeAsSeconds();

	protected:
		std::unique_ptr <State>		m_next;
		StateMachine &			m_machine;
		sf::RenderWindow &		m_window;
		bool				m_replacing;
		static const sf::Time		TimePerFrame;
		int				m_statisticsNumFrames = 0;
		sf::Time			m_timeSinceLastUpdate;
		sf::Time			m_elapsedTime;
		sf::Clock			m_clock;
		sf::Clock			m_stateBirthdate;
		sf::Time			m_stateAge;
		sf::Font			m_font;
		sf::Text			m_statisticsText;
		sf::Time			m_statisticsUpdateTime;
		unsigned short int		m_urgentUpdateNeeded = 0;
		sf::View			m_worldView;
		std::deque <unsigned short int>	m_observedFPSLastN;
		short int			m_FPSAdjPosDelta = 0;
		short int			m_FPSAdjNegDelta = 0;
		unsigned short int		m_activeFPSLimit =
			CONFIG_DESIRED_FPS_INT;
		bool				m_justResumed = false;
};

#endif	// STATE_H

/* EOF */

