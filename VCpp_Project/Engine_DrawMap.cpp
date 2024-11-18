#include "Engine_DrawMap.h"

void Engine_DrawMap::drawMap()
{
    // 예제: 첫 번째 행과 두 번째 행에 벽과 아이템을 배치
    for (int i = 0; i < 50; i++)
    {
        EngineData::mapGrid[12][i] = 1; // (0, 1) 위치에 벽을 설정
    }

    for (int y = 10; y > 6; y--)
    {
        EngineData::mapGrid[y][12] = 1;
    }
    for (int y = 9; y > 6; y--)
    {
        EngineData::mapGrid[y][12] = 1;
    }
    for (int y = 6; y > 2; y--)
    {
        EngineData::mapGrid[y][15] = 1;
    }

    for (int y = 17; y < 23; y++)
    {
        EngineData::mapGrid[5][y] = 1;
    }

    for (int y = 15; y < 24; y++)
    {
        EngineData::mapGrid[9][y] = 1;
    }
    for (int y = 3; y < 10; y++)
    {
        EngineData::mapGrid[4][y] = 1;
    }


    EngineData::mapGrid[1][2] = 2; // (1, 2) 위치에 아이템을 설정
}