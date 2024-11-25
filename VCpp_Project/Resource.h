//{{NO_DEPENDENCIES}}
// Microsoft Visual C++에서 생성한 포함 파일입니다.
// 다음에서 사용 VCpp_Project.rc

#define IDS_APP_TITLE			103

#define IDR_MAINFRAME			128
#define IDD_VCPPPROJECT_DIALOG	102
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105
#define IDI_VCPPPROJECT			107
#define IDI_SMALL				108
#define IDC_VCPPPROJECT			109
#define IDC_MYICON				2
#ifndef IDC_STATIC
#define IDC_STATIC				-1

/// 맵 구성
#define GRID_ROWS 13 // 격자 행 수
#define GRID_COLS 27 // 격자 열 수
#define CELL_WIDTH 50 // 격자 셀 너비
#define CELL_HEIGHT 50 // 격자 셀 높이

/// 좌우 이동 타이머
#define IDT_TIMER1 100

/// 중력 및 가속도 계산 타이머
#define IDT_GRAVITY_TIMER 200
#define IDT_BOUNCE_TIMER 300

#define JUMP_HEIGHT 8
#define GRAVITY_SPEED 5

/// 가속도 관련
#define MOVE_ACCELERATION       0.05f    /// 중력 가속도
#define GRAVITY_ACCELERATION    0.25f    /// 중력 가속도
#define MAX_GRAVITY_SPEED       17.00f   /// 최대 중력 속도
#define MAX_PLAYER_SPEED        7.5f
#define BASIC_PLAYER_SPEED      5.0f

#define IDB_BACKGROUND 101

#define IDB_BACKGROUND2  102

#define IDI_PLAYBUTTON      201
#define IDI_EXITBUTTON      202
#define IDI_DEVELOPBUTTON   203
#define IDI_GUIDEBUTTON     204
#define IDI_MAINEXITBUTTON  205
#define IDI_WALLBRICK       206
#define IDI_TRAPBRICK       207
#define IDI_JUMPBRICK       208
#define IDI_EXITBRICK       209
#define IDI_EMPTYHEARTICON  210
#define IDI_HEARTICON       211

#endif
// 다음은 새 개체에 사용할 기본값입니다.
//
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

#define _APS_NO_MFC					130
#define _APS_NEXT_RESOURCE_VALUE	129
#define _APS_NEXT_COMMAND_VALUE		32771
#define _APS_NEXT_CONTROL_VALUE		1000
#define _APS_NEXT_SYMED_VALUE		110
#endif
#endif
