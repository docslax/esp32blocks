#ifndef GAME_H
#define GAME_H

#include <stdint.h>

extern uint8_t board[20][10];

void initBoard();

void updateGame();

void lockPiece();

bool checkCollision(
    int newX,
    int newY
);

void clearLines();

bool isLineFull(int y);

void clearLine(int row);

void shiftRowsDown(int clearedRow);

void removeLine(int row);

int checkForCompletedLines();

bool canPlaceCurrentPiece();

void startGame();

#endif