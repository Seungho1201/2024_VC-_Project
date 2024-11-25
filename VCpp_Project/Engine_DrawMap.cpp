#include "Engine_DrawMap.h"

/// 1 : 벽
/// 2 : 아이템
/// 3 : 적
/// 4 : 클리어 지점


void Engine_DrawMap::settingMap()
{
    /// EngineData::mapGrid[y][x]
    /// developMode 켜서 좌표 확인이 편함
    
    for (int x = 0; x < 50; x++)
    {
        EngineData::mapGrid[12][x] = 1;     
    }
    /*
    for (int x = 0; x < 26; x++)
    {
        EngineData::mapGrid[0][x] = 1;
    }
    */
    for (int y = 7; y < 12; y++)
    {
        EngineData::mapGrid[y][3] = 1;
    }

    for (int x = 4; x < 6; x++)
    {
        EngineData::mapGrid[7][x] = 1;
    }

    for (int x = 0; x < 4; x++)
    {
        EngineData::mapGrid[4][x] = 1;
    }

    for (int y = 3; y < 7; y++)
    {
        EngineData::mapGrid[y][5] = 1;
    }

    for (int y = 0; y < 8; y++)
    {
        EngineData::mapGrid[y][8] = 1;
    }

    for (int y = 10; y <12; y++)
    {
        EngineData::mapGrid[y][7] = 1;
    }

    for (int x = 11; x < 15; x++)
    {
        EngineData::mapGrid[2][x] = 1;
    }

    EngineData::mapGrid[3][6] = 1;

    for (int x = 14; x < 25; x++)
    {
        EngineData::mapGrid[3][x] = 1;
    }

    for (int x = 15; x < 27; x++)
    {
        EngineData::mapGrid[7][x] = 1;
    }





    EngineData::mapGrid[10][2] = 2; // (1, 2) 위치에 아이템을 설정
    EngineData::mapGrid[11][9] = 2; // (1, 2) 위치에 아이템을 설정
    EngineData::mapGrid[6][10] = 2; // (1, 2) 위치에 아이템을 설정

    for (int y = 3; y < 7; y++)
    {
        EngineData::mapGrid[y][11] = 3;
    }
    for (int y = 7; y < 12; y++)
    {
        EngineData::mapGrid[y][10] = 3;
    }

    EngineData::mapGrid[7][7] = 3; 
    EngineData::mapGrid[11][6] = 3;

    //EngineData::mapGrid[1][17] = 3;
    EngineData::mapGrid[2][17] = 3;

    //EngineData::mapGrid[1][11] = 3;


    //EngineData::mapGrid[1][20] = 3;
    EngineData::mapGrid[2][20] = 3;

    EngineData::mapGrid[1][23] = 3;


    EngineData::mapGrid[11][25] = 4; // (1, 2) 위치에 아이템을 설정
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
                /*
                // 벽은 RECT로 색 채우기
                HBRUSH wallBrush = CreateSolidBrush(RGB(100, 100, 100));
                FillRect(hMemDC, &cellRect, wallBrush);
                DeleteObject(wallBrush);
                */
                /// 아이콘 로드
                HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL),
                    MAKEINTRESOURCE(IDI_WALLBRICK),
                    IMAGE_ICON,
                    50,
                    50,
                    0
                );

                /// 아이콘 그리기
                DrawIconEx(hMemDC,
                    j * CELL_WIDTH + EngineData::mapOffset,
                    i * CELL_HEIGHT + EngineData::mapOffset,
                    hIcon, 50, 50, 0, NULL, DI_NORMAL);

                /// 아이콘 자원 해제
                DestroyIcon(hIcon);
            }
            else if (EngineData::mapGrid[i][j] == 2) // 아이템
            {
                /*
                HPEN hNullPen = (HPEN)GetStockObject(NULL_PEN); // 투명한 펜 생성
                HPEN hOldPen = (HPEN)SelectObject(hMemDC, hNullPen); // 이전 펜 저장
                // 아이템을 초록색 원으로 표시
                HBRUSH itemBrush = CreateSolidBrush(RGB(0, 255, 0)); // 초록색
                HBRUSH oldBrush = (HBRUSH)SelectObject(hMemDC, itemBrush);

                Ellipse(hMemDC, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom);
                // 이전 펜 복원
                SelectObject(hMemDC, hOldPen);

                SelectObject(hMemDC, oldBrush); // 이전 브러시로 복원
                DeleteObject(itemBrush);
                */

                HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL),
                    MAKEINTRESOURCE(IDI_JUMPBRICK),
                    IMAGE_ICON,
                    50,
                    50,
                    0
                );

                /// 아이콘 그리기
                DrawIconEx(hMemDC,
                    j * CELL_WIDTH + EngineData::mapOffset,
                    i * CELL_HEIGHT + EngineData::mapOffset,
                    hIcon, 50, 50, 0, NULL, DI_NORMAL);

                /// 아이콘 자원 해제
                DestroyIcon(hIcon);
            }
            else if (EngineData::mapGrid[i][j] == 3) // 장애물
            {
                /*
                HPEN hNullPen = (HPEN)GetStockObject(NULL_PEN); // 투명한 펜 생성
                HPEN hOldPen = (HPEN)SelectObject(hMemDC, hNullPen); // 이전 펜 저장
                // 아이템을 초록색 원으로 표시
                HBRUSH itemBrush = CreateSolidBrush(RGB(255, 0, 0)); // 초록색
                HBRUSH oldBrush = (HBRUSH)SelectObject(hMemDC, itemBrush);

                Rectangle(hMemDC, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom);
                // 이전 펜 복원
                SelectObject(hMemDC, hOldPen);

                SelectObject(hMemDC, oldBrush); // 이전 브러시로 복원
                DeleteObject(itemBrush);
                */
                /// 아이콘 로드
                HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL),
                    MAKEINTRESOURCE(IDI_TRAPBRICK),
                    IMAGE_ICON,
                    50,
                    50,
                    0
                );

                /// 아이콘 그리기
                DrawIconEx(hMemDC,
                    j * CELL_WIDTH + EngineData::mapOffset,
                    i * CELL_HEIGHT + EngineData::mapOffset,
                    hIcon, 50, 50, 0, NULL, DI_NORMAL);

                /// 아이콘 자원 해제
                DestroyIcon(hIcon);
            }
            else if (EngineData::mapGrid[i][j] == 4) // 클리어 지점
            {
                /*
                HPEN hNullPen = (HPEN)GetStockObject(NULL_PEN); // 투명한 펜 생성
                HPEN hOldPen = (HPEN)SelectObject(hMemDC, hNullPen); // 이전 펜 저장
                // 아이템을 초록색 원으로 표시
                HBRUSH itemBrush = CreateSolidBrush(RGB(0, 0, 150)); // 초록색
                HBRUSH oldBrush = (HBRUSH)SelectObject(hMemDC, itemBrush);

                Rectangle(hMemDC, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom);
                // 이전 펜 복원
                SelectObject(hMemDC, hOldPen);

                SelectObject(hMemDC, oldBrush); // 이전 브러시로 복원
                DeleteObject(itemBrush);
                */
                /// 아이콘 로드
                HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL),
                    MAKEINTRESOURCE(IDI_EXITBRICK),
                    IMAGE_ICON,
                    50,
                    50,
                    0
                );

                /// 아이콘 그리기
                DrawIconEx(hMemDC,
                    j* CELL_WIDTH + EngineData::mapOffset,
                    i* CELL_HEIGHT + EngineData::mapOffset,
                    hIcon, 50, 50, 0, NULL, DI_NORMAL);

                /// 아이콘 자원 해제
                DestroyIcon(hIcon);
            }
            else
            {
                if (EngineData::developMode)
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
    }
    HPEN hNullPen = (HPEN)GetStockObject(NULL_PEN); // 투명한 펜 생성
    HPEN hOldPen = (HPEN)SelectObject(hMemDC, hNullPen); // 이전 펜 저장

    Rectangle(hMemDC, 0, 0, 50, 710);
    Rectangle(hMemDC, 1400, 0, 1450, 710);

    // 이전 펜 복원
    SelectObject(hMemDC, hOldPen);

    if (EngineData::developMode)
    {
        WCHAR buffer[50];
       
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
   
}

