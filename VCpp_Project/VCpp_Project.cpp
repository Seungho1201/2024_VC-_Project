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

// 전역 변수
int backgroundOffsetX = 0; // 배경 이미지의 X축 오프셋
const int BACKGROUND_SCROLL_SPEED = 5; // 배경 스크롤 속도

// 전역 변수
const float BOUNCE_DAMPING = 0.8f; // 바운스 감쇠 계수
const float GROUND_FRICTION = 0.98f; // 지면 마찰 계수
bool isJumping = false; // 점프 상태 변수
bool isInAir = true;     // 중력 적용 상태 변수
bool isBounce = false;

float imageMove = 0;
RECT clientRect;
RECT startPoint;

RECT mouseClick;
RECT a;

float bounceVelocity = 0.0f;  // 바운스 속도
/// 마우스 좌표 알려고 임시로 만듦
int mouse_X;
int mouse_Y;

HBITMAP hBackground; // 배경 이미지 핸들
RECT playButton = { 500, 500, 600, 600 };

#define PLAYSTART 800

bool playMap1 = false;
bool keyOn = false;

MakeButton playGameButton(500, 500, 600, 600);
MakeButton exitButton(1300, 700, 1400, 800);
MakeButton developButtton(1200, 700, 1300, 800);

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
        /// 중력 타이머 설정
       
        //startPoint = EngineData::userBox;
        break;
    }
    case WM_LBUTTONDOWN:
    {
        HDC hdc = GetDC(hWnd);

        int x = LOWORD(lParam);
        int y = HIWORD(lParam);

        mouseClick.left = x;
        mouseClick.top = y;
        mouseClick.right = mouseClick.left + 1;
        mouseClick.bottom = mouseClick.top + 1;

        if (IntersectRect(&a, &mouseClick, &playGameButton.rectButton))
        {
            /// 시작 좌표 저장
            startPoint = EngineData::userBox;

            /// Engine_DrawMap 파일에서 맵과 아이템 구성
            Engine_DrawMap::settingMap();

            SetTimer(hWnd, IDT_GRAVITY_TIMER, 2, NULL);

            /// 배경 이미지 로드
            hBackground = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCE(IDB_BACKGROUND2), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
           
            if (!hBackground)
            {
                MessageBox(hWnd, L"배경 이미지를 로드할 수 없습니다.", L"에러", MB_OK);
            }

            /// 현재 창의 크기를 받아 이미지 움직임
            GetClientRect(hWnd, &clientRect);
            imageMove = (clientRect.left + clientRect.right) / 2.0;

            playMap1 = true;
            EngineData::developMode = false;
            playGameButton.setCoordinate(-100, -100, -200, -200);
        }
        else if (IntersectRect(&a, &mouseClick, &exitButton.rectButton))
        {
            //EngineData::userBox = startPoint;
            EngineData::userBox = startPoint;
            playMap1 = false;
            playGameButton.setCoordinate(500, 500, 600, 600);

        }
        else if (IntersectRect(&a, &mouseClick, &developButtton.rectButton))
        {
            EngineData::developMode = !EngineData::developMode;
        }
        
    }
    break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
            case VK_RIGHT:
                isMovingRight = true;
                if (!keyOn)
                {
                    keyOn = true;
                    SetTimer(hWnd, IDT_TIMER1, 2, NULL);    /// 이동 타이머
                }
                break;

            case VK_LEFT:
                isMovingLeft = true;
                if (!keyOn)
                {
                    keyOn = true;
                    SetTimer(hWnd, IDT_TIMER1, 2, NULL);    /// 이동 타이머
                }
                break;

            case 'C': 
            {
                if (!isJumping)
                {
                    isJumping = true;        // 점프 중으로 설정

                    isInAir = true;          // C 키를 누르면 공중 상태로 설정
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
            RECT tempPlayerBox = EngineData::userBox;

            /// 방향키 이동
            if (isMovingRight) 
            { 
                tempPlayerBox.left += EngineData::playerSpeed; 
                tempPlayerBox.right += EngineData::playerSpeed; 
                
                if (!IsCollidingWithWall(tempPlayerBox, EngineData::mapGrid, 0, 0))
                {
                
                    if (!(tempPlayerBox.right > clientRect.right - 50))
                    {
                        imageMove += 0.2;
                        EngineData::userBox = tempPlayerBox; // 충돌이 없을 경우에만 이동
                    }
                    break;
                }            
            }
            
            if (isMovingLeft)   
            { 
                tempPlayerBox.left -= EngineData::playerSpeed; 
                tempPlayerBox.right -= EngineData::playerSpeed; 
                
                if (!IsCollidingWithWall(tempPlayerBox, EngineData::mapGrid, 0, 0))
                {
                    if (!(tempPlayerBox.left < clientRect.left + 50))
                    {
                        imageMove -= 0.2;
                        EngineData::userBox = tempPlayerBox; // 충돌이 없을 경우에만 이동;
                    }     
                    break;
                }
            }
            InvalidateRect(hWnd, NULL, TRUE);
        }

        /// 중력 타이머
        else if (wParam == IDT_GRAVITY_TIMER)
        {
            /// 중력값 증가
            EngineData::gravityVelocity += GRAVITY_ACCELERATION;
            EngineData::playerSpeed += 0.01f;
            // 최대 중력 속도 제한
            if (EngineData::gravityVelocity > MAX_GRAVITY_SPEED)
            {
                EngineData::gravityVelocity = MAX_GRAVITY_SPEED;
            }
            if (EngineData::playerSpeed > MAX_PLAYER_SPEED)
            {
                EngineData::playerSpeed = MAX_PLAYER_SPEED;
            }


            float newY = EngineData::userBox.top + EngineData::gravityVelocity;

            /// 중력 타이머에서의 충돌 감지시 바운스 효과 적용
            if (!IsCollidingWithWall(EngineData::userBox, EngineData::mapGrid, 0, EngineData::gravityVelocity))
            {
                
                /// 아이템 충돌 여부 확인
                if (IsCollidingWithItem(EngineData::userBox, EngineData::mapGrid, 0, 0))
                {
                    EngineData::gravityVelocity = -10; /// JUMP_HEIGHT는 위로 튀어오를 속도
                    isInAir = true;                    /// 공중 상태 설정
                    isJumping = false;                 /// 아이템 충돌시 점프 다시 가능
                }

                /// 장애물 충돌 여부 확인
                if (IsCollidingWithEnemy(EngineData::userBox, EngineData::mapGrid, 0, 0))
                {
                    EngineData::userBox.left = startPoint.left;
                    EngineData::userBox.right = startPoint.right;
                    EngineData::userBox.top = startPoint.top;
                    EngineData::userBox.bottom = startPoint.bottom;

                    imageMove = (clientRect.left + clientRect.right) / 2.0;

                    isJumping = false;                 /// 아이템 충돌시 점프 다시 가능
                }

                /// 중력에 따라 이동
                EngineData::userBox.top = newY;
                EngineData::userBox.bottom = EngineData::userBox.top + 30;
                

                isInAir = true;
            }
            else
            {
                /// 바닥에 한번 충돌해야 점프 재사용 가능
                isJumping = false;
                EngineData::playerSpeed = BASIC_PLAYER_SPEED;

                /// 충돌 발생 시 바운스
                if (EngineData::gravityVelocity >3.5) 
                {
                    /// 탄성 계수는 현 중력에 비례한 속도 유지
                    EngineData::gravityVelocity = -EngineData::gravityVelocity / 1.75;

                    /// 중력이 일정값 이하일 시 기본 중력값 설정
                } else {
                    // 매우 낮은 속도일 때 정지
                    EngineData::gravityVelocity = 2;
                    
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

        if (playMap1)
        {
            // 배경 이미지 출력
            if (hBackground)
            {
                HDC hBackgroundDC = CreateCompatibleDC(hdc);
                SelectObject(hBackgroundDC, hBackground);
                // 원본 비트맵 크기
                BITMAP bmp;
                GetObject(hBackground, sizeof(BITMAP), &bmp);

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

                /// 맵 그리기
                Engine_DrawMap::drawMap(hMemDC);

                // 플레이어 그리기
                Ellipse(hMemDC, EngineData::userBox.left, EngineData::userBox.top, EngineData::userBox.right, EngineData::userBox.bottom);

                // 중력 속도 표시
                Engine_DrawMap::drawInfo(hMemDC, mouse_X, mouse_Y);

                /// 나가기 버튼
                exitButton.drawRectButton(hMemDC, IDI_EXITBUTTON);
                developButtton.drawRectButton(hMemDC, IDI_DEVELOPBUTTON);
            }
        }

        playGameButton.drawRectButton(hMemDC, IDI_PLAYBUTTON);

        // 더블 버퍼링된 내용을 화면에 출력
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
