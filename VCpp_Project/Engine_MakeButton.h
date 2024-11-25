#pragma once

#include "Resource.h"
#include "framework.h"
#include "Engine_Data.h"

class MakeButton
{
private:
    int icon;             /// ������ ���� ��� ����
    int width;            /// ��ư�� ��
    int height;           /// ��ư�� ����
    int func;             /// ��ư�� ID


public:
    RECT rectButton;

    /**
   * @brief MakeButton Ŭ������ ������ ��ġ ��ǥ �ʱ�ȭ
   * @param int left RECT �ڷ����� left
   * @param int top RECT �ڷ����� top
   * @param int right RECT �ڷ����� right
   * @param int bottom RECT �ڷ����� bottom
   */
    MakeButton(int left, int top, int right, int bottom);

    /**
    * @brief �Ϲ� �̹��� ��ư �׸��� WM_PAINT���� ���
    * @param HDC tHdc WM_PAINT�� hdc
    * @param int icon ��ư�� ������ �̹��� (.rc, Resource�� ����)
    */
    void drawRectButton(HDC tHdc, int icon);

    /**
    * @brief RECT �ڷ��� ��ư���� ��ǥ ���� �޼���
    * @param int left RECT �ڷ����� left
    * @param int top RECT �ڷ����� top
    * @param int right RECT �ڷ����� right
    * @param int bottom RECT �ڷ����� bottom
    */
    void setCoordinate(int left, int top, int right, int bottom);


protected:
    void buttonLoadImage(int icon, HDC tHdc);
};