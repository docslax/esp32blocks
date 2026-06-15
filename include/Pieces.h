#ifndef PIECES_H
#define PIECES_H

#include <stdint.h>

extern int previousX;
extern int previousY;
extern uint8_t previousRotation;

enum PieceType
{
    PIECE_O,
    PIECE_I
};

struct Piece
{
    int x;
    int y;

    uint8_t rotation;
    PieceType type;
};

struct PieceRotation
{
    uint8_t width;
    uint8_t height;
    uint8_t blocks[4][4];
};

struct PieceDefinition
{
    uint16_t color;
    PieceRotation rotations[4];
};

extern const PieceDefinition PIECES[];
extern Piece currentPiece;
extern Piece nextPiece;

void spawnPiece();
void rotatePiece();
void initPieces();

#endif