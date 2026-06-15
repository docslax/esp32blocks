#include "Game.h"
#include "Pieces.h"
#include "Config.h"
#include "Graphics.h"
#include "GameState.h"

#include <string.h>
#include <Arduino.h>

uint8_t board[20][10];

unsigned long lastDrop = 0;

void initBoard()
{
    memset(board, 0, sizeof(board));
}

void updateGame()
{
    if (millis() - lastDrop > DROP_DELAY)
    {
        if (!checkCollision(currentPiece.x, currentPiece.y + 1))
        {
            // previousX = currentPiece.x;
            // previousY = currentPiece.y;

            currentPiece.y++;

            screenDirty = true;

            lastDrop = millis();
        }
        else
        {
            lockPiece();
            Serial.printf("Locked piece type=%d at %d, %d\n", currentPiece.type, currentPiece.x, currentPiece.y);

            for (int y = 0; y < BOARD_HEIGHT; y++)
            {
                if (isLineFull(y))
                {
                    Serial.printf("LINE %d FULL!\n", y);
                }
            }
        }

        lastDrop = millis();
    }
}

void lockPiece()
{
    const PieceDefinition& piece =
        PIECES[currentPiece.type];

    const PieceRotation& rotation =
        piece.rotations[currentPiece.rotation];

    for (int py = 0; py < 4; py++)
    {
        for (int px = 0; px < 4; px++)
        {
            if (!rotation.blocks[py][px])
                continue;

            board[currentPiece.y + py]
                 [currentPiece.x + px] =
                 currentPiece.type + 1;
        }
    }

    calculateScore();

    // previousX = currentPiece.x;
    // previousY = currentPiece.y;

    spawnPiece();

    if (!canPlaceCurrentPiece())
    {
        gameState = STATE_GAME_OVER;
    }

    drawBoard();
}

bool checkCollision(int newX, int newY)
{
    const PieceDefinition& piece =
    PIECES[currentPiece.type];

    const PieceRotation& rotation =
        piece.rotations[currentPiece.rotation];

    for (int py = 0; py < 4; py++)
    {
        for (int px = 0; px < 4; px++)
        {
            if (!rotation.blocks[py][px])
                continue;

            int boardX = newX + px;
            int boardY = newY + py;

            // Left wall
            if (boardX < 0)
                return true;

            // Right wall
            if (boardX >= BOARD_WIDTH)
                return true;

            // Bottom wall
            if (boardY >= BOARD_HEIGHT)
                return true;

            // Existing blocks
            if (board[boardY][boardX])
                return true;
        }
    }

    return false;
}

void rotatePiece()
{
    uint8_t oldRotation =
        currentPiece.rotation;

    currentPiece.rotation =
        (currentPiece.rotation + 1) % 4;

    if (checkCollision(
            currentPiece.x,
            currentPiece.y))
    {
        currentPiece.rotation =
            oldRotation;
    }

    screenDirty = true;
}

bool isLineFull(int row)
{
    for (int x = 0; x < BOARD_WIDTH; x++)
    {
        if (board[row][x] == 0)
            return false;
    }

    return true;
}

void clearLine(int row)
{
    for (int x = 0; x < BOARD_WIDTH; x++)
    {
        board[row][x] = 0;
    }
}

void shiftRowsDown(int clearedRow)
{
    for (int y = clearedRow; y > 0; y--)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            board[y][x] = board[y - 1][x];
        }
    }

    // Clear top row
    for (int x = 0; x < BOARD_WIDTH; x++)
    {
        board[0][x] = 0;
    }
}

void removeLine(int row)
{
    Serial.printf("Clearing line %d\n", row);

    clearLine(row);
    shiftRowsDown(row);

    screenDirty = true;
}

int checkForCompletedLines()
{
    int linesCleared = 0;

    for (int y = BOARD_HEIGHT - 1; y >= 0; y--)
    {
        if (isLineFull(y))
        {
            removeLine(y);

            linesCleared++;

            y++;
        }
    }

    return linesCleared;
}

void startGame()
{
    memset(board, 0, sizeof(board));

    score = 0;

    initPieces();

    spawnPiece();

    screenDirty = true;

    gameState = STATE_PLAYING;
}

bool canPlaceCurrentPiece()
{
    const PieceDefinition& piece =
        PIECES[currentPiece.type];

    const PieceRotation& rotation =
        piece.rotations[currentPiece.rotation];

    for (int py = 0; py < 4; py++)
    {
        for (int px = 0; px < 4; px++)
        {
            if (!rotation.blocks[py][px])
                continue;

            int boardX = currentPiece.x + px;
            int boardY = currentPiece.y + py;

            if (board[boardY][boardX])
                return false;
        }
    }

    return true;
}