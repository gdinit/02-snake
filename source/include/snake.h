/* snake.h */

#ifndef SNAKE_H
#define SNAKE_H

#include <include/config.h>
// needed for collision detection/boundingbox
#include <include/common.h>
#include <include/fruit.h>
#include <include/cell.h>

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
		bool				m_snakeMustDie;
		enum	{
			DIRECTIONNONE = 0,
			DIRECTIONLEFT,
			DIRECTIONRIGHT,
			DIRECTIONUP,
			DIRECTIONDOWN
		};
		signed short int		m_snakeMoveAccumulator;
		unsigned short int		m_snakeHeadPositionId;
		unsigned short int		m_snakeDirection;
		sf::Sound			m_soundAteFruit;
		sf::SoundBuffer			m_bufferAteFruit;
		sf::Sound			m_soundBlip1;
		sf::SoundBuffer			m_bufferBlip1;
		std::deque <unsigned short int>	m_snakeCells;
};

#endif	// SNAKE_H

/* EOF */

