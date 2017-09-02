/* cell.cc */

#include "cell.h"

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Cell>		cell;
// extern std::unique_ptr <Fruit>		fruit;

Cell::Cell()
{
	std::cout << "IN PROGRESS: Loading textures...\n";	// TODO remove
								// debug
	// LOAD TEXTURES
	if ( !m_squareTexture.loadFromFile(
		     "assets/textures/texturepak.png" ) ) {
		std::cout << "\nERROR while attempting to load a resource!\n";
		exit( EXIT_FAILURE );
	}
	std::cout << "SUCCESS: Loaded textures.\n";	// TODO remove debug
}

Cell::~Cell() {}

void Cell::newRound()
{
	// CREATE ALL CELLS IN THE DATABASE (cells
	// CONFIG_FIRSTCELL-CONFIG_LASTCELL)
	std::cout << "IN PROGRESS: Creating cells in the database...\n";// TODO
									// remove
									// debug
	m_cellDetailsDatabase.clear();
	m_cellSpriteDatabase.clear();
	unsigned short int rowCounter = 0, curRow = 0, curColumn = 0;
	for ( unsigned short int n = CONFIG_FIRSTCELL; n < CONFIG_LASTCELL;
	      ++n )
	{
		if ( rowCounter == CONFIG_COLUMNS ) {
			curRow++;
			rowCounter = 0;
		}

		curColumn = n % CONFIG_COLUMNS;

		CellDetails		tmprecord;
		unsigned short int	tmpid = n;
		unsigned short int	tmpcontent = 0;

		tmprecord.cellNumericId = tmpid;
		tmprecord.cellCurrentContent = tmpcontent;

		m_cellDetailsDatabase.emplace_back( tmprecord );

		m_cellSpriteDatabase.emplace_back( sf::Sprite(
				m_squareTexture ) );
		m_cellSpriteDatabase [ n ].setPosition(
			static_cast <float> ( curColumn * 16 )
			, ( static_cast <float> ( curRow * 16 ) ) );

		++rowCounter;
	}
	std::cout << "SUCCESS: Created cells in the database.\n";// TODO remove
								// debug

	/////////////////////
	// MARK BORDER CELLS
	/////////////////////

	// TOP
	std::cout << "IN PROGRESS: Marking border cells...\n";
	for ( int n = CONFIG_COLUMNS; n < CONFIG_COLUMNS * 3; n++ )
	{
		m_cellDetailsDatabase.at( n ).cellCurrentContent = 1;
	}

	// BOTTOM
	for ( int n = 0; n < CONFIG_COLUMNS; n++ ) {
		m_cellDetailsDatabase.at( n + ( ( CONFIG_ROWS - 1 ) *
						CONFIG_COLUMNS ) ).
		cellCurrentContent = 1;
	}

	// LEFT
	for ( int n = 0; n < ( CONFIG_ROWS * CONFIG_COLUMNS ); n +=
		      CONFIG_COLUMNS ) {
		m_cellDetailsDatabase.at( n ).cellCurrentContent = 1;
	}

	// RIGHT
	for ( int n = CONFIG_COLUMNS - 1; n < ( CONFIG_ROWS * CONFIG_COLUMNS );
	      n += CONFIG_COLUMNS ) {
		m_cellDetailsDatabase.at( n ).cellCurrentContent = 1;
	}
	std::cout << "COMPLETED: Marked border cells\n";

	/////////////////////////////////////////////
	// HUD WITH SCORE,LIVES ETC. AT TOP OF SCREEN
	std::cout << "IN PROGRESS: Marking HUD cells...\n";
	// hud row 1 of 2
	for ( int n = 0; n < CONFIG_COLUMNS; n++ )
	{
		m_cellDetailsDatabase.at( n ).cellCurrentContent = 5;
	}
	// hud row 2 of 2
	for ( int n = CONFIG_COLUMNS; n < CONFIG_COLUMNS * 2; n++ )
	{
		m_cellDetailsDatabase.at( n ).cellCurrentContent = 5;
	}
	std::cout << "COMPLETED: Marked HUD cells\n";
}

void Cell::update( sf::Time timeSinceLastUpdate )
{
	// blue	(0, 0, 16, 16)) -- empty cells
	// black	(16, 0, 16, 16)) -- not in use
	// white	(32, 0, 16, 16)) -- food
	// red	(48, 0, 16, 16)) -- borders
	// yellow	(64, 0, 16, 16)) -- snake
	// gray	(80, 0, 16, 16)) -- debug marker
	// pink	(96, 0, 16, 16)) -- not in use

	// UPDATE CELL SPRITE DATABASE TO ENSURE IT CONTAINS CORRECT SPRITE FOR
	// EACH CELL
	for ( unsigned short int n = CONFIG_FIRSTCELL; n < CONFIG_LASTCELL;
	      ++n ) {
		// TODO switch to switch statement here for better efficiency?
		if ( m_cellDetailsDatabase.at( n ).cellCurrentContent == 0 ) {
			m_cellSpriteDatabase [ n ].setTextureRect( sf::IntRect(
					0, 0, 16, 16 ) );//
							// empty=blue
		} else if ( m_cellDetailsDatabase.at( n ).cellCurrentContent ==
			    1 ) {
			m_cellSpriteDatabase [ n ].setTextureRect( sf::IntRect(
					48, 0, 16, 16 ) );	//
								// border=red
		} else if ( m_cellDetailsDatabase.at( n ).cellCurrentContent ==
			    2 ) {
			m_cellSpriteDatabase [ n ].setTextureRect( sf::IntRect(
					64, 0, 16, 16 ) );	//
								// snake=yellow
		} else if ( m_cellDetailsDatabase.at( n ).cellCurrentContent ==
			    3 ) {
			m_cellSpriteDatabase [ n ].setTextureRect( sf::IntRect(
					32, 0, 16, 16 ) );	//
								// fruit=white
		} else if ( m_cellDetailsDatabase.at( n ).cellCurrentContent ==
			    4 ) {
			m_cellSpriteDatabase [ n ].setTextureRect( sf::IntRect(
					96, 0, 16, 16 ) );	//
								// obstacle=pink
		} else if ( m_cellDetailsDatabase.at( n ).cellCurrentContent ==
			    5 ) {
			m_cellSpriteDatabase [ n ].setTextureRect( sf::IntRect(
					0, 0, 16, 16 ) );//
							// hud=blue
							// (same
							// color
							// with
							// 'empty'
							// cells
							// but
							// different
							// logical
							// meaning)
		} else if ( m_cellDetailsDatabase.at( n ).cellCurrentContent ==
			    6 ) {
			m_cellSpriteDatabase [ n ].setTextureRect( sf::IntRect(
					80, 0, 16, 16 ) );	//
								// debugMarked=gray
		}
	}
}

void Cell::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	for ( unsigned short int n = CONFIG_FIRSTCELL; n < CONFIG_LASTCELL;
	      ++n ) {
		target.draw( m_cellSpriteDatabase [ n ] );
	}
}

/* EOF */

