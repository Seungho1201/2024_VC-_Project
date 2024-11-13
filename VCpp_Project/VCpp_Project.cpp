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

// 전역 변수
RECT playerBox = { 0, 0, 100, 100 };

RECT t1 = { 10, 500, 600, 600 };

RECT t2 = { 800, 200, 1000, 700 };

RECT a;

#define IDT_TIMER1 1
#define IDT_GRAVITY_TIMER 3
#define JUMP_HEIGHT 50
#define GRAVITY_SPEED 7
#define GRAVITY_ACCELERATION 0.5f // 중력 가속도
#define MAX_GRAVITY_SPEED 10.0f   // 최대 중력 속도

bool isJumping = false; // 점프 상태 변수
bool isInAir = true;     // 중력 적용 상태 변수
float gravityVelocity = 0.0f;    // 중력 속도

// WndProc 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static bool isMovingRight = false;
    static bool isMovingLeft = false;
    static bool isMovingUp = false;

    switch (message)
    {
    case WM_CREATE:

        /// 중력 타이머 설정
        SetTimer(hWnd, IDT_GRAVITY_TIMER, 10, NULL); 
        break;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_RIGHT:
            isMovingRight = true;
            SetTimer(hWnd, IDT_TIMER1, 5, NULL); 
            break;

        case VK_LEFT:
            isMovingLeft = true;
            SetTimer(hWnd, IDT_TIMER1, 5, NULL);
            break;

        case VK_UP:
            isMovingUp = true;
            KillTimer(hWnd, IDT_GRAVITY_TIMER);
            SetTimer(hWnd, IDT_TIMER1, 5, NULL);
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

        case VK_UP:
            SetTimer(hWnd, IDT_GRAVITY_TIMER, 10, NULL);
            isInAir = true;
            isMovingUp = false;
            break;
        }

        if (!isMovingRight && !isMovingLeft && !isMovingUp)
        {
            KillTimer(hWnd, IDT_TIMER1); // 모든 이동 중지 시 타이머 해제
        }
        break;
    }
    case WM_TIMER:
    {
        if (wParam == IDT_TIMER1)
        {
            if (isMovingRight)  { playerBox.left += 4; playerBox.right += 4; }
            if (isMovingLeft)   { playerBox.left -= 4; playerBox.right -= 4; }
            if (isMovingUp)     { playerBox.top -= 4; playerBox.bottom -= 4; }

            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (wParam == IDT_GRAVITY_TIMER)
        {
            // 충돌 감지
            if (IntersectRect(&a, &t1, &playerBox) || IntersectRect(&a, &t2, &playerBox))
            {
                isInAir = false;
                gravityVelocity = 0.0f; // 바닥에 닿으면 중력 속도를 초기화
            }
            else
            {
                isInAir = true;
            }

            // 중력 가속도 적용
            if (isInAir)
            {
                gravityVelocity += GRAVITY_ACCELERATION; // 가속도 추가
                if (gravityVelocity > MAX_GRAVITY_SPEED)
                {
                    gravityVelocity = MAX_GRAVITY_SPEED; // 최대 속도 제한
                }

                playerBox.top += (int)gravityVelocity;
                playerBox.bottom += (int)gravityVelocity;

                
            }
        }
        InvalidateRect(hWnd, NULL, TRUE);
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

        Rectangle(hMemDC, playerBox.left, playerBox.top, playerBox.right, playerBox.bottom);
        Rectangle(hMemDC, t1.left, t1.top, t1.right, t1.bottom);
        Rectangle(hMemDC, t2.left, t2.top, t2.right, t2.bottom);




        BitBlt(hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top, hMemDC, 0, 0, SRCCOPY);

        SelectObject(hMemDC, hOldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(hMemDC);

        EndPaint(hWnd, &ps);
    }
    break;

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
