#ifndef CONFIG_H
#define CONFIG_H

#define SCREEN_WIDTH       320
#define SCREEN_HEIGHT      480

#define BOARD_WIDTH        10
#define BOARD_HEIGHT       20

#define BLOCK_SIZE         20

#define SCOREBOARD_HEIGHT  80

#define BOARD_X ((SCREEN_WIDTH - (BOARD_WIDTH * BLOCK_SIZE)) / 2)
#define BOARD_Y 0

#define SCOREBOARD_Y (SCREEN_HEIGHT - SCOREBOARD_HEIGHT)

#define SCORE_X 10
#define LEVEL_X 110
#define NEXT_X  220

#define DROP_DELAY     200

// Controls
#define JOY_X_PIN      35
#define JOY_Y_PIN      34
#define TOUCH_PIN      25
#define BUTTON_PIN     27

#endif