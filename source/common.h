/* common.h */

// Class to cover common objects between play & pause states
// e.g.: background, borders, top text (score, lives, snakename)
//
// Note that all main objects (such as snakeObject, foodObject, wallObject)
// are each defined in their own class files, and instantiated via global
// unique_ptr

#ifndef  COMMON_H
#define  COMMON_H

#include "config.h"
#include "globals.h"
// needed for centerOrigin
#include "utility.h"
#include "game_objects.h"

#include <SFML/Graphics.hpp>

class Common : public sf::Transformable, public sf::Drawable, private
	     sf::NonCopyable
{
	public:
		Common();
		virtual ~Common();
		void		update( sf::Time timeSinceLastUpdate );
		virtual void	draw( sf::RenderTarget &target, sf::RenderStates
		states ) const;

	protected:
		friend class Snake;	// Snake now can see the internals of
					// Common
		sf::RectangleShape	m_playAreaBarTop;
		sf::RectangleShape	m_playAreaBarBottom;
		sf::RectangleShape	m_playAreaBarLeft;
		sf::RectangleShape	m_playAreaBarRight;

	private:
		sf::Font		m_topTextFont;
		sf::Text		m_topText;
		sf::Vector2i		m_screenSize;

		sf::Texture		m_texturePak;
		sf::Sprite		m_blueBackground;
};

#endif	// COMMON_H

/* EOF */

