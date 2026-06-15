#include "Graphics.h"
#include "Input.h"
#include "Game.h"
#include "Pieces.h"
#include "GameState.h"

bool screenDirty = true;
GameState previousState = STATE_TITLE;

void setup()
{
    

    Serial.begin(115200);
    random(millis());

    initInput();

    initGraphics();
    
    gameState = STATE_TITLE;
    drawTitleScreen();

    // spawnPiece();

    // drawBoard();

    // drawCurrentPiece();
}

void loop()
{
    // State change handler
    if (gameState != previousState)
    {
        switch (gameState)
        {
            case STATE_TITLE:
                drawTitleScreen();
                break;

            case STATE_GAME_OVER:
                drawGameOver();
                break;

            case STATE_PLAYING:
                drawBoard();
                screenDirty = true;
                break;
        }

        previousState = gameState;
    }

    switch (gameState)
    {
        case STATE_TITLE:

            if (isButtonPressed())
            {
                startGame();
            }

            break;

        case STATE_PLAYING:

            previousX = currentPiece.x;
            previousY = currentPiece.y;
            previousRotation = currentPiece.rotation;

            readControls();
            
            if (isTouchJustPressed())
            {
                rotatePiece();
            }
            
            updateGame();

            if (screenDirty)
            {
                drawGame();
                screenDirty = false;
            }

            break;

        case STATE_GAME_OVER:

            if (isButtonPressed())
            {
                startGame();
            }

            break;
    }
}