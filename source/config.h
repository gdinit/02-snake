/* config.h */

#ifndef CONFIG_H
#define CONFIG_H

#include "globals.h"

// needed for window_title etc.
#include <string>
// #define NDEBUG
// #include <assert.h>

// WINDOW
// constexpr unsigned short int	CONFIG_WIN_WIDTH = { 1600 }, CONFIG_WIN_HEIGHT = { 1200 };
// constexpr unsigned short int	CONFIG_WIN_WIDTH = { 1024 }, CONFIG_WIN_HEIGHT = { 768 };
// constexpr unsigned short int	CONFIG_WIN_WIDTH = { 768 }, CONFIG_WIN_HEIGHT = { 576 };
// constexpr unsigned short int	CONFIG_WIN_WIDTH = { 700 }, CONFIG_WIN_HEIGHT = { 550 };
constexpr unsigned short int	CONFIG_WIN_WIDTH = { 640 }, CONFIG_WIN_HEIGHT = { 480 };
const std::string		CONFIG_WINDOW_TITLE_TEXT { "Snake" };

// FPS
constexpr unsigned short int	CONFIG_DESIRED_FPS_INT { 60 };
constexpr float			CONFIG_DESIRED_FPS_FLOAT { 60.f };
constexpr unsigned short int	CONFIG_OBSERVED_FPS_CONTAINER_MAX_SIZE { 10 };
constexpr unsigned short int	CONFIG_OBSERVED_FPS_ACT_THRESHOLD { 5 };
constexpr float			CONFIG_FPS_CATCHUP_STEP_F { 0.5 };
constexpr unsigned short int	CONFIG_DYNFPS_TOO_YOUNG_THRESHOLD_SECONDS_INT { 5 };
constexpr unsigned short int	CONFIG_FPS_OVERLAY_MIN_AGE_TO_UPDATE_SECONDS_INT { 1 };
// DEBUG
constexpr bool			DEBUG { true };
// show in-game FPS/Stats overlay
constexpr bool			CONFIG_DEBUG_SHOW_OVERLAY { true };
// print extra messages in game console window
constexpr bool			CONFIG_DEBUG_CONSOLE_OUTPUT { false };
// dynamic fps monitoring & adjustment => report to the console
constexpr bool			CONFIG_DEBUG_DYNFPS_CONSOLE_OUTPUT { false };
// PLAY AREA
constexpr float			CONFIG_PLAY_AREA_INDENT_TOP { 20.f };
constexpr float			CONFIG_PLAY_AREA_INDENT_BOTTOM { 20.f };
constexpr float			CONFIG_PLAY_AREA_INDENT_RIGHT { 20.f };
constexpr float			CONFIG_PLAY_AREA_INDENT_LEFT { 20.f };
constexpr float			CONFIG_PLAY_AREA_OUTSIDE_LEFT { -1.f };
constexpr float			CONFIG_GOAL_LINE_LEFT { 0.f };
constexpr float			CONFIG_GOAL_LINE_RIGHT { CONFIG_WIN_WIDTH };
// PLAYERS
constexpr bool			CONFIG_SIDE_RIGHT_IS_COMPUTER { false };
constexpr bool			CONFIG_SIDE_LEFT_IS_COMPUTER { true };
// MAIN MENU
constexpr float			CONFIG_MENU_BOX_WIDTH { 220.f };
constexpr float			CONFIG_MENU_BOX_HEIGHT { 40.f };
constexpr float			CONFIG_MENU_BUTTON_1 { .40f };
constexpr float			CONFIG_MENU_BUTTON_2 { .55f };
constexpr float			CONFIG_MENU_BUTTON_3 { .70f };
// CELL
constexpr float			CONFIG_CELLSIZE { 11.f };
constexpr signed short int	CONFIG_ROWS = { 30 };
constexpr signed short int	CONFIG_COLUMNS = { 40 };
constexpr signed short int	CONFIG_FIRSTCELL = { 0 };
constexpr signed short int	CONFIG_LASTCELL = { CONFIG_ROWS* CONFIG_COLUMNS };
// SNAKE
constexpr float			CONFIG_SNAKE_SPAWN_POS_X { 100.f };
constexpr float			CONFIG_SNAKE_SPAWN_POS_Y { 100.f };
constexpr float			CONFIG_SNAKE_SPEED { 0.15f };
constexpr signed short int	CONFIG_SNAKE_MAX_LIVES = { 3 };
// BORDER
constexpr float			CONFIG_BORDER_START_X { 0.f };
constexpr float			CONFIG_BORDER_START_Y { 20.f };
constexpr float			CONFIG_BORDER_THICKNESS { 12.f };
// PREGAME ANIMATION
constexpr float			CONFIG_PREGAME_ANIMATION_STEP_DURATION { .50f };
constexpr float			CONFIG_PREGAME_ANIMATION_POS_X { CONFIG_WIN_WIDTH / 2 };
constexpr float			CONFIG_PREGAME_ANIMATION_POS_Y { CONFIG_WIN_HEIGHT* 0.38f };
// SCORE
// constexpr float			CONFIG_SCORE_STEP { 125.f };
constexpr signed long int	CONFIG_SCORE_STEP = { 125 };
// FRUIT
constexpr float			CONFIG_NEW_FRUIT_MIN_DISTANCE_TO_HEAD { CONFIG_WIN_WIDTH / 3 };
// GAME SPEED
constexpr float			CONFIG_ACCUMULATOR_VALUE { 9.f };
// GAME MISC OPTIONS
// constexpr float			CONFIG_GROWTH_MULTIPLIER_VALUE { 2 };
constexpr signed short int	CONFIG_GROWTH_MULTIPLIER_VALUE = { 2 };
/*
        FRUIT #			GROWTH CELLS
        1			2
        2			4
        3			6
        4			8
        5			10
        6			12
        7			14
        8			16
        9			18
*/

#endif	// CONFIG_H

/* EOF */

