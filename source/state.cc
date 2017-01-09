/* state.cc */

#include <include/state.h>

const sf::Time State::TimePerFrame = sf::seconds( 1.f / CONFIG_DESIRED_FPS_FLOAT );

State::State( StateMachine &	machine,
	sf::RenderWindow &	window,
	bool			replace )
	: m_machine{ machine }
	, m_window{ window }
	, m_replacing{ replace }
{
}

std::unique_ptr <State> State::next()
{
	return std::move( m_next );
}

bool State::isReplacing()
{
	return m_replacing;
}

void State::toggleDebugShowOverlay()
{
	if ( SETTINGS->inGameOverlay == true ) {
		SETTINGS->inGameOverlay = false;
		// destroy the text
		m_statisticsText.setString( "" );
	} else if ( SETTINGS->inGameOverlay == false ) {
		SETTINGS->inGameOverlay = true;
		// immediately ugenerate some values
		updateDebugOverlayTextIfEnabled( true );// give me stats in the first frame, but first make up some plausible values
	}
	std::cout << "DebugOverlay\t[" << SETTINGS->inGameOverlay << "]\n";
}

void State::toggleDebugConsoleOutput()
{
	SETTINGS->debugPrintToConsole = !SETTINGS->debugPrintToConsole;
	std::cout << "Console debug\t[" << SETTINGS->debugPrintToConsole << "]\n";
}

void State::toggleDebugDynFPSConsoleOutput()
{
	SETTINGS->debugPrintToConsoleFPS = !SETTINGS->debugPrintToConsoleFPS;
	std::cout << "debugPrintToConsoleFPS\t[" << SETTINGS->debugPrintToConsoleFPS << "]\n";
}

void State::updateDebugOverlayTextIfEnabled( bool b )
{
	if ( SETTINGS->inGameOverlay ) {
		if ( b ) {
			// do fabricate the initial values
			int short	n = CONFIG_DESIRED_FPS_INT;
			int long	mil = 1000000;
			m_statisticsText.setString( std::to_string( n ) + " FPS \n" +
						    std::to_string( mil / n ) + "us\n" );
		} else {
			updateDebugOverlayTextIfEnabled();
		}
	}
}

// update the overlay text
void State::updateDebugOverlayTextIfEnabled()
{
	// we should not update for `too young` states or it will print values like 13084738473 FPS!
	if ( SETTINGS->inGameOverlay && ( getStateAgeAsSeconds() >= CONFIG_FPS_OVERLAY_MIN_AGE_TO_UPDATE_SECONDS_INT ) ) {
		m_statisticsText.setString( std::to_string( m_statisticsNumFrames ) + " FPS \n" +
					    std::to_string( m_statisticsUpdateTime.asMicroseconds() / m_statisticsNumFrames ) + "us\n" );
	}
}

void State::printConsoleDebugIfEnabled()
{
	if ( SETTINGS->debugPrintToConsole ) {
		std::cout << "FPS: " + std::to_string( m_statisticsNumFrames ) + "\t" +
			"Time/Update: " + std::to_string( m_statisticsUpdateTime.asMicroseconds() / m_statisticsNumFrames ) + "us\t" +
			"updateTime: " + std::to_string( m_statisticsUpdateTime.asMicroseconds() ) + "us\n";
	}
}

void State::recordObservedFPS()
{
	// proceed only if stateAge is > CONFIG_DYNFPS_TOO_YOUNG_THRESHOLD_SECONDS_INT
	if ( getStateAgeAsSeconds() < CONFIG_DYNFPS_TOO_YOUNG_THRESHOLD_SECONDS_INT ) {
	} else {
		// add the observed fps to the end of the queue
		m_observedFPSLastN.push_back( m_statisticsNumFrames );

		// prevent overgrowth
		while ( m_observedFPSLastN.size() > CONFIG_OBSERVED_FPS_CONTAINER_MAX_SIZE ) {
			m_observedFPSLastN.pop_front();
		}

		// print all values
		if ( SETTINGS->debugPrintToConsoleFPS ) {
			std::cout << "\t<m_observedFPSLastN>: ";
			std::deque <unsigned short int>::iterator it = m_observedFPSLastN.begin();
			while ( it != m_observedFPSLastN.end() ) {
				std::cout << ' ' << *it++;
			}
		}
	}
}

