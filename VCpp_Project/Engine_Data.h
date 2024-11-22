#pragma once

#include "Resource.h"
#include "framework.h"
#include "Engine_Data.h"

class EngineData {
public:
    static int mapGrid[GRID_ROWS][GRID_COLS];   // 2���� ��
    static int mapOffset;                       // RECT ����

    static float playerSpeed;                   // �÷��̾� �ӵ�              
    static float gravityVelocity;               // �߷� ��

    static RECT userBox;                        // �÷��̾� RECT


};