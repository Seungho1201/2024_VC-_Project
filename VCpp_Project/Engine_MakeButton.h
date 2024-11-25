#pragma once

#include "Resource.h"
#include "framework.h"
#include "Engine_Data.h"

class MakeButton
{
private:
    int icon;             /// 아이콘 지정 멤버 변수
    int width;            /// 버튼의 폭
    int height;           /// 버튼의 높이
    int func;             /// 버튼의 ID


public:
    RECT rectButton;

    /**
   * @brief MakeButton 클래스의 생성자 위치 좌표 초기화
   * @param int left RECT 자료형의 left
   * @param int top RECT 자료형의 top
   * @param int right RECT 자료형의 right
   * @param int bottom RECT 자료형의 bottom
   */
    MakeButton(int left, int top, int right, int bottom);

    /**
    * @brief 일반 이미지 버튼 그리기 WM_PAINT에서 사용
    * @param HDC tHdc WM_PAINT의 hdc
    * @param int icon 버튼에 삽입할 이미지 (.rc, Resource에 정의)
    */
    void drawRectButton(HDC tHdc, int icon);

    /**
    * @brief RECT 자료형 버튼들의 좌표 지정 메서드
    * @param int left RECT 자료형의 left
    * @param int top RECT 자료형의 top
    * @param int right RECT 자료형의 right
    * @param int bottom RECT 자료형의 bottom
    */
    void setCoordinate(int left, int top, int right, int bottom);


protected:
    void buttonLoadImage(int icon, HDC tHdc);
};