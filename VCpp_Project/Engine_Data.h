#pragma once

#include "Resource.h"
#include "framework.h"
#include "Engine_Data.h"

class EngineData {
public:
    static int mapGrid[GRID_ROWS][GRID_COLS];   // 2차원 맵
    static int mapOffset;                       // RECT 간격

    static float playerSpeed;                   // 플레이어 속도              
    static float gravityVelocity;               // 중력 값

    static RECT userBox;                        // 플레이어 RECT
    static HWND playButton;
    static bool developMode;

    static HBITMAP hBackground;

    static float imageMove;

    static int playerHeart;

    static DWORD playTimer;
    static double elapsedTime; // 경과 시간
    static bool isStopwatchRunning; // 스톱워치 동작 여부

    static HICON hIcon;
    static HICON hIconItem;
    static HICON hIconEnemy;
    static HICON hIconClear;

    static int printBlock;
};