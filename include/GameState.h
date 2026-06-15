#ifndef GAMESTATE_H
#define GAMESTATE_H

enum GameState
{
    STATE_TITLE,
    STATE_PLAYING,
    STATE_GAME_OVER
};

extern GameState gameState;

extern int score;
extern int level;
extern int linesCleared;

extern bool screenDirty;

void calculateScore();

#endif