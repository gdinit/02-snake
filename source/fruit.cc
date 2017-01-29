/* fruit.cc */

#include "fruit.h"

// TODO: REMOVE THIS DEBUG-ONLY
// #include <iostream>

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Snake>		snake;
// needed for collision detection/boundingbox
extern std::unique_ptr <Common>		common;
extern std::unique_ptr <Cell>		cell;

Fruit::Fruit()
{
}

Fruit::~Fruit() {}

void Fruit::createNewFruit()
{
	// ****************************************
	// REPOSITION THE FRUIT
	// TODO: move this to fruit class && TODO: move this to a separate function
	// ****************************************
	++m_fruitID;

	// TODO: convert this fruidID-text-update to a function
	m_textFruitID.setString( std::to_string( m_fruitID ) );
	centerOrigin( m_textFruitID );
	m_textFruitID.setPosition( ( getX() + 20 ), ( getY() + 20 ) );

	signed short int			fruitNewCell;
	fruitNewCell = -9999;

	// set up RNG
	std::mt19937				mt1;
	auto					seed1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	mt1.seed( ( unsigned long )seed1 );
	// TODO remove hardcoded 115 and improve ranposgen code
	std::uniform_real_distribution <>	dist1( 115, ( CONFIG_ROWS * CONFIG_COLUMNS ) );

	unsigned short int			candidateCell = 0;

	do {
		// NEW CELL
		candidateCell = static_cast <unsigned short int> ( dist1( mt1 ) );
	} while ( cell->m_cellDetailsDatabase.at( candidateCell ).cellCurrentContent != 0 );

	cell->m_cellDetailsDatabase.at( candidateCell ).cellCurrentContent = 3;
}

void Fruit::setFruitIdToZero()
{
	m_fruitID = 0;
}

void Fruit::update( sf::Time timeSinceLastUpdate )
{
}

void Fruit::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
}

float Fruit::getX() const noexcept { return m_fruitSprite.getPosition().x; }

float Fruit::getY() const noexcept { return m_fruitSprite.getPosition().y; }

/* EOF */

