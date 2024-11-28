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

    for (int x = 20; x < 27; x++)
    {
        EngineData::mapGrid[7][x] = 1;
    }

    EngineData::mapGrid[8][20] = 1;
    EngineData::mapGrid[9][20] = 1;
    EngineData::mapGrid[10][20] = 1;

    for (int y = 5; y < 11; y++)
    {
        EngineData::mapGrid[y][13] = 1;
    }


    EngineData::mapGrid[10][2] = 2; // (1, 2) 위치에 아이템을 설정
    EngineData::mapGrid[11][9] = 2; // (1, 2) 위치에 아이템을 설정
    EngineData::mapGrid[6][10] = 2; // (1, 2) 위치에 아이템을 설정
    EngineData::mapGrid[9][18] = 2;
    EngineData::mapGrid[9][14] = 2;

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
    EngineData::mapGrid[2][17] = 3;
    EngineData::mapGrid[2][20] = 3;
    EngineData::mapGrid[0][23] = 3;
    EngineData::mapGrid[1][23] = 3;
    EngineData::mapGrid[10][23] = 3;
    EngineData::mapGrid[11][23] = 3;
    EngineData::mapGrid[6][16] = 3;

    for (int x = 14; x < 20; x++)
    {
        EngineData::mapGrid[10][x] = 3;
    }

    EngineData::mapGrid[11][25] = 4; // (1, 2) 위치에 아이템을 설정
}

void Engine_DrawMap::drawMap(HDC hMemDC)
{
    static HICON hIcon;


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
                /// 아이콘 그리기
                DrawIconEx(hMemDC,
                    j * CELL_WIDTH + EngineData::mapOffset,
                    i * CELL_HEIGHT + EngineData::mapOffset,
                    EngineData::hIcon, 50, 50, 0, NULL, DI_NORMAL);

            }
            else if (EngineData::mapGrid[i][j] == 2) // 아이템
            {
                DrawIconEx(hMemDC,
                    j * CELL_WIDTH + EngineData::mapOffset,
                    i * CELL_HEIGHT + EngineData::mapOffset,
                    EngineData::hIconItem, 50, 50, 0, NULL, DI_NORMAL);
            }
            else if (EngineData::mapGrid[i][j] == 3) // 장애물
            {
                DrawIconEx(hMemDC,
                    j * CELL_WIDTH + EngineData::mapOffset,
                    i * CELL_HEIGHT + EngineData::mapOffset,
                    EngineData::hIconEnemy, 50, 50, 0, NULL, DI_NORMAL);
            }
            else if (EngineData::mapGrid[i][j] == 4) // 클리어 지점
            {

                /// 아이콘 그리기

                DrawIconEx(hMemDC,
                    j* CELL_WIDTH + EngineData::mapOffset,
                    i* CELL_HEIGHT + EngineData::mapOffset,
                    EngineData::hIconClear, 50, 50, 0, NULL, DI_NORMAL);

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

    WCHAR buffer[50];

    /// 게임 정보
    swprintf_s(buffer, 50, L"점프 : C");
    TextOut(hMemDC, 275, 720, buffer, wcslen(buffer));

    swprintf_s(buffer, 50, L"이동 : ← →");
    TextOut(hMemDC, 275, 750, buffer, wcslen(buffer));

    /// 걸린 시간
    swprintf_s(buffer, 50, L"타이머 : %05.2f", EngineData::elapsedTime);
    TextOut(hMemDC, 275, 775, buffer, wcslen(buffer));

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
        TextOut(hMemDC, 200, 810, buffer, wcslen(buffer));

        swprintf_s(buffer, 50, L"현재 Y 좌표 : %d", (EngineData::userBox.top + EngineData::userBox.bottom) / 2);
        TextOut(hMemDC, 400, 810, buffer, wcslen(buffer));

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
    static HICON hIconEmptyHeart = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_EMPTYHEARTICON),IMAGE_ICON, 50, 50, 0);
    static HICON hIconHeart = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_HEARTICON), IMAGE_ICON, 50, 50, 0 );

    for (int y = EngineData::playerHeart; y < 3; y++)
    {
        /// 아이콘 그리기
        DrawIconEx(hMemDC, 50 + y * 60, 720, hIconEmptyHeart,
            50, 50, 0, NULL, DI_NORMAL);
    }

    for (i; i < EngineData::playerHeart; i++)
    {
        /// 아이콘 그리기
        DrawIconEx(hMemDC, 50 + i * 60, 720, hIconHeart,
            50, 50, 0, NULL, DI_NORMAL);
    }
}

