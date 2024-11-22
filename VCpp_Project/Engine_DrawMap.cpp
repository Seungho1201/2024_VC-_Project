#include "Engine_DrawMap.h"

/// 1 : ��
/// 2 : ������


void Engine_DrawMap::settingMap()
{
    // ����: ù ��° ��� �� ��° �࿡ ���� �������� ��ġ
    for (int i = 0; i < 50; i++)
    {
        EngineData::mapGrid[12][i] = 1;     // (0, 1) ��ġ�� ���� ����
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


    EngineData::mapGrid[1][2] = 2; // (1, 2) ��ġ�� �������� ����
    EngineData::mapGrid[1][3] = 2; // (1, 2) ��ġ�� �������� ����
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

            if (EngineData::mapGrid[i][j] == 1) // ��
            {
                // ���� RECT�� �� ä���
                HBRUSH wallBrush = CreateSolidBrush(RGB(100, 100, 100));
                FillRect(hMemDC, &cellRect, wallBrush);
                DeleteObject(wallBrush);
            }
            else
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

    WCHAR buffer[50];
    Rectangle(hMemDC,0, 0, 50, 650);

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

void Engine_DrawMap::drawInfo(HDC hMemDC, int mouse_X, int mouse_Y)
{
    WCHAR buffer[50];

    /// ���� ���ӵ�
    swprintf_s(buffer, 50, L"���� �߷°��ӵ� : %.2f", EngineData::gravityVelocity);
    TextOut(hMemDC, 10, 780, buffer, wcslen(buffer));

    swprintf_s(buffer, 50, L"���� �̵����ӵ� : %.2f", EngineData::playerSpeed);
    TextOut(hMemDC, 10, 810, buffer, wcslen(buffer));

    // �� ���콺 ��ǥ
    swprintf_s(buffer, 50, L"���� X ��ǥ : %d", (EngineData::userBox.left + EngineData::userBox.right) / 2);
    TextOut(hMemDC, 200, 780, buffer, wcslen(buffer));

    swprintf_s(buffer, 50, L"���� Y ��ǥ : %d", (EngineData::userBox.top + EngineData::userBox.bottom) / 2);
    TextOut(hMemDC, 200, 810, buffer, wcslen(buffer));

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
DeleteObject(hRedPen); }