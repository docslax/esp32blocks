#include "Config.h"
#include "Pieces.h"
#include "GameState.h"
#include <Arduino.h>
#include "TFT_eSPI.h"

Piece currentPiece;
Piece nextPiece;

int previousX = 0;
int previousY = 0;
uint8_t previousRotation = 0;

// const PieceDefinition PIECES[] =
// {
//     // O
//     {
//         2,
//         2,
//         {
//             {1,1,0,0},
//             {1,1,0,0},
//             {0,0,0,0},
//             {0,0,0,0}
//         },
//         TFT_YELLOW
//     },

//     // I
//     {
//         4,
//         1,
//         {
//             {1,1,1,1},
//             {0,0,0,0},
//             {0,0,0,0},
//             {0,0,0,0}
//         },
//         TFT_CYAN
//     },

//     // T
//     {
//         3,
//         2,
//         {
//             {1,1,1,0},
//             {0,1,0,0},
//             {0,0,0,0},
//             {0,0,0,0}
//         },
//         TFT_MAGENTA
//     },

//     // L
//     {
//         3,
//         2,
//         {
//             {1,1,1,0},
//             {1,0,0,0},
//             {0,0,0,0},
//             {0,0,0,0}
//         },
//         TFT_ORANGE
//     },

//     // J
//     {
//         3,
//         2,
//         {
//             {1,1,1,0},
//             {0,0,1,0},
//             {0,0,0,0},
//             {0,0,0,0}
//         },
//         TFT_BLUE
//     },

//     // S
//     {
//         3,
//         2,
//         {
//             {0,1,1,0},
//             {1,1,0,0},
//             {0,0,0,0},
//             {0,0,0,0}
//         },
//         TFT_GREEN
//     },

//     // Z
//     {
//         3,
//         2,
//         {
//             {1,1,0,0},
//             {0,1,1,0},
//             {0,0,0,0},
//             {0,0,0,0}
//         },
//         TFT_RED
//     }
// };

const PieceDefinition PIECES[] =
    {
        // O
        {TFT_YELLOW,
         {{2,
           2,
           {{1, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}}},

          {2,
           2,
           {{1, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}}},

          {2,
           2,
           {{1, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}}},

          {2,
           2,
           {{1, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}}}}},
        
        // I
        {TFT_CYAN,
         {{4,
           1,
           {{1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}}},

          {1,
           4,
           {{1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0}}},

          // duplicate for now
          {
              4,
              1,
              {{1, 1, 1, 1},
               {0, 0, 0, 0},
               {0, 0, 0, 0},
               {0, 0, 0, 0}}},

          {1,
           4,
           {{1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0}}}}}

        // T
        
        // L

        // J

        // S

        // Z

};

int numPieces = sizeof(PIECES) / sizeof(PIECES[0]);

void spawnPiece()
{
    currentPiece = nextPiece;

    currentPiece.x = BOARD_WIDTH / 2 - 2;
    currentPiece.y = 0;
    currentPiece.rotation = 0;

    nextPiece.type = (PieceType)random(0, numPieces);
    nextPiece.rotation = 0;

    Serial.printf(
        "Current=%d Next=%d\n",
        currentPiece.type,
        nextPiece.type);
}

void initPieces()
{
    int numPieces =
        sizeof(PIECES) / sizeof(PIECES[0]);

    currentPiece.type =
        (PieceType)random(0, numPieces);

    nextPiece.type =
        (PieceType)random(0, numPieces);
}