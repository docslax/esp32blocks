#include "Input.h"
#include "Pieces.h"
#include "Game.h"
#include "Config.h"

#include <Arduino.h>

extern bool screenDirty;
bool wasTouched = false;

void readControls()
{
    int x = analogRead(JOY_X_PIN);

    // Physical stick LEFT
    if (x > 3500)
    {
        if (!checkCollision(
                currentPiece.x - 1,
                currentPiece.y))
        {
            // previousX = currentPiece.x;
            // previousY = currentPiece.y;

            currentPiece.x--;

            screenDirty = true;
        }

        delay(150);
    }

    // Physical stick RIGHT
    else if (x < 500)
    {
        if (!checkCollision(
                currentPiece.x + 1,
                currentPiece.y))
        {
            // previousX = currentPiece.x;
            // previousY = currentPiece.y;

            currentPiece.x++;

            screenDirty = true;
        }

        delay(150);
    }
}

void initInput()
{
  pinMode(BUTTON_PIN, INPUT);
  pinMode(TOUCH_PIN, INPUT);
}

bool isButtonPressed()
{
  return digitalRead(BUTTON_PIN) == LOW;
}

bool isTouchJustPressed()
{
    bool current = digitalRead(TOUCH_PIN);

    bool result =
        current && !wasTouched;

    wasTouched = current;

    return result;
}