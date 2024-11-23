#include "Engine_Data.h"

int EngineData::mapGrid[GRID_ROWS][GRID_COLS] = { 0 };

float EngineData::playerSpeed = BASIC_PLAYER_SPEED;
float EngineData::gravityVelocity = GRAVITY_SPEED;

int EngineData::mapOffset = 50;

RECT EngineData::userBox = { 60, 600, 90, 630 };
HWND EngineData::playButton = nullptr;
bool EngineData::developMode = false;

HBITMAP EngineData::hBackground = nullptr;