/* game_objects.cc */

#include <include/game_objects.h>

// CREATE GAME OBJECTS
std::unique_ptr <Settings>	SETTINGS = std::make_unique <Settings> ();
std::unique_ptr <Globals>	GLOBALS = std::make_unique <Globals> ();
std::unique_ptr <Snake>		snake = std::make_unique <Snake> ();
std::unique_ptr <Fruit>		fruit = std::make_unique <Fruit> ();
std::unique_ptr <Cell>		cell = std::make_unique <Cell> ();
std::unique_ptr <Common>	common = std::make_unique <Common> ();

/* EOF */

