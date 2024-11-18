// VCpp_Project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "VCpp_Project.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_VCPPPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VCPPPROJECT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VCPPPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_VCPPPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

const int offset = 50; // 상단 및 왼쪽 오프셋 설정

bool IsCollidingWithWall(RECT player, int grid[GRID_ROWS][GRID_COLS], int dx, int dy)
{
    RECT newPlayerPosition = { player.left + dx, player.top + dy, player.right + dx, player.bottom + dy };

    // 플레이어의 위치를 기준으로 검사할 격자 영역 계산
    int startRow =  max(0, (newPlayerPosition.top - offset) / CELL_HEIGHT);
    int endRow =    min(GRID_ROWS - 1, (newPlayerPosition.bottom - offset) / CELL_HEIGHT);
    int startCol =  max(0, (newPlayerPosition.left - offset) / CELL_WIDTH);
    int endCol =    min(GRID_COLS - 1, (newPlayerPosition.right - offset) / CELL_WIDTH);

    // 지정된 범위 내의 격자만 검사
    for (int i = startRow; i <= endRow; i++)
    {
        for (int j = startCol; j <= endCol; j++)
        {
            if (EngineData::mapGrid[i][j] == 1) // 벽인 경우
            {
                RECT wallRect = { j * CELL_WIDTH + offset, i * CELL_HEIGHT + offset,
                                  (j + 1) * CELL_WIDTH + offset, (i + 1) * CELL_HEIGHT + offset };

                RECT intersection;

                if (IntersectRect(&intersection, &newPlayerPosition, &wallRect))
                {
                    return true; // 충돌 발생
                }
            }
        }
    }
    return false; // 충돌 없음
}

bool IsCollidingWithItem(RECT player, int grid[GRID_ROWS][GRID_COLS], int dx, int dy)
{
    RECT newPlayerPosition = { player.left + dx, player.top + dy, player.right + dx, player.bottom + dy };

    // 플레이어의 위치를 기준으로 검사할 격자 영역 계산
    int startRow =  max(0, (newPlayerPosition.top - offset) / CELL_HEIGHT);
    int endRow =    min(GRID_ROWS - 1, (newPlayerPosition.bottom - offset) / CELL_HEIGHT);
    int startCol =  max(0, (newPlayerPosition.left - offset) / CELL_WIDTH);
    int endCol =    min(GRID_COLS - 1, (newPlayerPosition.right - offset) / CELL_WIDTH);

    // 지정된 범위 내의 격자만 검사
    for (int i = startRow; i <= endRow; i++)
    {
        for (int j = startCol; j <= endCol; j++)
        {
            if (EngineData::mapGrid[i][j] == 2) // 아이템인 경우
            {
                RECT itemRect = { j * CELL_WIDTH + offset, i * CELL_HEIGHT + offset,
                                  (j + 1) * CELL_WIDTH + offset, (i + 1) * CELL_HEIGHT + offset };

                RECT intersection;
                if (IntersectRect(&intersection, &newPlayerPosition, &itemRect))
                {
                    return true; // 충돌 발생
                }
            }
        }
    }
    return false; // 충돌 없음
}

// 전역 변수
RECT a;

bool isJumping = false; // 점프 상태 변수
bool isInAir = true;     // 중력 적용 상태 변수

/// 마우스 좌표 알려고 임시로 만듦
int mouse_X;
int mouse_Y;

