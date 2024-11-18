#pragma once

#include "Resource.h"
#include "framework.h"
#include "Engine_Data.h"

class EngineData {
public:
    static int mapGrid[GRID_ROWS][GRID_COLS];
    static float playerSpeed;                   // 0은 빈 공간, 1은 벽, 2는 아이템
    static float gravityVelocity;

    static RECT userBox;

};