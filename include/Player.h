#ifndef PLAYER_H
#define PLAYER_H

#include "Constants.h"
#include "Object.h"
#include <tchar.h>
#include <windows.h>

class Player
{
    public:
        Player();

        virtual void LoadResources() = 0;
        virtual void freeResources() = 0;
        virtual void Display(HDC&, HDC&) = 0;

        virtual void setState(const int&) = 0;
        int getState() const { return state; }
        virtual void setPunch(bool, int, int, int) = 0;

        void updateX(const int&);
        int getX() const { return warrior.x; }

        int hp = 100;
        int state = 0;
        int punchCounter = 0;
        int type = 0;
        bool isPunched = false;
        bool inProgress = false;
        bool disabled = false;

        HBRUSH hpBar = CreateSolidBrush(RGB(219,255,118));

        Object warrior, armKick, comboKick, flyKick, kickedKick, knockedKick, kneeKick, legKick;
        Object punch;
        Object blockStance;

        int cx = 0, cy = 0, pcx = 0, pcy = 0;

    protected:

    private:
};

#endif // PLAYER_H
