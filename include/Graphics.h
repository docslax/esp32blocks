#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <TFT_eSPI.h>
#include "Pieces.h"

// Display objects
extern TFT_eSPI tft;
constexpr uint16_t DEFAULT_COLOR = 0xFFFF;

void initGraphics();

void drawBoard();

void drawCurrentPiece();

void drawGame();

void eraseCurrentPiece();

void clearField();

void drawScoreboard();

void drawPiece(
    int pixelX,
    int pixelY,
    const Piece& pieceInstance,
    uint16_t color = DEFAULT_COLOR
);

void drawNextPiece();

void drawTitleScreen();

void drawGameOver();

#endif