#include "Engine_DrawMap.h"

/// 1 : ��
/// 2 : ������
/// 3 : ��
/// 4 : Ŭ���� ����


void Engine_DrawMap::settingMap()
{
    /// EngineData::mapGrid[y][x]
    /// developMode �Ѽ� ��ǥ Ȯ���� ����
    
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


    EngineData::mapGrid[10][2] = 2; // (1, 2) ��ġ�� �������� ����
    EngineData::mapGrid[11][9] = 2; // (1, 2) ��ġ�� �������� ����
    EngineData::mapGrid[6][10] = 2; // (1, 2) ��ġ�� �������� ����
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

    EngineData::mapGrid[11][25] = 4; // (1, 2) ��ġ�� �������� ����
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

            if (EngineData::mapGrid[i][j] == 1) // ��
            {
                /// ������ �׸���
                DrawIconEx(hMemDC,
                    j * CELL_WIDTH + EngineData::mapOffset,
                    i * CELL_HEIGHT + EngineData::mapOffset,
                    EngineData::hIcon, 50, 50, 0, NULL, DI_NORMAL);

            }
            else if (EngineData::mapGrid[i][j] == 2) // ������
            {
                DrawIconEx(hMemDC,
                    j * CELL_WIDTH + EngineData::mapOffset,
                    i * CELL_HEIGHT + EngineData::mapOffset,
                    EngineData::hIconItem, 50, 50, 0, NULL, DI_NORMAL);
            }
            else if (EngineData::mapGrid[i][j] == 3) // ��ֹ�
            {
                DrawIconEx(hMemDC,
                    j * CELL_WIDTH + EngineData::mapOffset,
                    i * CELL_HEIGHT + EngineData::mapOffset,
                    EngineData::hIconEnemy, 50, 50, 0, NULL, DI_NORMAL);
            }
            else if (EngineData::mapGrid[i][j] == 4) // Ŭ���� ����
            {

                /// ������ �׸���

                DrawIconEx(hMemDC,
                    j* CELL_WIDTH + EngineData::mapOffset,
                    i* CELL_HEIGHT + EngineData::mapOffset,
                    EngineData::hIconClear, 50, 50, 0, NULL, DI_NORMAL);

            }
            else
            {
                if (EngineData::developMode)
                {
                    // �� �����̳� �ٸ� ���� �����θ� ���� �׸���
                    HPEN gridPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 200)); // ȸ�� ��
                    HPEN oldPen = (HPEN)SelectObject(hMemDC, gridPen);

                    // ��� ��
                    MoveToEx(hMemDC, cellRect.left, cellRect.top, NULL);
                    LineTo(hMemDC, cellRect.right, cellRect.top);

                    // �ϴ� ��
                    MoveToEx(hMemDC, cellRect.left, cellRect.bottom, NULL);
                    LineTo(hMemDC, cellRect.right, cellRect.bottom);

                    // ���� ��
                    MoveToEx(hMemDC, cellRect.left, cellRect.top, NULL);
                    LineTo(hMemDC, cellRect.left, cellRect.bottom);

                    // ������ ��
                    MoveToEx(hMemDC, cellRect.right, cellRect.top, NULL);
                    LineTo(hMemDC, cellRect.right, cellRect.bottom);

                    SelectObject(hMemDC, oldPen); // ���� ������ ����
                    DeleteObject(gridPen);
                }
            }
        }
    }

    HPEN hNullPen = (HPEN)GetStockObject(NULL_PEN); // ������ �� ����
    HPEN hOldPen = (HPEN)SelectObject(hMemDC, hNullPen); // ���� �� ����

    Rectangle(hMemDC, 0, 0, 50, 710);
    Rectangle(hMemDC, 1400, 0, 1450, 710);

    // ���� �� ����
    SelectObject(hMemDC, hOldPen);

    WCHAR buffer[50];

    /// ���� ����
    swprintf_s(buffer, 50, L"���� : C");
    TextOut(hMemDC, 275, 720, buffer, wcslen(buffer));

    swprintf_s(buffer, 50, L"�̵� : �� ��");
    TextOut(hMemDC, 275, 750, buffer, wcslen(buffer));

    /// �ɸ� �ð�
    swprintf_s(buffer, 50, L"Ÿ�̸� : %05.2f", EngineData::elapsedTime);
    TextOut(hMemDC, 275, 775, buffer, wcslen(buffer));

    if (EngineData::developMode)
    {
        WCHAR buffer[50];
       
        /// �� RECT ���ں� �ε��� ǥ��
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

        /// ���� ���ӵ�
        swprintf_s(buffer, 50, L"���� �߷°��ӵ� : %.2f", EngineData::gravityVelocity);
        TextOut(hMemDC, 10, 780, buffer, wcslen(buffer));

        swprintf_s(buffer, 50, L"���� �̵����ӵ� : %.2f", EngineData::playerSpeed);
        TextOut(hMemDC, 10, 810, buffer, wcslen(buffer));

        // �� ���콺 ��ǥ
        swprintf_s(buffer, 50, L"���� X ��ǥ : %d", (EngineData::userBox.left + EngineData::userBox.right) / 2);
        TextOut(hMemDC, 200, 810, buffer, wcslen(buffer));

        swprintf_s(buffer, 50, L"���� Y ��ǥ : %d", (EngineData::userBox.top + EngineData::userBox.bottom) / 2);
        TextOut(hMemDC, 400, 810, buffer, wcslen(buffer));

        // �Ķ��� �� ����
        HPEN hBluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255)); // �Ķ���
        HPEN hOldPen = (HPEN)SelectObject(hMemDC, hBluePen); // ���� �� ����

        // ù ��° �� �׸��� (�Ķ���)
        MoveToEx(hMemDC, 50, (EngineData::userBox.top + EngineData::userBox.bottom) / 2, NULL);
        LineTo(hMemDC, (EngineData::userBox.left + EngineData::userBox.right) / 2, (EngineData::userBox.top + EngineData::userBox.bottom) / 2);

        // ������ �� ����
        HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // ������
        SelectObject(hMemDC, hRedPen); // ������ ������ ����

        // �� ��° �� �׸��� (������)
        MoveToEx(hMemDC, (EngineData::userBox.left + EngineData::userBox.right) / 2, 50, NULL);
        LineTo(hMemDC, (EngineData::userBox.left + EngineData::userBox.right) / 2, (EngineData::userBox.top + EngineData::userBox.bottom) / 2);

        // ���� �� ���� �� ������ �� ����
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
        /// ������ �׸���
        DrawIconEx(hMemDC, 50 + y * 60, 720, hIconEmptyHeart,
            50, 50, 0, NULL, DI_NORMAL);
    }

    for (i; i < EngineData::playerHeart; i++)
    {
        /// ������ �׸���
        DrawIconEx(hMemDC, 50 + i * 60, 720, hIconHeart,
            50, 50, 0, NULL, DI_NORMAL);
    }
}