void Engine_DrawMap::drawGuide(HDC hMemDC)
{
    Rectangle(hMemDC, 0, 0, 1500, 900);

    WCHAR buffer[250];

    /// 벽 아이콘 그리기
    DrawIconEx(hMemDC, 150, 50, EngineData::hIcon, 50, 50, 0, NULL, DI_NORMAL);

    /// 게임 정보
    swprintf_s(buffer, 50, L"벽 : 통과할 수 없는 장애물입니다");
    TextOut(hMemDC, 250, 70, buffer, wcslen(buffer));

    /// 아이템 아이콘 그리기
    DrawIconEx(hMemDC, 150, 150, EngineData::hIconItem, 50, 50, 0, NULL, DI_NORMAL);

    swprintf_s(buffer, 50, L"점프대 : 높이 점프를 시켜주는 아이템입니다.");
    TextOut(hMemDC, 250, 170, buffer, wcslen(buffer));

    /// 장애물 아이콘 그리기
    DrawIconEx(hMemDC, 150, 250, EngineData::hIconEnemy, 50, 50, 0, NULL, DI_NORMAL);

    swprintf_s(buffer, 50, L"장애물 : 부딪히면 생명력이 줄어들며 초기 위치로 돌아갑니다.");
    TextOut(hMemDC, 250, 270, buffer, wcslen(buffer));

    /// 클리어 아이콘 그리기
    DrawIconEx(hMemDC, 150, 350, EngineData::hIconClear, 50, 50, 0, NULL, DI_NORMAL);

    swprintf_s(buffer, 50, L"클리어 : 이 지점에 도달 시 게임은 클리어 됩니다.");
    TextOut(hMemDC, 250, 370, buffer, wcslen(buffer));

    swprintf_s(buffer, 150, L"벽 아이콘 제작자: Alfredo Hernandez - Flaticon : https://www.flaticon.com/kr/free-icons/\"title=\"벽돌 아이콘");
    TextOut(hMemDC, 50, 600, buffer, wcslen(buffer));

    swprintf_s(buffer, 150, L"점프대 아이콘 제작자: Freepik - Flaticon : https://www.flaticon.com/kr/free-icons/\"title=\"트램폴린 아이콘");
    TextOut(hMemDC, 50, 630, buffer, wcslen(buffer));

    swprintf_s(buffer, 150, L"장애물 아이콘 제작자: SA Family - Flaticon : https://www.flaticon.com/kr/free-icons/\"title=\"가시 아이콘");
    TextOut(hMemDC, 50, 660, buffer, wcslen(buffer));

    swprintf_s(buffer, 150, L"클리어 아이콘 제작자: BankSeeNgern - Flaticon : https://www.flaticon.com/kr/free-icons/\"title=\"탈출 아이콘");
    TextOut(hMemDC, 50, 690, buffer, wcslen(buffer));

    swprintf_s(buffer, 200, L"스파크 아이콘 제작자 :June Design - Flaticon : https://www.flaticon.com/kr/free-icons/\"title=\"새해 아이콘");
    TextOut(hMemDC, 50, 720, buffer, wcslen(buffer));



    MoveToEx(hMemDC, 800, 50, NULL);
    LineTo(hMemDC, 800, 800);

    swprintf_s(buffer, 50, L"하강 시 벽과 접촉한 방향으로 방향키 입력 시");
    TextOut(hMemDC, 930, 500, buffer, wcslen(buffer));

    swprintf_s(buffer, 50, L"이펙트와 함께 천천히 하강합니다");
    TextOut(hMemDC, 930, 530, buffer, wcslen(buffer));
}