#include "GameState.h"
#include "Game.h"

GameState gameState = STATE_TITLE;

int score = 0;
int level = 1;
int linesCleared = 0;

void calculateScore()
{
    int lines = checkForCompletedLines();

    switch (lines)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    case 4:
        score += 800;
        break;
    }
}

