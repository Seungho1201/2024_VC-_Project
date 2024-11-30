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
    static HWND playButton;
    static bool developMode;

    static HBITMAP hBackground;

    static float imageMove;

    static int playerHeart;

    static DWORD playTimer;
    static double elapsedTime; // ��� �ð�
    static bool isStopwatchRunning; // �����ġ ���� ����

    static HICON hIcon;
    static HICON hIconItem;
    static HICON hIconEnemy;
    static HICON hIconClear;

    static int printBlock;
};