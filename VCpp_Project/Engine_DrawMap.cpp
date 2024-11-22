#include "Engine_DrawMap.h"

/// 1 : 벽
/// 2 : 아이템


void Engine_DrawMap::settingMap()
{
    // 예제: 첫 번째 행과 두 번째 행에 벽과 아이템을 배치
    for (int i = 0; i < 50; i++)
    {
        EngineData::mapGrid[12][i] = 1;     // (0, 1) 위치에 벽을 설정
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
    EngineData::mapGrid[1][3] = 2; // (1, 2) 위치에 아이템을 설정
}
void Engine_DrawMap::drawMap(HDC hMemDC)
{
    for (int i = 0; i < GRID_ROWS; i++)
    {
        for (int j = 0; j < GRID_COLS; j++)
        {
            RECT cellRect = {
                j * CELL_WIDTH + EngineData::mapOffset,
                i * CELL_HEIGHT + EngineData::mapOffset,
                (j + 1) * CELL_WIDTH + EngineData::mapOffset,
                (i + 1) * CELL_HEIGHT + EngineData::mapOffset
            };

            if (EngineData::mapGrid[i][j] == 1) // 벽
            {
                // 벽은 RECT로 색 채우기
                HBRUSH wallBrush = CreateSolidBrush(RGB(100, 100, 100));
                FillRect(hMemDC, &cellRect, wallBrush);
                DeleteObject(wallBrush);
            }
            else
            {
                // 빈 공간이나 다른 값은 선으로만 격자 그리기
                HPEN gridPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 200)); // 회색 선
                HPEN oldPen = (HPEN)SelectObject(hMemDC, gridPen);

                // 상단 선
                MoveToEx(hMemDC, cellRect.left, cellRect.top, NULL);
                LineTo(hMemDC, cellRect.right, cellRect.top);

                // 하단 선
                MoveToEx(hMemDC, cellRect.left, cellRect.bottom, NULL);
                LineTo(hMemDC, cellRect.right, cellRect.bottom);

                // 왼쪽 선
                MoveToEx(hMemDC, cellRect.left, cellRect.top, NULL);
                LineTo(hMemDC, cellRect.left, cellRect.bottom);

                // 오른쪽 선
                MoveToEx(hMemDC, cellRect.right, cellRect.top, NULL);
                LineTo(hMemDC, cellRect.right, cellRect.bottom);

                SelectObject(hMemDC, oldPen); // 이전 펜으로 복원
                DeleteObject(gridPen);
            }
        }
    }

    WCHAR buffer[50];
    Rectangle(hMemDC,0, 0, 50, 650);

    /// 각 RECT 격자별 인덱스 표시
    for (int i = 0; i < GRID_ROWS; i++) {
        swprintf_s(buffer, 50, L"%d", i);
        TextOut(hMemDC, 20, 70 + i * EngineData::mapOffset, buffer, wcslen(buffer));
    }

    for (int i = 0; i < GRID_COLS; i++) {
        swprintf_s(buffer, 50, L"%d", i);
        TextOut(hMemDC, 70 + i * EngineData::mapOffset, 20, buffer, wcslen(buffer));
    }
}

void Engine_DrawMap::drawInfo(HDC hMemDC, int mouse_X, int mouse_Y)
{
    WCHAR buffer[50];

    /// 현재 가속도
    swprintf_s(buffer, 50, L"현재 중력가속도 : %.2f", EngineData::gravityVelocity);
    TextOut(hMemDC, 10, 780, buffer, wcslen(buffer));

    swprintf_s(buffer, 50, L"현재 이동가속도 : %.2f", EngineData::playerSpeed);
    TextOut(hMemDC, 10, 810, buffer, wcslen(buffer));

    // 현 마우스 좌표
    swprintf_s(buffer, 50, L"현재 X 좌표 : %d", (EngineData::userBox.left + EngineData::userBox.right) / 2);
    TextOut(hMemDC, 200, 780, buffer, wcslen(buffer));

    swprintf_s(buffer, 50, L"현재 Y 좌표 : %d", (EngineData::userBox.top + EngineData::userBox.bottom) / 2);
    TextOut(hMemDC, 200, 810, buffer, wcslen(buffer));

   // 파란색 펜 생성
HPEN hBluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255)); // 파란색
HPEN hOldPen = (HPEN)SelectObject(hMemDC, hBluePen); // 이전 펜 저장

// 첫 번째 선 그리기 (파란색)
MoveToEx(hMemDC, 50, (EngineData::userBox.top + EngineData::userBox.bottom) / 2, NULL);
LineTo(hMemDC, (EngineData::userBox.left + EngineData::userBox.right) / 2, (EngineData::userBox.top + EngineData::userBox.bottom) / 2);

// 빨간색 펜 생성
HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // 빨간색
SelectObject(hMemDC, hRedPen); // 빨간색 펜으로 변경

// 두 번째 선 그리기 (빨간색)
MoveToEx(hMemDC, (EngineData::userBox.left + EngineData::userBox.right) / 2, 50, NULL);
LineTo(hMemDC, (EngineData::userBox.left + EngineData::userBox.right) / 2, (EngineData::userBox.top + EngineData::userBox.bottom) / 2);

// 이전 펜 복원 및 생성한 펜 삭제
SelectObject(hMemDC, hOldPen); 
DeleteObject(hBluePen);
DeleteObject(hRedPen); }