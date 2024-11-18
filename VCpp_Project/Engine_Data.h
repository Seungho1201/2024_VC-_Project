#pragma once

#include "Resource.h"
#include "framework.h"
#include "Engine_Data.h"

class EngineData {
public:
    static int mapGrid[GRID_ROWS][GRID_COLS];
    static float playerSpeed;                   // 0�� �� ����, 1�� ��, 2�� ������
    static float gravityVelocity;

    static RECT userBox;

};