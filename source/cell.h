/* cell.h */

#ifndef CELL_H
#define CELL_H

#include "config.h"
#include "game_objects.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>

#include <iostream>

class Cell : public sf::Transformable, public sf::Drawable, private
	   sf::NonCopyable
{
	public:
		Cell();
		virtual ~Cell();
		void	update( sf::Time timeSinceLastUpdate );
		void	draw( sf::RenderTarget &target, sf::RenderStates
		states ) const;
		void	newRound();

	protected:
		friend class Snake;
		friend class Fruit;

	private:
		enum	{
			EMPTY = 0
			, BORDER// 1
			, SNAKE	// 2
			, FRUIT	// 3
			, OBSTACLE	// 4
			, HUD	// 5
			, DEBUGMARKED	// 6
		};
		struct CellDetails
		{
			unsigned short int cellNumericId;
			unsigned short int cellCurrentContent;
		};
		std::vector <CellDetails>	m_cellDetailsDatabase;
		std::vector <sf::Sprite>	m_cellSpriteDatabase;
		sf::Texture			m_squareTexture;
};

#endif	// CELL_H

/* EOF */

