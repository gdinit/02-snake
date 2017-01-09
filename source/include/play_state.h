/* play_state.h */

#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <include/state.h>
#include <include/state_machine.h>
#include <include/main_menu_state.h>
#include <include/ingame_menu_state.h>
#include <include/pause_state.h>
#include <include/config.h>
// needed for centerOrigin
#include <include/utility.h>
#include <include/make_unique.h>
#include <include/game_objects.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

// to in-line document
// needed for std::unique_ptr
#include <memory>

// TODO REMOVE THIS
// needed for debugging
#include <iostream>

// #include <stdlib.h>

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class PlayState : public State
{
	public:
		PlayState( StateMachine &	machine,
		sf::RenderWindow &		window,
		bool				replace = true );
		void	initializeState();
		void	processEvents();
		void	update();
		void	draw();
		void	pause();
		void	resume();
		void	restartPregameAnimationClock();
		void	playPreGameAnimation();
		float	getPreGameAnimationAgeAsSeconds();

	private:
		bool m_nextThrowTowardsRight;

		// TESTING ====================
		struct CellStatus
		{
			unsigned char nextNodeDirection;
			bool isSnake;
			bool isFood;
		};

		sf::Texture			m_texturePak;
		std::vector <sf::Sprite>	m_cellSprite;
		std::vector <CellStatus>	m_cellState;

		// sf::Clock			m_pregameAnimationClock;
		sf::Clock			m_animationClock;
		sf::Time			m_animationAge;
		sf::Text			m_preGameAnimationStep1Text;
		sf::Text			m_preGameAnimationStep2Text;
		sf::Text			m_preGameAnimationStep3Text;
		sf::Text			m_preGameAnimationStep4Text;
		sf::SoundBuffer			m_sbBlip2;
		sf::Sound			m_sBlip2;
};

#endif	// PLAY_STATE_H

/* EOF */

