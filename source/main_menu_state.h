/* main_menu_state.h */

#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "state.h"
#include "state_machine.h"
#include "config.h"
// needed for centerOrigin
#include "utility.h"
#include "play_state.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Mouse.hpp>

// for FPS text
#include <string>

class StateMachine;

namespace sf
{
	class RenderWindow;
}

class MainMenuState : public State
{
	public:
		MainMenuState( StateMachine &machine
		, sf::RenderWindow &window,                 bool replace =
			true );
		void	initializeState();
		void	processEvents();
		void	buttonCollisionDetectRespond( void ) noexcept;
		void	update();
		void	draw();
		void	pause();
		void	resume();

	private:
		sf::Texture	m_textureWhite;
		sf::Sprite	m_sprPlay;
		bool		m_sprPlayNeedSFX;
		bool		m_sprPlayButtonHot;
		sf::Font	m_fontPlayText;
		sf::Text	m_textPlay;

		sf::Sprite	m_sprCredits;
		bool		m_sprCreditsNeedSFX;
		bool		m_sprCreditsButtonHot;
		sf::Font	m_fontCreditsText;
		sf::Text	m_textCredits;

		sf::Sprite	m_sprQuit;
		bool		m_sprQuitNeedSFX;
		bool		m_sprQuitButtonHot;
		sf::Font	m_fontQuitText;
		sf::Text	m_textQuit;

		sf::SoundBuffer m_sbMouseOver;
		sf::Sound	m_sMouseOver;
		sf::SoundBuffer m_sbMouseClicked;
		sf::Sound	m_sMouseClicked;

		sf::Vector2i	m_mousePos;
};

#endif	// MAIN_MENU_STATE_H

/* EOF */

