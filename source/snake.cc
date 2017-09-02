/* snake.cc */

#include "snake.h"

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;
extern std::unique_ptr <Fruit>		fruit;
// needed for collision detection/boundingbox
extern std::unique_ptr <Common>		common;
extern std::unique_ptr <Cell>		cell;

Snake::Snake()
{
	///////////////////
	// SOUNDS

	// death
	if ( !m_bufferBlip1.loadFromFile( "assets/sounds/blip1.wav" ) ) {
		std::cout << "\nERROR while attempting to load a resource!\n\n";
		exit( EXIT_FAILURE );
	}
	m_soundBlip1.setBuffer( m_bufferBlip1 );

	// ate
	if ( !m_bufferAteFruit.loadFromFile( "assets/sounds/ate-fruit.wav" ) ) {
		std::cout << "\nERROR while attempting to load a resource!\n\n";
		exit( EXIT_FAILURE );
	}
	m_soundAteFruit.setBuffer( m_bufferAteFruit );
}

Snake::~Snake() {}

void Snake::newSnake()
{
	// for now, spawn at hardcoded cell coordinates
	m_snakeMustDie = false;

	// clear snakebodycell list
	m_snakeCells.clear();

	GLOBALS->snakeCellGrowthPendingCount = 0;

	// NOTE THIS MUST COME BEFORE createNewFruit()!
	cell->newRound();

	fruit->createNewFruit();

	// create the new snake
	for ( unsigned short int n = 462; n < 465; n++ ) {
		cell->m_cellDetailsDatabase.at( n ).cellCurrentContent = 2;
		// add the observed fps to the end of the queue
		m_snakeCells.push_back( n );
	}
	m_snakeHeadPositionId = 464;
	m_snakeDirection = DIRECTIONRIGHT;
	m_snakeMoveAccumulator = 0;
}

void Snake::startNewGame()
{
	//// RESET the lives here before starting a new round
	if ( CONFIG_SNAKE_MAX_LIVES >= 1 ) {
		// we are spawning one snake in playarea, thus 1 life used
		GLOBALS->livesLeft = CONFIG_SNAKE_MAX_LIVES - 1;
		fruit->setFruitIdToZero();
		newSnake();
	}
}

void Snake::collisionDetectRespond( void ) noexcept
{
	if ( m_snakeMustDie ) {
		// action 'killing process' here

		if ( GLOBALS->livesLeft >= 1 ) {
			GLOBALS->livesLeft = GLOBALS->livesLeft - 1;
			// TODO change this to a new sound (death sound. less
			// dramatic then new/planned GameOver sound)
			m_soundBlip1.play();
			fruit->createNewFruit();
			newSnake();
		} else if ( GLOBALS->livesLeft == 0 ) {
			// TODO: change this to more dramatic GameOver sound
			m_soundBlip1.play();
			GLOBALS->mustMainMenu = true;
		}
	}
}