void Engine_DrawMap::drawGuide(HDC hMemDC)
{
    Rectangle(hMemDC, 0, 0, 1500, 900);

    WCHAR buffer[250];

    /// �� ������ �׸���
    DrawIconEx(hMemDC, 150, 50, EngineData::hIcon, 50, 50, 0, NULL, DI_NORMAL);

    /// ���� ����
    swprintf_s(buffer, 50, L"�� : ����� �� ���� ��ֹ��Դϴ�");
    TextOut(hMemDC, 250, 70, buffer, wcslen(buffer));

    /// ������ ������ �׸���
    DrawIconEx(hMemDC, 150, 150, EngineData::hIconItem, 50, 50, 0, NULL, DI_NORMAL);

    swprintf_s(buffer, 50, L"������ : ���� ������ �����ִ� �������Դϴ�.");
    TextOut(hMemDC, 250, 170, buffer, wcslen(buffer));

    /// ��ֹ� ������ �׸���
    DrawIconEx(hMemDC, 150, 250, EngineData::hIconEnemy, 50, 50, 0, NULL, DI_NORMAL);

    swprintf_s(buffer, 50, L"��ֹ� : �ε����� ������� �پ��� �ʱ� ��ġ�� ���ư��ϴ�.");
    TextOut(hMemDC, 250, 270, buffer, wcslen(buffer));

    /// Ŭ���� ������ �׸���
    DrawIconEx(hMemDC, 150, 350, EngineData::hIconClear, 50, 50, 0, NULL, DI_NORMAL);

    swprintf_s(buffer, 50, L"Ŭ���� : �� ������ ���� �� ������ Ŭ���� �˴ϴ�.");
    TextOut(hMemDC, 250, 370, buffer, wcslen(buffer));

    swprintf_s(buffer, 150, L"�� ������ ������: Alfredo Hernandez - Flaticon : https://www.flaticon.com/kr/free-icons/\"title=\"���� ������");
    TextOut(hMemDC, 50, 600, buffer, wcslen(buffer));

    swprintf_s(buffer, 150, L"������ ������ ������: Freepik - Flaticon : https://www.flaticon.com/kr/free-icons/\"title=\"Ʈ������ ������");
    TextOut(hMemDC, 50, 630, buffer, wcslen(buffer));

    swprintf_s(buffer, 150, L"��ֹ� ������ ������: SA Family - Flaticon : https://www.flaticon.com/kr/free-icons/\"title=\"���� ������");
    TextOut(hMemDC, 50, 660, buffer, wcslen(buffer));

    swprintf_s(buffer, 150, L"Ŭ���� ������ ������: BankSeeNgern - Flaticon : https://www.flaticon.com/kr/free-icons/\"title=\"Ż�� ������");
    TextOut(hMemDC, 50, 690, buffer, wcslen(buffer));

    swprintf_s(buffer, 200, L"����ũ ������ ������ :June Design - Flaticon : https://www.flaticon.com/kr/free-icons/\"title=\"���� ������");
    TextOut(hMemDC, 50, 720, buffer, wcslen(buffer));



    MoveToEx(hMemDC, 800, 50, NULL);
    LineTo(hMemDC, 800, 800);

    swprintf_s(buffer, 50, L"�ϰ� �� ���� ������ �������� ����Ű �Է� ��");
    TextOut(hMemDC, 930, 500, buffer, wcslen(buffer));

    swprintf_s(buffer, 50, L"����Ʈ�� �Բ� õõ�� �ϰ��մϴ�");
    TextOut(hMemDC, 930, 530, buffer, wcslen(buffer));
}