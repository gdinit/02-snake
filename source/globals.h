/* globals.h */

#ifndef GLOBALS_H
#define GLOBALS_H

struct Settings {
	bool inGameOverlay = false;
	bool debugPrintToConsole = false;
	bool debugPrintToConsoleFPS = false;
	float playAreaTopLine = -99999.f;
	float playAreaBottomLine = -99999.f;
	float playAreaLeftLine = -99999.f;
	float playAreaRightLine = -99999.f;
	unsigned short int currentScreenSizeWidth = 0;
	unsigned short int currentScreenSizeHeight = 0;
	// speed set in config, loaded by app()
	float snakeSpeed = -1.f;
};

struct Globals {
	bool moveLeftRequestActive = false;
	bool moveRightRequestActive = false;
	bool moveUpRequestActive = false;
	bool moveDownRequestActive = false;
	signed long int	currentScore = -1;
	// snake.cc does not have access to *_state's feature
	// "m_machine.quit()",
	// therefore if an app termination is needed they flip this bool
	bool mustDie = false;
	// TODO: change this to show "Game Over!"" screen
	bool mustMainMenu = false;
	signed int snakeCurrentWidth = -1;
	signed short int livesLeft = -1;
	bool preGameAnimationNeeded = true;
	bool preGameAnimationRunning = false;
	bool preGameAnimationStep1Needed = true;
	bool preGameAnimationStep2Needed = true;
	bool preGameAnimationStep3Needed = true;
	bool preGameAnimationStep4Needed = true;
	bool preGameAnimationStep1SFXNeeded = true;
	bool preGameAnimationStep2SFXNeeded = true;
	bool preGameAnimationStep3SFXNeeded = true;
	bool preGameAnimationStep4SFXNeeded = true;
	signed short int snakeCellGrowthPendingCount = 0;
};

#endif	// GLOBALS_H

/* EOF */

