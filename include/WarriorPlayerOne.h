#ifndef WARRIORPLAYERONE_H
#define WARRIORPLAYERONE_H

#include "Object.h"
#include "Constants.h"
#include "Player.h"
#include <tchar.h>
#include <windows.h>


class WarriorPlayerOne : public Player
{
    public:
        WarriorPlayerOne();

        void LoadResources();
        void Display(HDC&, HDC&);

        void setState(const int& s) { state = s; }
        void setPunch(bool, int, int, int);

        void freeResources();

    protected:

    private:

        HBITMAP hbmPunch, hbmPunchMask;

        HBITMAP hbmWarrior, hbmWarriorMask;
        HBITMAP hbmArmKick, hbmArmKickMask;
        HBITMAP combo, comboMask;
        HBITMAP fly, flyMask;
        HBITMAP kicked, kickedMask;
        HBITMAP knee, kneeMask;
        HBITMAP knocked, knockedMask;
        HBITMAP leg, legMask;
        HBITMAP block, blockMask;

};

#endif // WARRIORPLAYERONE_H
