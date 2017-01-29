/* snake.h */

#ifndef SNAKE_H
#define SNAKE_H

#include "config.h"
// needed for collision detection/boundingbox
#include "common.h"
#include "fruit.h"
#include "cell.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// required for RNG
#include <random>
// required for RNG
#include <chrono>
#include <iostream>
// container to store snakeCells
#include <deque>

class Snake : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		Snake();
		virtual ~Snake();
		void	update( sf::Time timeSinceLastUpdate );
		void	draw( sf::RenderTarget &target, sf::RenderStates states ) const;
		void	startNewGame();
		void	newSnake();
		void	collisionDetectRespond( void ) noexcept;
		float	getX()       const noexcept;
		float	getY()       const noexcept;
		void	processHumanDirectionKeypress();

	protected:

	private:
		enum	{
			DIRECTIONNONE = 0,
			DIRECTIONLEFT,
			DIRECTIONRIGHT,
			DIRECTIONUP,
			DIRECTIONDOWN
		};
		unsigned short int		m_snakeDirection = DIRECTIONNONE;
		bool				m_snakeMustDie = false;
		signed short int		m_snakeMoveAccumulator = 0;
		unsigned short int		m_snakeHeadPositionId = 0;
		sf::Sound			m_soundAteFruit;
		sf::SoundBuffer			m_bufferAteFruit;
		sf::Sound			m_soundBlip1;
		sf::SoundBuffer			m_bufferBlip1;
		std::deque <unsigned short int>	m_snakeCells;
};

#endif	// SNAKE_H

/* EOF */