void State::dynamicallyAdjustFPSLimit()
{
	// proceed only if stateAge is > CONFIG_DYNFPS_TOO_YOUNG_THRESHOLD_SECONDS_INT
	if ( getStateAgeAsSeconds() < CONFIG_DYNFPS_TOO_YOUNG_THRESHOLD_SECONDS_INT ) {
	} else {
		// act if there are at least N values in our de-queue
		if ( m_observedFPSLastN.size() >= CONFIG_OBSERVED_FPS_ACT_THRESHOLD ) {
			// get median
			unsigned short int median = calcMedianFPS( m_observedFPSLastN );

			// modify the running FPS limit
			if ( median < CONFIG_DESIRED_FPS_INT ) {
				// our FPS is too low!
				unsigned short int delta = CONFIG_DESIRED_FPS_INT - median;
				// set frameLimit to the delta corrected new value -- for large values go slow
				if ( delta > 10 ) {
					m_activeFPSLimit = m_activeFPSLimit + 10;
					// action only if delta is more than 1
				} else if ( delta < 10 && delta > 1 ) {
					m_activeFPSLimit += delta;
				} else if ( delta == 1 ) {
					// do nothing = allow 1 FPS delta. trying to fix 1 FPS delta causes more harm than good (i.e.: 2 fps or more fps delta!)
					if ( SETTINGS->debugPrintToConsoleFPS ) {
						std::cout << "\t(Delta=1)\tFPSLimit INTACT.\tMedian: " << median << "\t";
					}
				}
				// apply the new frame limit
				m_window.setFramerateLimit( m_activeFPSLimit );
				if ( SETTINGS->debugPrintToConsoleFPS ) {
					std::cout << "\tFPSLimit INCREASED to: " << m_activeFPSLimit << "\tDelta is: " << delta << "\tMedian: " << median << "\t";
				}
				// wipe the container
				m_observedFPSLastN.clear();
			} else if ( median > CONFIG_DESIRED_FPS_INT ) {
				// our FPS is too high!
				unsigned short int delta = median - CONFIG_DESIRED_FPS_INT;
				// set frameLimit to the delta corrected new value -- for large values go slow
				if ( delta > 10 ) {
					m_activeFPSLimit = m_activeFPSLimit - 10;
					// action only if delta is more than 1. trying to fix 1 FPS delta causes more harm than good (i.e.: 2 fps or more fps delta!)
				} else if ( delta < 10 && delta > 1 ) {
					m_activeFPSLimit -= delta;
				} else if ( delta == 1 ) {
					// do nothing = allow 1 FPS delta. trying to fix 1 FPS delta causes more harm than good (i.e.: 2 fps or more fps delta!)
					if ( SETTINGS->debugPrintToConsoleFPS ) {
						std::cout << "\t(Delta=1)\tFPSLimit INTACT.\tMedian: " << median << "\t";
					}
				}
				if ( delta != 1 ) {
					// apply the new frame limit
					m_window.setFramerateLimit( m_activeFPSLimit );
					if ( SETTINGS->debugPrintToConsoleFPS ) {
						std::cout << "\tFPSLimit REDUCED to: " << m_activeFPSLimit << "\tDelta is: " << delta << "\tMedian: " << median << "\t";
					}
					// wipe the container
					m_observedFPSLastN.clear();
				}
			} else if ( median == CONFIG_DESIRED_FPS_INT ) {
				if ( SETTINGS->debugPrintToConsoleFPS ) {
					std::cout << "\t(median==desired)\tFPSLimit INTACT.\tMedian: " << median << "\t";
				}
			}
		}
	}
}

unsigned short int State::calcMedianFPS( std::deque <unsigned short int> records )
{
	int	median;

	size_t	size = records.size();
	sort( records.begin(), records.end() );
	if ( size % 2 == 0 ) {
		median = ( records [ size / 2 - 1 ] + records [ size / 2 ] ) / 2;
	} else {
		median = records [ size / 2 ];
	}

	return median;
}

void State::restartStateClock()
{
	m_stateBirthdate.restart();

	// reset the birth date 2nd time to (almost) zero out the state age. used for dynFPSadj
	m_stateAge = m_stateBirthdate.restart();

	if ( SETTINGS->debugPrintToConsole ) {
		std::cout << "Born!\n";
	}
}

int State::getStateAgeAsSeconds()
{
	sf::Time		tmp = sf::Time::Zero;

	tmp = m_stateBirthdate.getElapsedTime();

	signed short int	n = -1;

	// we don't need this -- adding just to quiet cppcheck!
	n = n - 1;

	n = std::round( tmp.asSeconds() );

	return n;
}

/* EOF */

