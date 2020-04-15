#include "Arena.h"
#include <stdio.h>

extern bool endGame;

Arena::Arena()
{
    //ctor
}

Arena::~Arena()
{
    //dtor
}

void Arena::LoadResources()
{
    BITMAP bitmap;
    hbmMoon = (HBITMAP) LoadImage(NULL, "arena/moon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hbmTemple = (HBITMAP) LoadImage(NULL, "arena/temple.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hbmVolcano = (HBITMAP) LoadImage(NULL, "arena/volcano.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    counter_black = (HBITMAP) LoadImage(NULL, "arena/counter_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    counter_white = (HBITMAP) LoadImage(NULL, "arena/counter_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    GetObject(counter_black, sizeof(BITMAP), &bitmap);
    counter_height = bitmap.bmHeight/31;
    counter_width = bitmap.bmWidth/6;

    GetObject(hbmMoon, sizeof(BITMAP), &bitmap);
    moon.width = bitmap.bmWidth/5;
    moon.height = bitmap.bmHeight/12;
    moon.x = 0;
    moon.y = 0;

    GetObject(hbmTemple, sizeof(BITMAP), &bitmap);
    temple.width = bitmap.bmWidth/5;
    temple.height = bitmap.bmHeight/12;
    temple.x = 0;
    temple.y = 0;

    GetObject(hbmVolcano, sizeof(BITMAP), &bitmap);
    volcano.width = bitmap.bmWidth/5;
    volcano.height = bitmap.bmHeight/12;
    volcano.x = 0;
    volcano.y = 0;

    hbmSelect = (HBITMAP) LoadImage(NULL, "arena/select.bmp", IMAGE_BITMAP, SELECT_X, SELECT_Y, LR_LOADFROMFILE);
}

void Arena::selectArena(HWND& hwnd, HDC& hdcMem, HDC& hdcBuffer)
{
    BitBlt(hdcBuffer, 0, 0, SELECT_X, SELECT_Y, hdcMem, 0, 0, SRCCOPY);
}

void Arena::Display(HDC& hdcMem, HDC& hdcBuffer)
{
    if (state == MOON_ARENA)
    {
        BitBlt(hdcBuffer, 0, 0, moon.width, moon.height, hdcMem, cx * moon.width, cy * moon.height, SRCCOPY);
        ++cx;
        if (cx > 4)
        {
            ++cy;
            if (cy > 11)
                cy = 0;
            cx = 0;
        }
    }
    else
    {
        BitBlt(hdcBuffer, 0, 0, volcano.width, volcano.height, hdcMem, cx * volcano.width, cy * volcano.height, SRCCOPY);
        ++cx;
        if (cx > 4)
        {
            ++cy;
            if (cy > 11)
                cy = 0;
            cx = 0;
        }
    }

    if (!endGame)
    {
        SelectObject(hdcMem, counter_black);
        BitBlt(hdcBuffer, (DEFAULT_WINDOW_X-counter_width)/2, 10, counter_width, counter_height, hdcMem, counter_width * counterx, counter_height * countery, SRCPAINT);
        SelectObject(hdcMem, counter_white);
        BitBlt(hdcBuffer, (DEFAULT_WINDOW_X-counter_width)/2, 10, counter_width, counter_height, hdcMem, counter_width * counterx, counter_height * countery, SRCAND);
    }
}

HBITMAP Arena::GetArenaHbm() const
{
    if (state == MOON_ARENA)
        return hbmMoon;
    else if (state == VOLCANO_ARENA)
        return hbmVolcano;
    else if (state == TEMPLE_ARENA)
        return hbmTemple;
}
