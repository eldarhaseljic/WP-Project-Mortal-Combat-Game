#ifndef ARENA_H
#define ARENA_H

#include "Object.h"
#include "Constants.h"
#include <tchar.h>
#include <windows.h>

class Arena
{
    public:
        Arena();
        virtual ~Arena();
        HBITMAP GetArenaHbm() const;
        void setArena(const int& s) { state = s;}
        void selectArena(HWND&, HDC&, HDC&);
        void LoadResources();
        void Display(HDC&, HDC&);

        HBITMAP hbmSelect;

        HBITMAP counter_black, counter_white;
        int counter_height, counter_width;
        int counterx = 0, countery = 0;

    protected:

    private:
        int state = MOON_ARENA; // Current arena
        int cx = 0, cy = 0; // counters for animation

        Object moon, temple, volcano;
        HBITMAP hbmMoon;
        HBITMAP hbmVolcano;
        HBITMAP hbmTemple;
};

#endif // ARENA_H
