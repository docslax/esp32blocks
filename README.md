# ESP32Blocks

A Tetris-style block game for the ESP32, designed to run on a TFT display with joystick, button, and touch controls. The project uses PlatformIO and the `TFT_eSPI` library to draw the playfield, score area, next-piece preview, and game-over screen.

## Features

- **Classic falling-block gameplay** with a 10×20 playfield
- **Joystick control** for moving pieces left and right
- **Touch input** to rotate the current piece
- **Button control** to start and restart the game
- **Next-piece preview** shown in the score area
- **Scoreboard display** for score and status information
- **Hardware-configured layout** using constants defined in [include/Config.h](include/Config.h)

## Hardware Requirements

- **Microcontroller**: ESP32 development board
- **Display**: TFT LCD compatible with `TFT_eSPI`
- **Input**: Analog joystick (for left/right movement)
- **Input**: Touch pad or touch-capable input for rotation
- **Input**: Push button for start/restart
- **Power**: Stable 5V supply for the display and ESP32 board

## Pin Configuration

The current GPIO layout is defined in [include/Config.h](include/Config.h):

| Component | Purpose | Pin |
|-----------|---------|-----|
| Joystick X | Move piece left/right | `35` |
| Joystick Y | Not used for movement in current logic | `34` |
| Touch input | Rotate piece | `25` |
| Button | Start / restart | `27` |

### Display Wiring Notes

The display is initialized with `TFT_eSPI` in [src/Graphics.cpp](src/Graphics.cpp), and the game uses a landscape-style screen layout with:

- `tft.init()` to initialize the display driver
- `tft.setRotation(2)` to match the expected screen orientation

If you are using a different TFT module, you will likely need to configure the correct driver and pin mapping in your `User_Setup.h` file for the `TFT_eSPI` library.

## TFT Setup Details

To get the display working correctly, make sure the following are configured:

1. **Install `TFT_eSPI`** in PlatformIO
2. **Select the correct driver** for your LCD panel in `User_Setup.h`
3. **Set the SPI pins** to match your wiring (MOSI, SCLK, CS, DC, RST)
4. **Match the screen resolution** with your display
5. **Verify the rotation value** if the image appears upside down or sideways

A typical TFT setup for this kind of project usually includes:

- SPI MOSI pin
- SPI SCLK pin
- CS (chip select)
- DC (data/command)
- RESET pin
- optional backlight control pin

If your display is not rendering correctly, the first things to check are:

- the driver selection in `User_Setup.h`
- SPI pin assignments
- display rotation settings
- power connections to the TFT module

## Display Configuration

The game assumes a screen layout of:

- **320×480** display area
- **10-cell wide** game board
- **20-cell high** game board
- **20-pixel block size**
- scoreboard region at the bottom of the screen

These values are defined in [include/Config.h](include/Config.h).

## Project Structure

```text
src/
├── main.cpp        # Main loop and state management
├── Game.cpp        # Game logic, collision checks, and scoring
├── Graphics.cpp    # TFT drawing, screens, and piece rendering
├── Input.cpp       # Joystick, button, and touch handling
└── Pieces.cpp      # Piece definitions and spawn logic

include/
├── Config.h        # Hardware pins and game constants
├── Game.h          # Game function declarations
├── GameState.h     # Game state and score variables
├── Graphics.h      # Graphics declarations
├── Input.h         # Input declarations
└── Pieces.h        # Piece and piece-definition declarations
```

## Architecture Overview

The code is split into a few clear responsibilities:

- **Main loop** in [src/main.cpp](src/main.cpp) controls the overall game state (`TITLE`, `PLAYING`, `GAME_OVER`)
- **Game logic** in [src/Game.cpp](src/Game.cpp) handles dropping, locking, collision, line clearing, and restart flow
- **Graphics** in [src/Graphics.cpp](src/Graphics.cpp) redraws the board and UI elements on the TFT
- **Input** in [src/Input.cpp](src/Input.cpp) reads the joystick, touch, and button state
- **Piece data** in [src/Pieces.cpp](src/Pieces.cpp) defines the shapes, colors, and spawn behavior

## Gameplay

### Controls

- **Joystick X** - Move piece left/right
- **Touch input** - Rotate current piece
- **Button** - Start the game or restart after game over

### Game Flow

1. Title screen is shown on startup
2. Press the button to begin
3. A falling piece appears on the board
4. The player rotates and positions the piece to clear lines
5. The game ends when the stack reaches the top

## Building and Uploading

### Prerequisites

- [PlatformIO](https://platformio.org/) installed
- ESP32 board support configured
- USB cable connected to the ESP32
- TFT display configured correctly for `TFT_eSPI`

### Build

```bash
platformio run --target upload --environment esp32dev
```

### Build and Monitor

```bash
platformio run --target upload --target monitor --environment esp32dev
```

### Clean Build

```bash
platformio run --target clean --environment esp32dev
```

## Troubleshooting

### Display Not Working

- Verify the correct display driver is selected in `User_Setup.h`
- Check that the SPI connections match your wiring
- Confirm the screen rotation is correct
- Ensure the display is powered properly

### Input Not Responding

- Verify the joystick and touch pins in [include/Config.h](include/Config.h)
- Confirm the button is wired correctly and reading LOW when pressed
- Test values with serial output if needed

## Configuration

You can change game behavior and hardware settings in:

- [include/Config.h](include/Config.h) for pins and board constants
- [src/Graphics.cpp](src/Graphics.cpp) for display drawing behavior
- [src/Pieces.cpp](src/Pieces.cpp) for piece shapes and colors

## License

See [LICENSE](LICENSE) for details.
