#include "Engine_MakeButton.h"

MakeButton::MakeButton(int left, int top, int right, int bottom)
{
    /// ������ �ʱ�ȭ
    this->rectButton.left = left;
    this->rectButton.top = top;
    this->rectButton.right = right;
    this->rectButton.bottom = bottom;
    this->icon = 0;
}

void MakeButton::drawRectButton(HDC tHdc, int icon)
{
    this->icon = icon;  /// ��� ������ icon �� ����

    
    /// �簢�� �׸� �� �ܰ��� ���� ó�� (NULL_BRUSH)
    /// ���� ��ư �߰� �� Ŭ�� ���� Ȯ�� �ʿ�� �̺κ� �ּ� ó��
    HBRUSH hOldBrush = (HBRUSH)SelectObject(tHdc, GetStockObject(NULL_BRUSH));
    HPEN hOldPen = (HPEN)SelectObject(tHdc, GetStockObject(NULL_PEN));
    
    /// Rectangle �׸��� 
    Rectangle(tHdc,
        this->rectButton.left,
        this->rectButton.top,
        this->rectButton.right,
        this->rectButton.bottom
    );

    /// ������ �׸���
    buttonLoadImage(this->icon, tHdc);

    
    /// ���� �귯�ÿ� �� ����
    SelectObject(tHdc, hOldBrush);
    SelectObject(tHdc, hOldPen);

    /// ���ҽ� ����
    DeleteObject(hOldBrush);
    DeleteObject(hOldPen);
    
}

void MakeButton::buttonLoadImage(int icon, HDC tHdc)
{
    /// ������ �ε�
    HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL),
        MAKEINTRESOURCE(icon),
        IMAGE_ICON,
        100,
        100,
        0
    );

    /// ������ �׸���
    DrawIconEx(tHdc,
        this->rectButton.left,
        this->rectButton.top,
        hIcon, 100, 100, 0, NULL, DI_NORMAL);

    /// ������ �ڿ� ����
    DestroyIcon(hIcon);
}

void MakeButton::setCoordinate(int left, int top, int right, int bottom)
{
    this->rectButton.left = left;           /// RECT �ڷ��� left
    this->rectButton.top = top;             /// RECT �ڷ��� top
    this->rectButton.right = right;         /// RECT �ڷ��� right
    this->rectButton.bottom = bottom;       /// RECT �ڷ��� bottom
    this->icon = 0;                         /// icon 0���� �ʱ�ȭ
}