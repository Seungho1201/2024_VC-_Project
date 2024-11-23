#pragma once

#include "Resource.h"
#include "framework.h"
#include "Engine_Data.h"

class Engine_DrawMap {
public:



   static void settingMap();

   static void drawMap(HDC hMemDC);

   static void drawInfo(HDC hMemDC, int mouse_X, int mouse_Y);


};
