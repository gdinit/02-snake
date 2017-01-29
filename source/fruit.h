/* fruit.h */

#ifndef FRUIT_H
#define FRUIT_H

#include "snake.h"
#include "config.h"
// needed for collision detection/boundingbox
#include "common.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// required for RNG
#include <random>
// required for RNG
#include <chrono>

class Fruit : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		Fruit();

		virtual ~Fruit();

		void	update( sf::Time timeSinceLastUpdate );
		void	draw( sf::RenderTarget &target, sf::RenderStates states ) const;
		void	createNewFruit();
		void	setFruitIdToZero();
		// float	getTop()     const noexcept;
		// float	getBottom()  const noexcept;
		// float	getLeft()    const noexcept;
		// float	getRight()   const noexcept;

	protected:
		friend class Snake;	// Snake now can see the internals of Fruit

	private:
		float	getX()       const noexcept;
		float	getY()       const noexcept;
		sf::Sprite	m_fruitSprite;
		sf::Texture	m_fruitTexture;
		float		m_distanceResult = -1;
		sf::Font	m_fontFruitID;
		sf::Text	m_textFruitID;
		signed int	m_fruitID = -9999;
		unsigned int	m_lastFruitCell = 9999;
};

#endif	// FRUIT_H

/* EOF */