// WndProc 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static bool isMovingRight = false;
    static bool isMovingLeft = false;
    static bool isMovingUp = false;

    switch (message)
    {
    case WM_CREATE:
    {
        /// Engine_DrawMap 파일에서 맵과 아이템 구성
        Engine_DrawMap::drawMap();

        /// 중력 타이머 설정
        SetTimer(hWnd, IDT_GRAVITY_TIMER, 1, NULL);
        break;
    }
    /// 이건 마우스 좌표를 알기 위해 임시 넣음
    case WM_MOUSEMOVE:
    {
        mouse_X = LOWORD(lParam);
        mouse_Y = HIWORD(lParam);

        break;
    }
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
            case VK_RIGHT:
                isMovingRight = true;
                SetTimer(hWnd, IDT_TIMER1, 1, NULL);    /// 이동 타이머
                break;

            case VK_LEFT:
                isMovingLeft = true;
                SetTimer(hWnd, IDT_TIMER1, 1, NULL);    /// 이동 타이머
                break;

            case 'C': 
            {
                isJumping = true;        // 점프 중으로 설정
                isInAir = true;         // C 키를 누르면 공중 상태로 설정
                EngineData::gravityVelocity = -JUMP_HEIGHT;                 /// 현재 중력값을 -로 설정
               // SetTimer(hWnd, IDT_GRAVITY_TIMER, 1, NULL);     /// 타이머 적용
            }
             break;
        }
        break;
    }
    case WM_KEYUP:
    {
        switch (wParam)
        {
        case VK_RIGHT:
            isMovingRight = false;
            break;

        case VK_LEFT:
            isMovingLeft = false;
            break;

        case 'C':
            isJumping = false;
            break;
        }

        /// 입력 없을시 이동 타이머 KILL
        if (!isMovingRight && !isMovingLeft)
        {
            KillTimer(hWnd, IDT_TIMER1);    
        }
        break;
    }
    case WM_TIMER:
    {
        /// 이동 판정 타이머
        if (wParam == IDT_TIMER1)
        {
            RECT tempPlayerBox = EngineData::userBox;

            /// 방향키 이동
            if (isMovingRight)  { tempPlayerBox.left += EngineData::playerSpeed; tempPlayerBox.right += EngineData::playerSpeed; }
            if (isMovingLeft)   { tempPlayerBox.left -= EngineData::playerSpeed; tempPlayerBox.right -= EngineData::playerSpeed; }
            if (isMovingUp)     { tempPlayerBox.top -= EngineData::playerSpeed; tempPlayerBox.bottom -= EngineData::playerSpeed; }

            /// 충돌 판정은 이동에서 판정한다

            // 충돌 여부 확인
            if (!IsCollidingWithWall(tempPlayerBox, EngineData::mapGrid, 0, 0))
            {
                EngineData::userBox = tempPlayerBox; // 충돌이 없을 경우에만 이동
            }
            // 아이템 충돌 여부 확인
            if (IsCollidingWithItem(tempPlayerBox, EngineData::mapGrid, 0, 0))
            {
                //KillTimer(hWnd, IDT_TIMER1);
                //MessageBox(hWnd, L"아이템", L"아이템", MB_OK);
            }
        }

        /// 중력 타이머
        else if (wParam == IDT_GRAVITY_TIMER)
        {
            isInAir = true; // 중력 타이머가 실행될 때 공중 상태를 기본으로 설정

            /// 중력 적용
            if (isInAir)
            {
                // 가속도 적용
                EngineData::gravityVelocity += GRAVITY_ACCELERATION; // 중력 값 증가
                EngineData::playerSpeed += MOVE_ACCELERATION;       // 플레이어 속도 증가

                // 최대 가속도 제한
                if (EngineData::playerSpeed > MAX_PLAYER_SPEED)         { EngineData::playerSpeed = MAX_PLAYER_SPEED; }
                if (EngineData::gravityVelocity > MAX_GRAVITY_SPEED)    { EngineData::gravityVelocity = MAX_GRAVITY_SPEED; }

                // 충돌 여부 확인
                if (!IsCollidingWithWall(EngineData::userBox, EngineData::mapGrid, 0, EngineData::gravityVelocity))
                {
                    EngineData::userBox.top += (int)EngineData::gravityVelocity;
                    EngineData::userBox.bottom = EngineData::userBox.top + 40;
                }
                else
                {
                    // 충돌 시 중력 멈춤
                    isInAir = false;
                    EngineData::gravityVelocity = GRAVITY_SPEED;
                    EngineData::playerSpeed = BASIC_PLAYER_SPEED;
                }
            }
        }

        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    case WM_GETMINMAXINFO:
    {
        // 최소 및 최대 크기 설정
        MINMAXINFO* pMinMaxInfo = (MINMAXINFO*)lParam;
        pMinMaxInfo->ptMinTrackSize.x = 1475; // 최소 너비 설정
        pMinMaxInfo->ptMinTrackSize.y = 900; // 최소 높이 설정
        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 더블 버퍼링
        HDC hMemDC = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top);
        HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

        FillRect(hMemDC, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        // 격자와 장애물, 아이템 그리기
        
        for (int i = 0; i < GRID_ROWS; i++)
        {
            for (int j = 0; j < GRID_COLS; j++)
            {
                RECT cellRect = { 
                    j * CELL_WIDTH  + offset, 
                    i * CELL_HEIGHT + offset,
                    (j + 1) * CELL_WIDTH  + offset, 
                    (i + 1) * CELL_HEIGHT + offset 
                };

                // 각 셀의 값을 확인하고 그리기
                if (EngineData::mapGrid[i][j] == 1) // 벽
                {
                    HBRUSH wallBrush = CreateSolidBrush(RGB(100, 100, 100));
                    FillRect(hMemDC, &cellRect, wallBrush);
                    DeleteObject(wallBrush);
                }
                else if (EngineData::mapGrid[i][j] == 2) // 아이템
                {
                    HBRUSH itemBrush = CreateSolidBrush(RGB(0, 150, 0));
                    FillRect(hMemDC, &cellRect, itemBrush);
                    DeleteObject(itemBrush);
                }
                else // 빈 공간 (연한 회색 격자 표시)
                {
                    HPEN gridPen = CreatePen(PS_SOLID, 1, RGB(200, 200, 200)); // 연한 회색 펜 생성
                    HPEN oldPen = (HPEN)SelectObject(hMemDC, gridPen);
                    Rectangle(hMemDC, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom);
                    SelectObject(hMemDC, oldPen); // 원래 펜으로 복원
                    DeleteObject(gridPen);
                }
            }
        }

        // 중력 속도 표시
        WCHAR buffer[50];
        swprintf_s(buffer, 50, L"현재 중력가속도 : %.2f", EngineData::gravityVelocity);
        TextOut(hMemDC, 10, 780, buffer, wcslen(buffer));
        swprintf_s(buffer, 50, L"현재 이동가속도 : %.2f", EngineData::playerSpeed);
        TextOut(hMemDC, 10, 810, buffer, wcslen(buffer));


        /// 현 마우스 좌표
        swprintf_s(buffer, 50, L"현재 X 좌표 :  : %d", mouse_X);
        TextOut(hMemDC, 200, 780, buffer, wcslen(buffer));
        swprintf_s(buffer, 50, L"현재 Y 좌표 : %d", mouse_Y);
        TextOut(hMemDC, 200, 810, buffer, wcslen(buffer));


        for (int i = 0; i < GRID_ROWS; i++) {
            swprintf_s(buffer, 50, L"%d", i);
            TextOut(hMemDC, 20, 70 + i * offset , buffer, wcslen(buffer));
        }

        for (int i = 0; i < GRID_COLS; i++) {
            swprintf_s(buffer, 50, L"%d", i);
            TextOut(hMemDC, 70 + i * offset, 20, buffer, wcslen(buffer));
        }

        // 플레이어 그리기
        Ellipse(hMemDC, EngineData::userBox.left, EngineData::userBox.top, EngineData::userBox.right, EngineData::userBox.bottom);

        BitBlt(hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top, hMemDC, 0, 0, SRCCOPY);

        SelectObject(hMemDC, hOldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(hMemDC);

        EndPaint(hWnd, &ps);
        break;
    }

    case WM_ERASEBKGND:
        return 1; // 화면 지우기 방지

    case WM_DESTROY:
        KillTimer(hWnd, IDT_GRAVITY_TIMER); // 중력 타이머 해제
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
