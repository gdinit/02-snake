/* common.cc */

#include "common.h"

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;

Common::Common()
{
	// TOP TEXT
	m_topTextFont.loadFromFile( "assets/fonts/sansation.ttf" );
	m_topText.setFont( m_topTextFont );
	m_topText.setPosition( 460, 9 );
	m_topText.setCharacterSize( 18u );
	m_topText.setFillColor( sf::Color::White );

	m_topText.setString( "SAMMY-->     Lives: " + std::to_string( GLOBALS->livesLeft ) + "                       " + std::to_string( GLOBALS->currentScore ) + "  " );
	centerOrigin( m_topText );
}

Common::~Common()
{
}

void Common::update( sf::Time timeSinceLastUpdate )
{
	m_topText.setString( "SAMMY-->     Lives: " + std::to_string( GLOBALS->livesLeft ) + "                       " + std::to_string( GLOBALS->currentScore ) + "  " );
	centerOrigin( m_topText );
}

void Common::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	// target. draw(	m_blueBackground );
	// target. draw(	m_playAreaBorder );
	target.draw( m_topText );
}

/* EOF */

