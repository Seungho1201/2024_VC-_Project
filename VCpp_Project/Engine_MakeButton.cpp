#include "Engine_MakeButton.h"

MakeButton::MakeButton(int left, int top, int right, int bottom)
{
    /// 생성자 초기화
    this->rectButton.left = left;
    this->rectButton.top = top;
    this->rectButton.right = right;
    this->rectButton.bottom = bottom;
    this->icon = 0;
}

void MakeButton::drawRectButton(HDC tHdc, int icon)
{
    this->icon = icon;  /// 멤버 변수에 icon 값 저장

    
    /// 사각형 그릴 때 외곽선 없게 처리 (NULL_BRUSH)
    /// 만약 버튼 추가 후 클릭 영역 확인 필요시 이부분 주석 처리
    HBRUSH hOldBrush = (HBRUSH)SelectObject(tHdc, GetStockObject(NULL_BRUSH));
    HPEN hOldPen = (HPEN)SelectObject(tHdc, GetStockObject(NULL_PEN));
    
    /// Rectangle 그리기 
    Rectangle(tHdc,
        this->rectButton.left,
        this->rectButton.top,
        this->rectButton.right,
        this->rectButton.bottom
    );

    /// 아이콘 그리기
    buttonLoadImage(this->icon, tHdc);

    
    /// 이전 브러시와 펜 복원
    SelectObject(tHdc, hOldBrush);
    SelectObject(tHdc, hOldPen);

    /// 리소스 해제
    DeleteObject(hOldBrush);
    DeleteObject(hOldPen);
    
}

void MakeButton::buttonLoadImage(int icon, HDC tHdc)
{
    /// 아이콘 로드
    HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL),
        MAKEINTRESOURCE(icon),
        IMAGE_ICON,
        100,
        100,
        0
    );

    /// 아이콘 그리기
    DrawIconEx(tHdc,
        this->rectButton.left,
        this->rectButton.top,
        hIcon, 100, 100, 0, NULL, DI_NORMAL);

    /// 아이콘 자원 해제
    DestroyIcon(hIcon);
}

void MakeButton::setCoordinate(int left, int top, int right, int bottom)
{
    this->rectButton.left = left;           /// RECT 자료형 left
    this->rectButton.top = top;             /// RECT 자료형 top
    this->rectButton.right = right;         /// RECT 자료형 right
    this->rectButton.bottom = bottom;       /// RECT 자료형 bottom
    this->icon = 0;                         /// icon 0으로 초기화
}