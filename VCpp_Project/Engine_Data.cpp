#include "Engine_Data.h"

int EngineData::mapGrid[GRID_ROWS][GRID_COLS] = { 0 };

float EngineData::playerSpeed = BASIC_PLAYER_SPEED;
float EngineData::gravityVelocity = GRAVITY_SPEED;

int EngineData::mapOffset = 50;

RECT EngineData::userBox = { 100, 100, 130, 130 };