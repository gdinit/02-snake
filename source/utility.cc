/* utility.cc */

#include "utility.h"

void centerOrigin( sf::Text &text )
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin( std::floor( bounds.left + bounds.width / 2.f )
		, std::floor( bounds.top + bounds.height / 2.f ) );
}

/* EOF */

