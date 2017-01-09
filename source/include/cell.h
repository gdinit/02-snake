/* cell.h */

#ifndef CELL_H
#define CELL_H

#include <include/config.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>

#include <iostream>

class Cell : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		Cell();
		virtual ~Cell();
		void	update( sf::Time timeSinceLastUpdate );
		void	draw( sf::RenderTarget &target, sf::RenderStates states ) const;
		void	newRound();

	protected:
		friend class Snake;	// Snake now can see the internals of Cell	// TODO consider removing this?
		friend class Fruit;	// Fruit now can see the internals of Cell	// TODO consider removing this?

	private:
		enum	{
			EMPTY = 0,
			BORDER,	// 1
			SNAKE,	// 2
			FRUIT,	// 3
			OBSTACLE,// 4
			HUD,	// 5
			DEBUGMARKED	// 6
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

