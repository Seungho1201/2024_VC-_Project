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
    int startRow =  max(0, (newPlayerPosition.top - EngineData::mapOffset) / CELL_HEIGHT);
    int endRow =    min(GRID_ROWS - 1, (newPlayerPosition.bottom - EngineData::mapOffset) / CELL_HEIGHT);
    int startCol =  max(0, (newPlayerPosition.left - EngineData::mapOffset) / CELL_WIDTH);
    int endCol =    min(GRID_COLS - 1, (newPlayerPosition.right - EngineData::mapOffset) / CELL_WIDTH);

    // 지정된 범위 내의 격자만 검사
    for (int i = startRow; i <= endRow; i++)
    {
        for (int j = startCol; j <= endCol; j++)
        {
            if (EngineData::mapGrid[i][j] == 1) // 벽인 경우
            {
                RECT wallRect = { 
                    j * CELL_WIDTH  + EngineData::mapOffset,
                    i * CELL_HEIGHT + EngineData::mapOffset,
                    (j + 1) * CELL_WIDTH  + EngineData::mapOffset,
                    (i + 1) * CELL_HEIGHT + EngineData::mapOffset
                };

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
    RECT playerAround = { player.left + dx, player.top + dy, player.right + dx, player.bottom + dy };

    // 플레이어의 위치를 기준으로 검사할 격자 영역 계산
    int startRow =  max(0, (playerAround.top - EngineData::mapOffset) / CELL_HEIGHT);
    int endRow =    min(GRID_ROWS - 1, (playerAround.bottom - EngineData::mapOffset) / CELL_HEIGHT);
    int startCol =  max(0, (playerAround.left - EngineData::mapOffset) / CELL_WIDTH);
    int endCol =    min(GRID_COLS - 1, (playerAround.right - EngineData::mapOffset) / CELL_WIDTH);

    // 지정된 범위 내의 격자만 검사
    for (int i = startRow; i <= endRow; i++)
    {
        for (int j = startCol; j <= endCol; j++)
        {
            if (EngineData::mapGrid[i][j] == 2) // 아이템인 경우
            {
                /// 아이템 RECT
                RECT itemRect = { 
                    j * CELL_WIDTH + EngineData::mapOffset,
                    i * CELL_HEIGHT + EngineData::mapOffset,
                    (j + 1) * CELL_WIDTH + EngineData::mapOffset,
                    (i + 1) * CELL_HEIGHT + EngineData::mapOffset
                };

                /// 반환용 RECT
                RECT intersection;

                if (IntersectRect(&intersection, &playerAround, &itemRect))
                {
                    return true; // 충돌 발생
                }
            }
        }
    }
    return false; // 충돌 없음
}

bool IsCollidingWithEnemy(RECT player, int grid[GRID_ROWS][GRID_COLS], int dx, int dy)
{
    RECT playerAround = { player.left + dx, player.top + dy, player.right + dx, player.bottom + dy };

    // 플레이어의 위치를 기준으로 검사할 격자 영역 계산
    int startRow = max(0, (playerAround.top - EngineData::mapOffset) / CELL_HEIGHT);
    int endRow = min(GRID_ROWS - 1, (playerAround.bottom - EngineData::mapOffset) / CELL_HEIGHT);
    int startCol = max(0, (playerAround.left - EngineData::mapOffset) / CELL_WIDTH);
    int endCol = min(GRID_COLS - 1, (playerAround.right - EngineData::mapOffset) / CELL_WIDTH);

    // 지정된 범위 내의 격자만 검사
    for (int i = startRow; i <= endRow; i++)
    {
        for (int j = startCol; j <= endCol; j++)
        {
            if (EngineData::mapGrid[i][j] == 3) // 적인 경우
            {
                /// 아이템 RECT
                RECT itemRect = {
                    j * CELL_WIDTH + EngineData::mapOffset,
                    i * CELL_HEIGHT + EngineData::mapOffset,
                    (j + 1) * CELL_WIDTH + EngineData::mapOffset,
                    (i + 1) * CELL_HEIGHT + EngineData::mapOffset
                };

                /// 반환용 RECT
                RECT intersection;

                if (IntersectRect(&intersection, &playerAround, &itemRect))
                {
                    return true; // 충돌 발생
                }
            }
        }
    }
    return false; // 충돌 없음
}

bool IsCollidingWithClear(RECT player, int grid[GRID_ROWS][GRID_COLS], int dx, int dy)
{
    RECT playerAround = { player.left + dx, player.top + dy, player.right + dx, player.bottom + dy };

    // 플레이어의 위치를 기준으로 검사할 격자 영역 계산
    int startRow = max(0, (playerAround.top - EngineData::mapOffset) / CELL_HEIGHT);
    int endRow = min(GRID_ROWS - 1, (playerAround.bottom - EngineData::mapOffset) / CELL_HEIGHT);
    int startCol = max(0, (playerAround.left - EngineData::mapOffset) / CELL_WIDTH);
    int endCol = min(GRID_COLS - 1, (playerAround.right - EngineData::mapOffset) / CELL_WIDTH);

    // 지정된 범위 내의 격자만 검사
    for (int i = startRow; i <= endRow; i++)
    {
        for (int j = startCol; j <= endCol; j++)
        {
            if (EngineData::mapGrid[i][j] == 4) /// 클리어 지점
            {
                /// 아이템 RECT
                RECT itemRect = {
                    j * CELL_WIDTH + EngineData::mapOffset,
                    i * CELL_HEIGHT + EngineData::mapOffset,
                    (j + 1) * CELL_WIDTH + EngineData::mapOffset,
                    (i + 1) * CELL_HEIGHT + EngineData::mapOffset
                };

                /// 반환용 RECT
                RECT intersection;

                if (IntersectRect(&intersection, &playerAround, &itemRect))
                {
                    return true; // 충돌 발생
                }
            }
        }
    }
    return false; // 충돌 없음
}


/// 전역 변수
bool isJumping = false;     /// 점프 상태 변수
float imageMove = 0;        /// 좌우 방향키에 따라 배경 움직임

RECT clientRect;            /// 메인창 화면 크기 받아올 RECT
RECT startPoint;            /// 플레이어 위치 저장용 RECT

RECT mouseClick;            /// 클릭한 위치 저장하는 RECT
RECT a;                     /// 그냥 반환용 RECT

HBITMAP hBackground;        /// 배경 이미지 핸들


bool playMap1 = false;      /// 맵 출력 여부 변수
bool keyOn = false;         /// 키 입력 관련 변수

bool isMovingRight = false;
bool isMovingLeft = false;

/// 메인 화면 버튼
MakeButton playGameButton(500, 500, 600, 600);
MakeButton guideButton(650, 500, 750, 600);
MakeButton mainExitButton(800, 500, 950, 600);

/// 플레이 화면 내 버튼
MakeButton exitButton(1300, 725, 1400, 825);
MakeButton developButtton(1200, 725, 1300, 825);

// WndProc 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        /// 창 생성시 창 크기를 받아옴
        GetClientRect(hWnd, &clientRect);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        HDC hdc = GetDC(hWnd);

        int x = LOWORD(lParam);
        int y = HIWORD(lParam);

        /// 현재 마우스가 클릭한 좌표 기준 RECT 생성
        mouseClick.left = x;
        mouseClick.top = y;
        mouseClick.right = mouseClick.left + 1;
        mouseClick.bottom = mouseClick.top + 1;

        /// 메인 화면 플레이 버튼
        if (IntersectRect(&a, &mouseClick, &playGameButton.rectButton))
        {
            /// 시작 좌표 저장
            startPoint = EngineData::userBox;

            /// Engine_DrawMap 파일에서 맵과 아이템 구성
            Engine_DrawMap::settingMap();

            /// 중력 타이머 설정
            SetTimer(hWnd, IDT_GRAVITY_TIMER, 2, NULL);

            /// 배경 이미지 로드
            EngineData::hBackground = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_BACKGROUND2), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
           
            /// 로드 실패시 메세지 출력
            if (!EngineData::hBackground)
            {
                MessageBox(hWnd, L"배경 이미지를 로드할 수 없습니다.", L"에러", MB_OK);
            }

            /// 현재 창의 크기를 받아 이미지 움직임
            imageMove = (clientRect.left + clientRect.right) / 2.0;

            /// 맵 활성화
            playMap1 = true;

            /// 기본값으로 개발자 모드는 false
            EngineData::developMode = false;
        }

        /// 메인 화면 가이드 버튼
        else if (IntersectRect(&a, &mouseClick, &guideButton.rectButton))
        {
            MessageBox(hWnd, L"구현 예정", L"PlayGuide", MB_OK);
        }

        /// 메인 화면 나가기 버튼
        else if (IntersectRect(&a, &mouseClick, &mainExitButton.rectButton))
        {
            DestroyWindow(hWnd);    /// 프로그램 종료
        }

        /// 나가기 버튼 (플레이 시 출력 되는 버튼)
        else if (IntersectRect(&a, &mouseClick, &exitButton.rectButton))
        {
            /// 플레이 버튼 클릭시 저장한 플레이어의 처음 좌표값으로 갱신
            EngineData::userBox = startPoint;

            /// 맵 표시 false
            playMap1 = false;
        }

        /// 개발자 버튼 (플레이 시 출력 되는 버튼)
        else if (IntersectRect(&a, &mouseClick, &developButtton.rectButton))
        {
            /// 개발자 버튼을 활성화
            EngineData::developMode = !EngineData::developMode;
        }

        InvalidateRect(hWnd, NULL, TRUE);   /// 화면 무효화
    }
    break;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
            case VK_RIGHT:
                isMovingRight = true;   /// 우측 이동 변수 true
                if (!keyOn)             /// 누르는 동안 타이머 무한 생성 방지
                {
                    keyOn = true;
                    SetTimer(hWnd, IDT_TIMER1, 2, NULL);    /// 이동 타이머
                }
                break;

            case VK_LEFT:
                isMovingLeft = true;    /// 좌측 이동 변수 true
                if (!keyOn)             /// 누르는 동안 타이머 무한 생성 방지
                {
                    keyOn = true;
                    SetTimer(hWnd, IDT_TIMER1, 2, NULL);    /// 이동 타이머
                }
                break;

            case 'C': 
            {
                if (!isJumping)     /// 점프 연속 사용 불가
                {
                    isJumping = true;        // 점프 중으로 설정
                    EngineData::gravityVelocity = -JUMP_HEIGHT;                 /// 현재 중력값을 -로 설정
                }
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
            keyOn = false;
            isMovingRight = false;
            break;

        case VK_LEFT:
            keyOn = false;
            isMovingLeft = false;
            break;

        case 'C':
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
            /// 임시 RECT 선언
            RECT tempUserBox = EngineData::userBox;

            /// 방향키 이동
            if (isMovingRight)  /// 우측 방향키 이동
            { 
                /// 임시 RECT에 플레이어 이동 방향 좌표 적용
                tempUserBox.left  += EngineData::playerSpeed; 
                tempUserBox.right += EngineData::playerSpeed; 
                
                /// 벽이랑 충돌 X시
                if (!IsCollidingWithWall(tempUserBox, EngineData::mapGrid, 0, 0))
                {
                    /// 플레이 영역
                    if (!(tempUserBox.right > clientRect.right - 50))
                    {
                        imageMove += 0.15;                  /// 배경 화면도 이동
                        EngineData::userBox = tempUserBox;  /// 충돌 X 이니 유저 RECT에 임시 RECT 적용
                    }
                    break;
                }            
            }
            if (isMovingLeft)   /// 좌측 방향키 이동 
            { 
                /// 임시 RECT에 플레이어 이동 방향 좌표 적용
                tempUserBox.left  -= EngineData::playerSpeed; 
                tempUserBox.right -= EngineData::playerSpeed; 

                /// 벽이랑 충돌 X시
                if (!IsCollidingWithWall(tempUserBox, EngineData::mapGrid, 0, 0))
                {
                    /// 플레이 영역
                    if (!(tempUserBox.left < clientRect.left + 50))
                    {
                        imageMove -= 0.15;                  /// 배경 화면도 이동
                        EngineData::userBox = tempUserBox;  /// 충돌 X 이니 유저 RECT에 임시 RECT 적용
                    }     
                    break;
                }
            }
            InvalidateRect(hWnd, NULL, TRUE);   /// 이동할 때마다 화면 무효화 발생시켜 바로 갱신
        }

        /// 중력 타이머
        else if (wParam == IDT_GRAVITY_TIMER)
        {
            
            EngineData::gravityVelocity += GRAVITY_ACCELERATION;    /// 중력값 증가
            EngineData::playerSpeed += 0.01f;                       /// 플레이어 가속도 증가

            /// 최대 중력 속도 제한
            if (EngineData::gravityVelocity > MAX_GRAVITY_SPEED)
            {
                EngineData::gravityVelocity = MAX_GRAVITY_SPEED;
            }

            /// 최대 플레이어 가속도 제한
            if (EngineData::playerSpeed > MAX_PLAYER_SPEED)
            {
                EngineData::playerSpeed = MAX_PLAYER_SPEED;
            }    

            /// 중력 타이머에서의 충돌 X일 시
            if (!IsCollidingWithWall(EngineData::userBox, EngineData::mapGrid, 0, EngineData::gravityVelocity))
            {
                /// 아이템 충돌 여부 확인
                if (IsCollidingWithItem(EngineData::userBox, EngineData::mapGrid, 0, 0))
                {
                    EngineData::gravityVelocity = -10; /// JUMP_HEIGHT는 위로 튀어오를 속도
                    isJumping = false;                 /// 아이템 충돌시 점프 다시 가능
                }

                /// 장애물 충돌 여부 확인
                else if (IsCollidingWithEnemy(EngineData::userBox, EngineData::mapGrid, 0, 0))
                {
                    /// 장애물 충돌시 원래 시작지점으로 이동
                    EngineData::userBox = startPoint;

                    /// 배경 이미지 위치도 원래대로 복귀
                    imageMove = (clientRect.left + clientRect.right) / 2.0;
                }

                /// 장애물 충돌 여부 확인
                else if (IsCollidingWithClear(EngineData::userBox, EngineData::mapGrid, 0, 0))
                {
                    /// 타이머 전부 종료
                    KillTimer(hWnd, IDT_GRAVITY_TIMER);
                    KillTimer(hWnd, IDT_TIMER1);

                    /// 메세지 출력
                    MessageBox(hWnd, L"클리어", L"클리어", MB_OK);             
                }

                /// 모든 오브젝트와 충돌 없을 시 중력값 만큼 userBox 위치 갱신
                EngineData::userBox.top   += EngineData::gravityVelocity;
                EngineData::userBox.bottom = EngineData::userBox.top + 30;
            }
            else    /// 바닥과 충돌했을 때
            {
                isJumping = false;                              /// 바닥과 충돌시 점프 재사용 가능
                EngineData::playerSpeed = BASIC_PLAYER_SPEED;   /// 바닥과 충돌시 플레이어 가속도 기본 속도로 지정

                /// 충돌 발생 시 바운스
                if (EngineData::gravityVelocity > 3.5) 
                {
                    /// 탄성 계수는 현 중력에 비례한 속도 유지
                    EngineData::gravityVelocity = -EngineData::gravityVelocity / 1.75;    
                } 
                else {      /// 중력이 일정값 이하일 시 기본 중력값 설정
                 
                    EngineData::gravityVelocity = 2;
                }
            }  
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }

    case WM_GETMINMAXINFO:      /// 화면 최대 크기 지정
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

        // 더블 버퍼링 최적화
        static HDC hMemDC = NULL;
        static HBITMAP hBitmap = NULL;
        static int oldWidth = 0, oldHeight = 0;

        // 윈도우 크기 가져오기
        RECT clientRect;
        GetClientRect(hWnd, &clientRect);
        int width = clientRect.right - clientRect.left;
        int height = clientRect.bottom - clientRect.top;

        // 윈도우 크기가 변경되었거나 초기 실행인 경우에만 새로운 비트맵 생성
        if (hMemDC == NULL || width != oldWidth || height != oldHeight)
        {
            if (hMemDC != NULL)
            {
                DeleteObject(hBitmap);
                DeleteDC(hMemDC);
            }

            hMemDC = CreateCompatibleDC(hdc);
            hBitmap = CreateCompatibleBitmap(hdc, width, height);
            SelectObject(hMemDC, hBitmap);

            oldWidth = width;
            oldHeight = height;
        }

        // 메모리 DC 초기화
        FillRect(hMemDC, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));

        /// 메인 화면 버튼 그리기
        playGameButton.drawRectButton(hMemDC, IDI_PLAYBUTTON);
        guideButton.drawRectButton(hMemDC, IDI_GUIDEBUTTON);
        mainExitButton.drawRectButton(hMemDC, IDI_MAINEXITBUTTON);

        /// 맵 출력
        if (playMap1)
        {
            /// 배경 이미지 출력
            if (EngineData::hBackground)
            {
                HDC hBackgroundDC = CreateCompatibleDC(hdc);
                SelectObject(hBackgroundDC, EngineData::hBackground);
                // 원본 비트맵 크기
                BITMAP bmp;
                GetObject(EngineData::hBackground, sizeof(BITMAP), &bmp);

                StretchBlt(
                    hMemDC,                         // 출력할 DC
                    imageMove - 730, 50,            // 출력 시작 위치
                    1400, 650,                      // 출력할 너비와 높이
                    hBackgroundDC,                  // 원본 비트맵 DC
                    0, 0,                           // 원본 비트맵의 시작 위치
                    bmp.bmWidth, bmp.bmHeight,      // 원본 비트맵의 너비와 높이
                    SRCCOPY                         // 복사 방식
                );
                DeleteDC(hBackgroundDC);
            }
                /// 맵 그리기
                Engine_DrawMap::drawMap(hMemDC);

                // 플레이어 그리기
                Ellipse(hMemDC, EngineData::userBox.left, EngineData::userBox.top, EngineData::userBox.right, EngineData::userBox.bottom);

                // 중력 속도 표시
                Engine_DrawMap::drawInfo(hMemDC);

                /// 플레이 화면 내 버튼
                exitButton.drawRectButton(hMemDC, IDI_EXITBUTTON);
                developButtton.drawRectButton(hMemDC, IDI_DEVELOPBUTTON);
        }

        /// 더블 버퍼링된 내용을 화면에 출력
        BitBlt(hdc, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);

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