void Engine_DrawMap::drawInfo(HDC hMemDC)
{
    if (EngineData::developMode) {
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
        DeleteObject(hRedPen);
    }
}

void Engine_DrawMap::drawHeart(HDC hMemDC)
{
    int i = 0;

    for (int y = EngineData::playerHeart; y < 3; y++)
    {
        /// 아이콘 로드
        HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL),
            MAKEINTRESOURCE(IDI_EMPTYHEARTICON),
            IMAGE_ICON,
            50,
            50,
            0
        );

        /// 아이콘 그리기
        DrawIconEx(hMemDC,
            50 + y * 60,
            720,
            hIcon, 50, 50, 0, NULL, DI_NORMAL);

        /// 아이콘 자원 해제
        DestroyIcon(hIcon);
    }

    for (i; i < EngineData::playerHeart; i++)
    {
        /// 아이콘 로드
        HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL),
            MAKEINTRESOURCE(IDI_HEARTICON),
            IMAGE_ICON,
            50,
            50,
            0
        );

        /// 아이콘 그리기
        DrawIconEx(hMemDC,
           50 + i * 60,
           720,
           hIcon, 50, 50, 0, NULL, DI_NORMAL);

        /// 아이콘 자원 해제
        DestroyIcon(hIcon);
    }

}