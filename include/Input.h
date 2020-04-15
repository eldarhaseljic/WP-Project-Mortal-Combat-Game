#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include "Constants.h"
#include "Player.h"


#define PRESSED(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

class Input
{
    public:
        void CheckInput(Player*, Player*, HWND&);
        Input();
        virtual ~Input();

    protected:

    private:
};

#endif // INPUT_H
