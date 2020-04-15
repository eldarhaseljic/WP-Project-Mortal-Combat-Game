#include "WarriorPlayerTwo.h"

WarriorPlayerTwo::WarriorPlayerTwo()
{
    //ctor
}

void WarriorPlayerTwo::LoadResources()
{
    BITMAP bitmap;
    hbmWarrior = (HBITMAP) LoadImage(NULL, "warrior_p2/stance_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hbmWarriorMask = (HBITMAP) LoadImage(NULL, "warrior_p2/stance_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hbmArmKick = (HBITMAP) LoadImage(NULL, "warrior_p2/arm_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hbmArmKickMask = (HBITMAP) LoadImage(NULL, "warrior_p2/arm_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    combo = (HBITMAP) LoadImage(NULL, "warrior_p2/combo_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    comboMask = (HBITMAP) LoadImage(NULL, "warrior_p2/combo_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    fly = (HBITMAP) LoadImage(NULL, "warrior_p2/fly_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    flyMask = (HBITMAP) LoadImage(NULL, "warrior_p2/fly_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    kicked = (HBITMAP) LoadImage(NULL, "warrior_p2/kicked_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    kickedMask = (HBITMAP) LoadImage(NULL, "warrior_p2/kicked_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    knee = (HBITMAP) LoadImage(NULL, "warrior_p2/knee_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    kneeMask = (HBITMAP) LoadImage(NULL, "warrior_p2/knee_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    knocked = (HBITMAP) LoadImage(NULL, "warrior_p2/knocked_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    knockedMask = (HBITMAP) LoadImage(NULL, "warrior_p2/knocked_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    leg = (HBITMAP) LoadImage(NULL, "warrior_p2/leg_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    legMask = (HBITMAP) LoadImage(NULL, "warrior_p2/leg_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    block = (HBITMAP) LoadImage(NULL, "warrior_p2/block_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    blockMask = (HBITMAP) LoadImage(NULL, "warrior_p2/block_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


    GetObject(hbmWarrior, sizeof(BITMAP), &bitmap);
    warrior.width = bitmap.bmWidth/6;
    warrior.height = bitmap.bmHeight/4;
    warrior.x = X_POSITION_P2;
    warrior.y = Y_POSITION_P2;

    GetObject(hbmArmKick, sizeof(BITMAP), &bitmap);
    armKick.width = bitmap.bmWidth/6;
    armKick.height = bitmap.bmHeight/4;
    armKick.x = warrior.x-ARM_KICK_DELTA_X;
    armKick.y = warrior.y-ARM_KICK_DELTA_Y;

    GetObject(combo, sizeof(BITMAP), &bitmap);
    comboKick.width = bitmap.bmWidth/6;
    comboKick.height = bitmap.bmHeight/9;
    comboKick.x = warrior.x-COMBO_KICK_DELTA_X;
    comboKick.y = warrior.y-COMBO_KICK_DELTA_Y;

    GetObject(fly, sizeof(BITMAP), &bitmap);
    flyKick.width = bitmap.bmWidth/5;
    flyKick.height = bitmap.bmHeight/5;
    flyKick.x = warrior.x-FLY_KICK_DELTA_X;
    flyKick.y = warrior.y-FLY_KICK_DELTA_Y;

    GetObject(kicked, sizeof(BITMAP), &bitmap);
    kickedKick.width = bitmap.bmWidth/6;
    kickedKick.height = bitmap.bmHeight/6;
    kickedKick.x = warrior.x-KICKED_DELTA_X;
    kickedKick.y = warrior.y-KICKED_DELTA_Y;

    GetObject(knee, sizeof(BITMAP), &bitmap);
    kneeKick.width = bitmap.bmWidth/7;
    kneeKick.height = bitmap.bmHeight/3;
    kneeKick.x = warrior.x-KNEE_KICK_DELTA_X;
    kneeKick.y = warrior.y;

    GetObject(knocked, sizeof(BITMAP), &bitmap);
    knockedKick.width = bitmap.bmWidth/7;
    knockedKick.height = bitmap.bmHeight/4;
    knockedKick.x = warrior.x;
    knockedKick.y = warrior.y;

    GetObject(leg, sizeof(BITMAP), &bitmap);
    legKick.width = bitmap.bmWidth/6;
    legKick.height = bitmap.bmHeight/3;
    legKick.x = warrior.x-LEG_KICK_DELTA_X;
    legKick.y = warrior.y-LEG_KICK_DELTA_Y;

    GetObject(block, sizeof(BITMAP), &bitmap);
    blockStance.width = bitmap.bmWidth/5;
    blockStance.height = bitmap.bmHeight/4;
    blockStance.x = warrior.x;
    blockStance.y = warrior.y+25;
}


void WarriorPlayerTwo::Display(HDC& hdcMem, HDC& hdcBuffer)
{
    SelectObject(hdcBuffer, (HBRUSH) this->hpBar);
    if (this->hp > 0)
        Rectangle(hdcBuffer, 592-this->hp*2, 10, 592, 25);
    if (state == STANCE_STATE)
    {
        SelectObject(hdcMem, hbmWarrior);
        BitBlt(hdcBuffer, warrior.x, warrior.y, warrior.width, warrior.height, hdcMem, cx * warrior.width, cy * warrior.height, SRCPAINT);
        SelectObject(hdcMem, hbmWarriorMask);
        BitBlt(hdcBuffer, warrior.x, warrior.y, warrior.width, warrior.height, hdcMem, cx * warrior.width, cy * warrior.height, SRCAND);
        cx++;
        if (cx > 5)
        {
            cy++;
            if (cy > 3)
                cy = 0;
            cx = 0;
        }
    }
    else if (state == ARM_KICK_STATE)
    {
        static bool first_time = true;
        if (first_time)
        {
            cx = 0; cy = 0;
            first_time = false;
        }
        SelectObject(hdcMem, hbmArmKick);
        BitBlt(hdcBuffer, armKick.x, armKick.y, armKick.width, armKick.height, hdcMem, cx * armKick.width, cy * armKick.height, SRCPAINT);
        SelectObject(hdcMem, hbmArmKickMask);
        BitBlt(hdcBuffer, armKick.x, armKick.y, armKick.width, armKick.height, hdcMem, cx * armKick.width, cy * armKick.height, SRCAND);
        cx++;
        if (cx > 5)
        {
            cy++;
            if (cy > 3)
            {
                state = 0;
                cy = 0;
                inProgress = false;
                first_time = true;
            }
            cx = 0;
        }
    }
    else if (state == LEG_KICK_STATE)
    {
        static bool first_time = true;
        if (first_time)
        {
            cx = 0; cy = 0;
            first_time = false;
        }
        SelectObject(hdcMem, leg);
        BitBlt(hdcBuffer, legKick.x, legKick.y, legKick.width, legKick.height, hdcMem, cx * legKick.width, cy * legKick.height, SRCPAINT);
        SelectObject(hdcMem, legMask);
        BitBlt(hdcBuffer, legKick.x, legKick.y, legKick.width, legKick.height, hdcMem, cx * legKick.width, cy * legKick.height, SRCAND);
        cx++;
        if (cx > 5)
        {
            cy++;
            if (cy > 2)
            {
                state = 0;
                cy = 0;
                inProgress = false;
                first_time = true;
            }
            cx = 0;
        }
    }
    else if (state == KNEE_KICK_STATE)
    {
        static bool first_time = true;
        if (first_time)
        {
            cx = 0; cy = 0;
            first_time = false;
        }
        SelectObject(hdcMem, knee);
        BitBlt(hdcBuffer, kneeKick.x, kneeKick.y, kneeKick.width, kneeKick.height, hdcMem, cx * kneeKick.width, cy * kneeKick.height, SRCPAINT);
        SelectObject(hdcMem, kneeMask);
        BitBlt(hdcBuffer, kneeKick.x, kneeKick.y, kneeKick.width, kneeKick.height, hdcMem, cx * kneeKick.width, cy * kneeKick.height, SRCAND);
        cx++;
        if (cx > 6)
        {
            cy++;
            if (cy > 2)
            {
                state = 0;
                cy = 0;
                inProgress = false;
                first_time = true;
            }
            cx = 0;
        }
    }
    else if (state == COMBO_KICK_STATE)
    {
        static bool first_time = true;
        if (first_time)
        {
            cx = 0; cy = 0;
            first_time = false;
        }
        SelectObject(hdcMem, combo);
        BitBlt(hdcBuffer, comboKick.x, comboKick.y, comboKick.width, comboKick.height, hdcMem, cx * comboKick.width, cy * comboKick.height, SRCPAINT);
        SelectObject(hdcMem, comboMask);
        BitBlt(hdcBuffer, comboKick.x, comboKick.y, comboKick.width, comboKick.height, hdcMem, cx * comboKick.width, cy * comboKick.height, SRCAND);
        cx++;
        if (cx > 5)
        {
            cy++;
            if (cy > 8)
            {
                state = 0;
                cy = 0;
                inProgress = false;
                first_time = true;
            }
            cx = 0;
        }
    }
    else if (state == FLY_KICK_STATE)
    {
        static bool first_time = true;
        if (first_time)
        {
            cx = 0; cy = 0;
            first_time = false;
        }
        SelectObject(hdcMem, fly);
        BitBlt(hdcBuffer, flyKick.x, flyKick.y, flyKick.width, flyKick.height, hdcMem, cx * flyKick.width, cy * flyKick.height, SRCPAINT);
        SelectObject(hdcMem, flyMask);
        BitBlt(hdcBuffer, flyKick.x, flyKick.y, flyKick.width, flyKick.height, hdcMem, cx * flyKick.width, cy * flyKick.height, SRCAND);
        cx++;
        if (cx > 4)
        {
            cy++;
            if (cy > 4)
            {
                state = 0;
                cy = 0;
                inProgress = false;
                first_time = true;
            }
            cx = 0;
        }
    }
    else if (state == KNOCKED_STATE)
    {
        static bool first_time = true;
        if (first_time)
        {
            cx = 0; cy = 0;
            first_time = false;
        }
        SelectObject(hdcMem, knocked);
        BitBlt(hdcBuffer, knockedKick.x, knockedKick.y, knockedKick.width, knockedKick.height, hdcMem, cx * knockedKick.width, cy * knockedKick.height, SRCPAINT);
        SelectObject(hdcMem, knockedMask);
        BitBlt(hdcBuffer, knockedKick.x, knockedKick.y, knockedKick.width, knockedKick.height, hdcMem, cx * knockedKick.width, cy * knockedKick.height, SRCAND);
        cx++;
        if (cx > 6)
        {
            cy++;
            if (cy > 3)
            {
                state = 0;
                cy = 0;
                inProgress = false;
                first_time = true;
                disabled = false;
            }
            cx = 0;
        }
    }
    else if (state == KICKED_STATE)
    {
        static bool first_time = true;
        if (first_time)
        {
            cx = 0; cy = 0;
            first_time = false;
        }
        SelectObject(hdcMem, kicked);
        BitBlt(hdcBuffer, kickedKick.x, kickedKick.y, kickedKick.width, kickedKick.height, hdcMem, cx * kickedKick.width, cy * kickedKick.height, SRCPAINT);
        SelectObject(hdcMem, kickedMask);
        BitBlt(hdcBuffer, kickedKick.x, kickedKick.y, kickedKick.width, kickedKick.height, hdcMem, cx * kickedKick.width, cy * kickedKick.height, SRCAND);
        cx++;
        if (cx == 3 && cy == 5)
        {
            cx = 0; cy = 0;
            state = 0;
            inProgress = false;
            first_time = true;
            disabled = false;
        }
        if (cx > 5)
        {
            cy++;
            if (cy > 5)
            {
                state = 0;
                cy = 0;
                inProgress = false;
                first_time = true;
                disabled = false;
            }
            cx = 0;
        }
    }
    else if (state == BLOCK_STATE)
    {
        static bool first_time = true;
        if (first_time)
        {
            cx = 0; cy = 0;
            first_time = false;
        }
        SelectObject(hdcMem, block);
        BitBlt(hdcBuffer, blockStance.x, blockStance.y, blockStance.width, blockStance.height, hdcMem, cx * blockStance.width, cy * blockStance.height, SRCPAINT);
        SelectObject(hdcMem, blockMask);
        BitBlt(hdcBuffer, blockStance.x, blockStance.y, blockStance.width, blockStance.height, hdcMem, cx * blockStance.width, cy * blockStance.height, SRCAND);
        cx++;
        if (cx > 4)
        {
            cy++;
            if (cy > 3)
            {
                state = 0;
                cy = 0;
                inProgress = false;
                first_time = true;
                disabled = false;
            }
            cx = 0;
        }
    }
    if (isPunched)
    {
        SelectObject(hdcMem, hbmPunch);
        BitBlt(hdcBuffer, punch.x, punch.y, punch.width, punch.height, hdcMem, pcx * punch.width, pcy * punch.height, SRCPAINT);
        SelectObject(hdcMem, hbmPunchMask);
        BitBlt(hdcBuffer, punch.x, punch.y, punch.width, punch.height, hdcMem, pcx * punch.width, pcy * punch.height, SRCAND);
        pcx++;
        if (pcx > 4)
        {
            if (!punchCounter)
            {
                isPunched = false;
            }
            punchCounter--;
            pcx = 0;
        }
    }
}

void WarriorPlayerTwo::setPunch(bool punched, int punch_state, int x, int y)
{
    punch.x = x;
    punch.y = y;
    isPunched = punched;
    punchCounter = punch_state;
}

void WarriorPlayerTwo::freeResources()
{
    DeleteObject(hbmPunch);
    DeleteObject(hbmPunchMask);
    DeleteObject(hbmWarrior);
    DeleteObject(hbmWarriorMask);
    DeleteObject(hbmArmKick);
    DeleteObject(hbmArmKickMask);
    DeleteObject(combo);
    DeleteObject(comboMask);
    DeleteObject(fly);
    DeleteObject(flyMask);
    DeleteObject(kicked);
    DeleteObject(kickedMask);
    DeleteObject(knee);
    DeleteObject(kneeMask);
    DeleteObject(knocked);
    DeleteObject(knockedMask);
    DeleteObject(leg);
    DeleteObject(legMask);
    DeleteObject(block);
    DeleteObject(blockMask);
}