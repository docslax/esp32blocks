#include "Config.h"
#include "Pieces.h"
#include "Graphics.h"
#include "Game.h"
#include "GameState.h"

TFT_eSPI tft = TFT_eSPI();

void initGraphics()
{
    tft.init();
    tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);
}

void drawBoard()
{
    tft.fillScreen(TFT_BLACK);

    // Left wall
    tft.fillRect(
        BOARD_X - 2,
        BOARD_Y,
        2,
        BOARD_HEIGHT * BLOCK_SIZE,
        TFT_CYAN);

    // Right wall
    tft.fillRect(
        BOARD_X + (BOARD_WIDTH * BLOCK_SIZE),
        BOARD_Y,
        2,
        BOARD_HEIGHT * BLOCK_SIZE,
        TFT_CYAN);

    // bottom area
    tft.drawLine(
        0,
        SCOREBOARD_Y,
        SCREEN_WIDTH,
        SCOREBOARD_Y,
        TFT_CYAN);

    drawScoreboard();

    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            if (board[y][x])
            {
                const PieceDefinition& piece =
                    PIECES[board[y][x] - 1];

                tft.fillRect(
                    BOARD_X + (x * BLOCK_SIZE),
                    BOARD_Y + (y * BLOCK_SIZE),
                    BLOCK_SIZE - 1,
                    BLOCK_SIZE - 1,
                    piece.color);
            }
        }
    }
}

void clearField()
{
    // Clear playfield first
    tft.fillRect(
        BOARD_X,
        BOARD_Y,
        BOARD_WIDTH * BLOCK_SIZE,
        BOARD_HEIGHT * BLOCK_SIZE,
        TFT_BLACK);
}

void drawScoreboard()
{
    tft.fillRect(
        0,
        SCOREBOARD_Y + 1,
        SCREEN_WIDTH,
        SCREEN_HEIGHT - SCOREBOARD_Y,
        TFT_BLACK);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);

    tft.setCursor(10, SCOREBOARD_Y + 10);
    tft.printf("Score");

    tft.setCursor(10, SCOREBOARD_Y + 35);
    tft.printf("%d", score);

    tft.setCursor(120, SCOREBOARD_Y + 10);
    tft.printf("Level");

    tft.setCursor(120, SCOREBOARD_Y + 35);
    tft.printf("1");

    tft.setCursor(220, SCOREBOARD_Y + 10);
    tft.printf("Next");

    drawNextPiece();
}

void drawPiece(
    int pixelX,
    int pixelY,
    const Piece& pieceInstance,
    uint16_t color)
{
    const PieceDefinition& piece =
        PIECES[pieceInstance.type];

    const PieceRotation& rotation =
        piece.rotations[pieceInstance.rotation];

    if (color == DEFAULT_COLOR)
    {
        color = piece.color;
    }

    for (int py = 0; py < 4; py++)
    {
        for (int px = 0; px < 4; px++)
        {
            if (!rotation.blocks[py][px])
                continue;

            tft.fillRect(
                pixelX + (px * BLOCK_SIZE),
                pixelY + (py * BLOCK_SIZE),
                BLOCK_SIZE - 1,
                BLOCK_SIZE - 1,
                color
            );
        }
    }
}

void eraseCurrentPiece()
{
    Piece erasePiece = currentPiece;
    erasePiece.rotation = previousRotation;

    drawPiece(
        BOARD_X + (previousX * BLOCK_SIZE),
        BOARD_Y + (previousY * BLOCK_SIZE),
        erasePiece,
        TFT_BLACK
    );
}

void drawCurrentPiece()
{
    drawPiece(
        BOARD_X + (currentPiece.x * BLOCK_SIZE),
        BOARD_Y + (currentPiece.y * BLOCK_SIZE),
        currentPiece
    );
}

void drawNextPiece()
{
    drawPiece(
        240,
        SCOREBOARD_Y + 25,
        nextPiece
    );
}

void drawGame()
{
    eraseCurrentPiece();

    drawCurrentPiece();
}

void drawTitleScreen()
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_CYAN);
    tft.setTextSize(4);

    tft.setCursor(80, 100);
    tft.println("ESP32");
    tft.setCursor(80, 150);
    tft.println("BLOCKS");

    tft.setTextSize(2);

    tft.setCursor(40, 200);
    tft.println("Press Button");

    tft.setCursor(40, 230);
    tft.println("To Start");
}

void drawGameOver()
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_RED);
    tft.setTextSize(4);

    tft.setCursor(20, 120);
    tft.println("GAME");

    tft.setCursor(20, 170);
    tft.println("OVER");

    tft.setTextSize(2);

    tft.setCursor(40, 260);
    tft.printf("Score: %d", score);

    tft.setCursor(40, 320);
    tft.println("Press Button");

    tft.setCursor(40, 350);
    tft.println("To Restart");
}