void Snake::update( sf::Time timeSinceLastUpdate )
{
	// MY ORIGINAL CODE
	++m_snakeMoveAccumulator;

	// UPDATE only if enough time has passed
	if ( ++m_snakeMoveAccumulator > CONFIG_ACCUMULATOR_VALUE ) {
		m_snakeMoveAccumulator = 0;

		if ( !GLOBALS->preGameAnimationRunning ) {
			// anim running -- DO process snake's movement

			processHumanDirectionKeypress();
			collisionDetectRespond();

			unsigned int	tailPos = m_snakeCells.front();
			signed int	newPos = m_snakeHeadPositionId;

			switch ( m_snakeDirection ) {
				// killer cells are	: 1 (border), 2 (snake),
				// 4 (obstacle), 5 (hud)
				// legal moves are	: 0 (empty), 3 (fruit),
				// 6 (debugmarked) - anything else kills the
				// snake!

				case DIRECTIONNONE:
					break;

				case DIRECTIONRIGHT:
					newPos = m_snakeHeadPositionId + 1;
					if ( ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 1 ) ||
					     ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 2 ) ||
					     ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 4 ) ||
					     ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 5 ) ) {
						// ILLEGAL MOVE -- DO NOT
						// ADVANCE
						m_snakeMustDie = true;

						return;
					} else {
						// LEGAL MOVE -- DO ADVANCE

						// MOVE -- mark new cell as
						// snake body
						m_snakeHeadPositionId = newPos;

						// FRUIT? CHECK & ACTION ON
						if ( cell->m_cellDetailsDatabase
						     .at(
							     newPos ).
						     cellCurrentContent ==
						     3 ) {
							// grow now but -- how
							// many cells?
							GLOBALS->
							snakeCellGrowthPendingCount
								=
									(
										GLOBALS
										->
										snakeCellGrowthPendingCount )
									+ ( (
										    fruit
										    ->
										    m_fruitID
										    *
										    CONFIG_GROWTH_MULTIPLIER_VALUE ) );
							m_soundAteFruit.play();	//
										//
										//
										//
										//
										//
										// MUSIC
										//
										//
										//
										//
										//
										// TO
										//
										//
										//
										//
										//
										// CELEBRATE
							GLOBALS->currentScore =
								GLOBALS->
								currentScore +
								CONFIG_SCORE_STEP;						//
																//
																//
																//
																//
																//
																// BUMP
																//
																//
																//
																//
																//
																// SCORE
							fruit->createNewFruit();//
										//
										//
										//
										//
										//
										// NEED
										//
										//
										//
										//
										//
										// TO
										//
										//
										//
										//
										//
										//
										// SPAWN
										//
										//
										//
										//
										//
										// A
										//
										//
										//
										//
										//
										// NEW
										//
										//
										//
										//
										//
										// FRUIT
						}

						// mark the new cell as snake
						cell->m_cellDetailsDatabase.at(
							m_snakeHeadPositionId ).
						cellCurrentContent = 2;
						// add new snakebodycell to the
						// list of known snakeCells
						m_snakeCells.push_back(
							m_snakeHeadPositionId );

						// KEEP TAIL INTACT (to grow) or
						// SHRINK THE TAIL?
						if ( GLOBALS->
						     snakeCellGrowthPendingCount
						     > 0 ) {
							// GROW HERE by doing
							// nothing
							--GLOBALS->
							snakeCellGrowthPendingCount;
						} else {
							// SHRINK HERE
							cell->
							m_cellDetailsDatabase.at(
								tailPos ).
							cellCurrentContent =
								0;
							m_snakeCells.pop_front();
						}
					}
					break;

				case DIRECTIONLEFT:
					newPos = m_snakeHeadPositionId - 1;
					if ( ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 1 ) ||
					     ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 2 ) ||
					     ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 4 ) ||
					     ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 5 ) ) {
						m_snakeMustDie = true;

						return;
					} else {
						// LEGAL MOVE -- DO ADVANCE

						// MOVE -- mark new cell as
						// snake body
						m_snakeHeadPositionId = newPos;

						// FRUIT? CHECK & ACTION ON
						if ( cell->m_cellDetailsDatabase
						     .at(
							     newPos ).
						     cellCurrentContent ==
						     3 ) {
							// grow now but -- how
							// many cells?
							GLOBALS->
							snakeCellGrowthPendingCount
								=
									(
										GLOBALS
										->
										snakeCellGrowthPendingCount )
									+ ( (
										    fruit
										    ->
										    m_fruitID
										    *
										    CONFIG_GROWTH_MULTIPLIER_VALUE ) );
							m_soundAteFruit.play();	//
										//
										//
										//
										//
										//
										// MUSIC
										//
										//
										//
										//
										//
										// TO
										//
										//
										//
										//
										//
										// CELEBRATE
							GLOBALS->currentScore =
								GLOBALS->
								currentScore +
								CONFIG_SCORE_STEP;						//
																//
																//
																//
																//
																//
																// BUMP
																//
																//
																//
																//
																//
																// SCORE
							fruit->createNewFruit();//
										//
										//
										//
										//
										//
										// NEED
										//
										//
										//
										//
										//
										// TO
										//
										//
										//
										//
										//
										//
										// SPAWN
										//
										//
										//
										//
										//
										// A
										//
										//
										//
										//
										//
										// NEW
										//
										//
										//
										//
										//
										// FRUIT
						}

						// mark the new cell as snake
						cell->m_cellDetailsDatabase.at(
							m_snakeHeadPositionId ).
						cellCurrentContent = 2;
						// add new snakebodycell to the
						// list of known snakeCells
						m_snakeCells.push_back(
							m_snakeHeadPositionId );

						// KEEP TAIL INTACT (to grow) or
						// SHRINK THE TAIL?
						if ( GLOBALS->
						     snakeCellGrowthPendingCount
						     > 0 ) {
							// GROW HERE by doing
							// nothing
							--GLOBALS->
							snakeCellGrowthPendingCount;
						} else {
							// SHRINK HERE
							cell->
							m_cellDetailsDatabase.at(
								tailPos ).
							cellCurrentContent =
								0;
							m_snakeCells.pop_front();
						}
					}
					break;

				case DIRECTIONUP:
					newPos = m_snakeHeadPositionId -
						CONFIG_COLUMNS;
					if ( ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 1 ) ||
					     ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 2 ) ||
					     ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 4 ) ||
					     ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 5 ) ) {
						m_snakeMustDie = true;

						return;
					} else {
						// LEGAL MOVE -- DO ADVANCE

						// MOVE -- mark new cell as
						// snake body
						m_snakeHeadPositionId = newPos;

						// FRUIT? CHECK & ACTION ON
						if ( cell->m_cellDetailsDatabase
						     .at(
							     newPos ).
						     cellCurrentContent ==
						     3 ) {
							// grow now but -- how
							// many cells?
							GLOBALS->
							snakeCellGrowthPendingCount
								=
									(
										GLOBALS
										->
										snakeCellGrowthPendingCount )
									+ ( (
										    fruit
										    ->
										    m_fruitID
										    *
										    CONFIG_GROWTH_MULTIPLIER_VALUE ) );
							m_soundAteFruit.play();	//
										//
										//
										//
										//
										//
										// MUSIC
										//
										//
										//
										//
										//
										// TO
										//
										//
										//
										//
										//
										// CELEBRATE
							GLOBALS->currentScore =
								GLOBALS->
								currentScore +
								CONFIG_SCORE_STEP;						//
																//
																//
																//
																//
																//
																// BUMP
																//
																//
																//
																//
																//
																// SCORE
							fruit->createNewFruit();//
										//
										//
										//
										//
										//
										// NEED
										//
										//
										//
										//
										//
										// TO
										//
										//
										//
										//
										//
										//
										// SPAWN
										//
										//
										//
										//
										//
										// A
										//
										//
										//
										//
										//
										// NEW
										//
										//
										//
										//
										//
										// FRUIT
						}

						// mark the new cell as snake
						cell->m_cellDetailsDatabase.at(
							m_snakeHeadPositionId ).
						cellCurrentContent = 2;
						// add new snakebodycell to the
						// list of known snakeCells
						m_snakeCells.push_back(
							m_snakeHeadPositionId );

						// KEEP TAIL INTACT (to grow) or
						// SHRINK THE TAIL?
						if ( GLOBALS->
						     snakeCellGrowthPendingCount
						     > 0 ) {
							// GROW HERE by doing
							// nothing
							--GLOBALS->
							snakeCellGrowthPendingCount;
						} else {
							// SHRINK HERE
							cell->
							m_cellDetailsDatabase.at(
								tailPos ).
							cellCurrentContent =
								0;
							m_snakeCells.pop_front();
						}
					}
					break;

				case DIRECTIONDOWN:
					newPos = m_snakeHeadPositionId +
						CONFIG_COLUMNS;
					if ( ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 1 ) ||
					     ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 2 ) ||
					     ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 4 ) ||
					     ( cell->m_cellDetailsDatabase.at(
						       newPos ).
					       cellCurrentContent == 5 ) ) {
						m_snakeMustDie = true;

						return;
					} else {
						// LEGAL MOVE -- DO ADVANCE

						// MOVE -- mark new cell as
						// snake body
						m_snakeHeadPositionId = newPos;

						// FRUIT? CHECK & ACTION ON
						if ( cell->m_cellDetailsDatabase
						     .at(
							     newPos ).
						     cellCurrentContent ==
						     3 ) {
							// grow now but -- how
							// many cells?
							GLOBALS->
							snakeCellGrowthPendingCount
								=
									(
										GLOBALS
										->
										snakeCellGrowthPendingCount )
									+ ( (
										    fruit
										    ->
										    m_fruitID
										    *
										    CONFIG_GROWTH_MULTIPLIER_VALUE ) );
							m_soundAteFruit.play();	//
										//
										//
										//
										//
										//
										// MUSIC
										//
										//
										//
										//
										//
										// TO
										//
										//
										//
										//
										//
										// CELEBRATE
							GLOBALS->currentScore =
								GLOBALS->
								currentScore +
								CONFIG_SCORE_STEP;						//
																//
																//
																//
																//
																//
																// BUMP
																//
																//
																//
																//
																//
																// SCORE
							fruit->createNewFruit();//
										//
										//
										//
										//
										//
										// NEED
										//
										//
										//
										//
										//
										// TO
										//
										//
										//
										//
										//
										//
										// SPAWN
										//
										//
										//
										//
										//
										// A
										//
										//
										//
										//
										//
										// NEW
										//
										//
										//
										//
										//
										// FRUIT
						}

						// mark the new cell as snake
						cell->m_cellDetailsDatabase.at(
							m_snakeHeadPositionId ).
						cellCurrentContent = 2;
						// add new snakebodycell to the
						// list of known snakeCells
						m_snakeCells.push_back(
							m_snakeHeadPositionId );

						// KEEP TAIL INTACT (to grow) or
						// SHRINK THE TAIL?
						if ( GLOBALS->
						     snakeCellGrowthPendingCount
						     > 0 ) {
							// GROW HERE by doing
							// nothing
							--GLOBALS->
							snakeCellGrowthPendingCount;
						} else {
							// SHRINK HERE
							cell->
							m_cellDetailsDatabase.at(
								tailPos ).
							cellCurrentContent =
								0;
							m_snakeCells.pop_front();
						}
					}
					break;
			}
			std::deque <unsigned short int>::iterator it =
				m_snakeCells.begin();
		}
	}
}

void Snake::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
}

void Snake::processHumanDirectionKeypress()
{
	if ( GLOBALS->moveLeftRequestActive && m_snakeDirection !=
	     DIRECTIONRIGHT ) {
		m_snakeDirection = DIRECTIONLEFT;
	} else if ( GLOBALS->moveRightRequestActive && m_snakeDirection !=
		    DIRECTIONLEFT ) {
		m_snakeDirection = DIRECTIONRIGHT;
	} else if ( GLOBALS->moveUpRequestActive && m_snakeDirection !=
		    DIRECTIONDOWN ) {
		m_snakeDirection = DIRECTIONUP;
	} else if ( GLOBALS->moveDownRequestActive && m_snakeDirection !=
		    DIRECTIONUP ) {
		m_snakeDirection = DIRECTIONDOWN;
	}
}

/* EOF */

