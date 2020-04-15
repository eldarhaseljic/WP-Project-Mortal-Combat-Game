#include "Input.h"

Input::Input()
{
    //ctor
}

Input::~Input()
{
    //dtor
}

extern Object hover1;
extern Object hover2;
extern bool p1Move;
extern bool p2Move;
extern bool PlayersInRange;

bool inRange(Player* p1, Player* p2)
{
    if (p2->getX() - p1->getX() <= 130)
        return true;

    return false;
}

void play_sound(char* filename, HWND& hwnd){
    static long id = 1;
    char cmd[300];
    char name[20];
    sprintf(name, "mydev%d", ++id);
    sprintf(cmd, "open %s type waveaudio alias %s", filename, name);
    mciSendString(cmd, NULL, NULL, NULL);
    sprintf(cmd, "play %s notify", name);
    mciSendString(cmd, NULL, NULL, hwnd);
}

void checkPlayer1Scorpion(HWND& hwnd, Player * Player1, Player * Player2)
{
    if (Player1->type == WARRIOR1 && Player1->getState() == COMBO_KICK_STATE)
    {
        if (inRange(Player1, Player2))
        {
            if ((Player1->cy == 1 && Player1->cx == 1)
            || (Player1->cy == 4 && Player1->cx == 1)
            || (Player1->cy == 6 && Player1->cx == 5))
            {
                play_sound("sounds/scorpion_kick.wav", hwnd);
                play_sound("sounds/scorpion_attack1.wav", hwnd);
                Player1->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P2);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KNOCKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 1 && Player1->cx == 1)
            || (Player1->cy == 4 && Player1->cx == 1)
            || (Player1->cy == 6 && Player1->cx == 5))
            {
                play_sound("sounds/scorpion_attack1.wav", hwnd);
            }
        }
    }

    if (Player1->type == WARRIOR1 && Player1->getState() == ARM_KICK_STATE)
    {
        if (inRange(Player1, Player2))
        {
            if ((Player1->cy == 0 && Player1->cx == 4)
            || (Player1->cy == 1 && Player1->cx == 4)
            || (Player1->cy == 2 && Player1->cx == 4))
            {
                play_sound("sounds/scorpion_kick.wav", hwnd);
                play_sound("sounds/scorpion_attack2.wav", hwnd);
                Player1->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P2+20);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KNOCKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 0 && Player1->cx == 4)
            || (Player1->cy == 1 && Player1->cx == 4)
            || (Player1->cy == 2 && Player1->cx == 4))
            {
                play_sound("sounds/scorpion_attack2.wav", hwnd);
            }
        }
    }

    if (Player1->type == WARRIOR1 && Player1->getState() == LEG_KICK_STATE)
    {
        if (inRange(Player1, Player2))
        {
            if ((Player1->cy == 1 && Player1->cx == 0))
            {
                play_sound("sounds/scorpion_kick.wav", hwnd);
                play_sound("sounds/scorpion_attack1.wav", hwnd);
                Player1->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P2+150);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KICKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 1 && Player1->cx == 0))
            {
                play_sound("sounds/scorpion_attack1.wav", hwnd);
            }
        }
    }

    if (Player1->type == WARRIOR1 && Player1->getState() == KNEE_KICK_STATE)
    {
        if (inRange(Player1, Player2))
        {
            if ((Player1->cy == 0 && Player1->cx == 4))
            {
                play_sound("sounds/scorpion_kick.wav", hwnd);
                play_sound("sounds/scorpion_attack3.wav", hwnd);
                Player1->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P2+50);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KNOCKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 0 && Player1->cx == 4))
            {
                play_sound("sounds/scorpion_attack3.wav", hwnd);
            }
        }
    }

    if (Player1->type == WARRIOR1 && Player1->getState() == FLY_KICK_STATE)
    {
        if (inRange(Player1, Player2))
        {
            if ((Player1->cy == 0 && Player1->cx == 4))
            {
                play_sound("sounds/scorpion_kick.wav", hwnd);
                play_sound("sounds/scorpion_attack1.wav", hwnd);
                Player1->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P2+30);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KICKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 0 && Player1->cx == 4))
            {
                play_sound("sounds/scorpion_attack1.wav", hwnd);
            }
        }
    }
}

void checkPlayer1Sonya(HWND& hwnd, Player * Player1, Player * Player2)
{
    if (Player1->type == SONYA1 && Player1->getState() == COMBO_KICK_STATE)
    {
        if (inRange(Player1, Player2))
        {
            if ((Player1->cy == 1 && Player1->cx == 4))
            {
                play_sound("sounds/sonya_kick.wav", hwnd);
                play_sound("sounds/sonya_attack1.wav", hwnd);
                Player1->setPunch(true, 0, Player2->getX(), Y_POSITION_P2);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KNOCKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 1 && Player1->cx == 4))
            {
                play_sound("sounds/sonya_attack1.wav", hwnd);
            }
        }
    }

    if (Player1->type == SONYA1 && Player1->getState() == ARM_KICK_STATE)
    {
        if (inRange(Player1, Player2))
        {
            if ((Player1->cy == 0 && Player1->cx == 0)
            || (Player1->cy == 1 && Player1->cx == 4)
            || (Player1->cy == 3 && Player1->cx == 4))
            {
                play_sound("sounds/sonya_kick.wav", hwnd);
                play_sound("sounds/sonya_attack2.wav", hwnd);
                Player1->setPunch(true, 0, Player2->getX()-10, Y_POSITION_P2+10);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KNOCKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 0 && Player1->cx == 0)
            || (Player1->cy == 1 && Player1->cx == 4)
            || (Player1->cy == 3 && Player1->cx == 4))
            {
                play_sound("sounds/sonya_attack2.wav", hwnd);
            }
        }
    }

    if (Player1->type == SONYA1 && Player1->getState() == LEG_KICK_STATE)
    {
        if (inRange(Player1, Player2))
        {
            if ((Player1->cy == 0 && Player1->cx == 8))
            {
                play_sound("sounds/sonya_kick.wav", hwnd);
                play_sound("sounds/sonya_attack3.wav", hwnd);
                Player1->setPunch(true, 0, Player2->getX()+10, Y_POSITION_P2+5);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KICKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 0 && Player1->cx == 8))
            {
                play_sound("sounds/sonya_attack3.wav", hwnd);
            }
        }
    }

    if (Player1->type == SONYA1 && Player1->getState() == KNEE_KICK_STATE)
    {
        if (inRange(Player1, Player2))
        {
            if ((Player1->cy == 1 && Player1->cx == 1))
            {
                play_sound("sounds/sonya_kick.wav", hwnd);
                play_sound("sounds/sonya_attack4.wav", hwnd);
                Player1->setPunch(true, 0, Player2->getX()-10, Y_POSITION_P2+50);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KNOCKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 1 && Player1->cx == 1))
            {
                play_sound("sounds/sonya_attack4.wav", hwnd);
            }
        }
    }

    if (Player1->type == SONYA1 && Player1->getState() == FLY_KICK_STATE)
    {
        if (inRange(Player1, Player2))
        {
            if ((Player1->cy == 1 && Player1->cx == 1))
            {
                play_sound("sounds/sonya_kick.wav", hwnd);
                play_sound("sounds/sonya_attack1.wav", hwnd);
                Player1->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P2+40);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KICKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 1 && Player1->cx == 1))
            {
                play_sound("sounds/sonya_attack1.wav", hwnd);
            }
        }
    }
}

void checkPlayer2Scorpion(HWND& hwnd, Player * Player1, Player * Player2)
{
    if (Player1->type == WARRIOR2 && Player1->getState() == COMBO_KICK_STATE)
    {
        if (inRange(Player2, Player1))
        {
            if ((Player1->cy == 1 && Player1->cx == 1)
            || (Player1->cy == 4 && Player1->cx == 1)
            || (Player1->cy == 6 && Player1->cx == 5))
            {
                play_sound("sounds/scorpion_kick.wav", hwnd);
                play_sound("sounds/scorpion_attack1.wav", hwnd);
                Player2->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P1);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KNOCKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 1 && Player1->cx == 1)
            || (Player1->cy == 4 && Player1->cx == 1)
            || (Player1->cy == 6 && Player1->cx == 5))
            {
                play_sound("sounds/scorpion_attack1.wav", hwnd);
            }
        }
    }

    if (Player1->type == WARRIOR2 && Player1->getState() == ARM_KICK_STATE)
    {
        if (inRange(Player2, Player1))
        {
            if ((Player1->cy == 0 && Player1->cx == 4)
            || (Player1->cy == 1 && Player1->cx == 4)
            || (Player1->cy == 2 && Player1->cx == 4))
            {
                play_sound("sounds/scorpion_kick.wav", hwnd);
                play_sound("sounds/scorpion_attack2.wav", hwnd);
                Player2->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P1+20);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KNOCKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 0 && Player1->cx == 4)
            || (Player1->cy == 1 && Player1->cx == 4)
            || (Player1->cy == 2 && Player1->cx == 4))
            {
                play_sound("sounds/scorpion_attack2.wav", hwnd);
            }
        }
    }

    if (Player1->type == WARRIOR2 && Player1->getState() == LEG_KICK_STATE)
    {
        if (inRange(Player2, Player1))
        {
            if ((Player1->cy == 1 && Player1->cx == 0))
            {
                play_sound("sounds/scorpion_kick.wav", hwnd);
                play_sound("sounds/scorpion_attack1.wav", hwnd);
                Player2->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P1+150);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KICKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 1 && Player1->cx == 0))
            {
                play_sound("sounds/scorpion_attack1.wav", hwnd);
            }
        }
    }

    if (Player1->type == WARRIOR2 && Player1->getState() == KNEE_KICK_STATE)
    {
        if (inRange(Player2, Player1))
        {
            if ((Player1->cy == 0 && Player1->cx == 4))
            {
                play_sound("sounds/scorpion_kick.wav", hwnd);
                play_sound("sounds/scorpion_attack3.wav", hwnd);
                Player2->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P1+50);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KNOCKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 0 && Player1->cx == 4))
            {
                play_sound("sounds/scorpion_attack3.wav", hwnd);
            }
        }
    }

    if (Player1->type == WARRIOR2 && Player1->getState() == FLY_KICK_STATE)
    {
        if (inRange(Player2, Player1))
        {
            if ((Player1->cy == 0 && Player1->cx == 4))
            {
                play_sound("sounds/scorpion_kick.wav", hwnd);
                play_sound("sounds/scorpion_attack1.wav", hwnd);
                Player2->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P1+30);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KICKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 0 && Player1->cx == 4))
            {
                play_sound("sounds/scorpion_attack1.wav", hwnd);
            }
        }
    }
}

void checkPlayer2Sonya(HWND& hwnd, Player * Player1, Player * Player2)
{
    if (Player1->type == SONYA2 && Player1->getState() == COMBO_KICK_STATE)
    {
        if (inRange(Player2, Player1))
        {
            if ((Player1->cy == 1 && Player1->cx == 4))
            {
                play_sound("sounds/sonya_kick.wav", hwnd);
                play_sound("sounds/sonya_attack1.wav", hwnd);
                Player2->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P1);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KNOCKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 1 && Player1->cx == 4))
            {
                play_sound("sounds/sonya_attack1.wav", hwnd);
            }
        }
    }

    if (Player1->type == SONYA2 && Player1->getState() == ARM_KICK_STATE)
    {
        if (inRange(Player2, Player1))
        {
            if ((Player1->cy == 0 && Player1->cx == 0)
            || (Player1->cy == 1 && Player1->cx == 4)
            || (Player1->cy == 3 && Player1->cx == 4))
            {
                play_sound("sounds/sonya_kick.wav", hwnd);
                play_sound("sounds/sonya_attack2.wav", hwnd);
                Player2->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P1);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KNOCKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 0 && Player1->cx == 0)
            || (Player1->cy == 1 && Player1->cx == 4)
            || (Player1->cy == 3 && Player1->cx == 4))
            {
                play_sound("sounds/sonya_attack2.wav", hwnd);
            }
        }
    }

    if (Player1->type == SONYA2 && Player1->getState() == LEG_KICK_STATE)
    {
        if (inRange(Player2, Player1))
        {
            if ((Player1->cy == 0 && Player1->cx == 8))
            {
                play_sound("sounds/sonya_kick.wav", hwnd);
                play_sound("sounds/sonya_attack3.wav", hwnd);
                Player2->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P1);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KICKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 0 && Player1->cx == 8))
            {
                play_sound("sounds/sonya_attack3.wav", hwnd);
            }
        }
    }

    if (Player1->type == SONYA2 && Player1->getState() == KNEE_KICK_STATE)
    {
        if (inRange(Player2, Player1))
        {
            if ((Player1->cy == 1 && Player1->cx == 1))
            {
                play_sound("sounds/sonya_kick.wav", hwnd);
                play_sound("sounds/sonya_attack4.wav", hwnd);
                Player2->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P1+30);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KNOCKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 1 && Player1->cx == 1))
            {
                play_sound("sounds/sonya_attack4.wav", hwnd);
            }
        }
    }

    if (Player1->type == SONYA2 && Player1->getState() == FLY_KICK_STATE)
    {
        if (inRange(Player2, Player1))
        {
            if ((Player1->cy == 1 && Player1->cx == 1))
            {
                play_sound("sounds/sonya_kick.wav", hwnd);
                play_sound("sounds/sonya_attack1.wav", hwnd);
                Player2->setPunch(true, 0, Player2->getX()+15, Y_POSITION_P1+50);
                if (Player2->getState() == BLOCK_STATE)
                    Player2->hp -= 1;
                else
                {
                    Player2->hp -= 3;
                    Player2->setState(KICKED_STATE);
                    Player2->disabled = true;
                }
            }
        }
        else
        {
            if ((Player1->cy == 1 && Player1->cx == 1))
            {
                play_sound("sounds/sonya_attack1.wav", hwnd);
            }
        }
    }
}

void Input::CheckInput(Player * Player1, Player * Player2, HWND& hwnd)
{
    checkPlayer1Scorpion(hwnd, Player1, Player2);
    checkPlayer2Scorpion(hwnd, Player2, Player1);
    checkPlayer1Sonya(hwnd, Player1, Player2);
    checkPlayer2Sonya(hwnd, Player2, Player1);

    if (!Player1->inProgress && !Player1->disabled)
    {
        if (PRESSED(KEY_Q))
        {
            Player1->inProgress = true;
            Player1->setState(COMBO_KICK_STATE);
        }
        if (PRESSED(KEY_W))
        {
            Player1->inProgress = true;
            Player1->setState(ARM_KICK_STATE);

        }
        if (PRESSED(KEY_E))
        {
            Player1->inProgress = true;
            Player1->setState(LEG_KICK_STATE);
        }
        if (PRESSED(KEY_R))
        {
            Player1->inProgress = true;
            Player1->setState(KNEE_KICK_STATE);
        }
        if (PRESSED(KEY_T))
        {
            Player1->inProgress = true;
            Player1->setState(FLY_KICK_STATE);
        }
        if (PRESSED(KEY_S))
        {
            Player1->inProgress = true;
            Player1->setState(BLOCK_STATE);
        }
    }

    // TWO

    if (!Player2->inProgress && !Player2->disabled)
    {
        if (PRESSED(KEY_G))
        {
            Player2->inProgress = true;
            Player2->setState(COMBO_KICK_STATE);
        }
        if (PRESSED(KEY_H))
        {
            Player2->inProgress = true;
            Player2->setState(ARM_KICK_STATE);
        }
        if (PRESSED(KEY_J))
        {
            Player2->inProgress = true;
            Player2->setState(LEG_KICK_STATE);
        }
        if (PRESSED(KEY_K))
        {
            Player2->inProgress = true;
            Player2->setState(KNEE_KICK_STATE);
        }
        if (PRESSED(KEY_L))
        {
            Player2->inProgress = true;
            Player2->setState(FLY_KICK_STATE);
        }
        if (PRESSED(VK_DOWN))
        {
            Player2->inProgress = true;
            Player2->setState(BLOCK_STATE);
        }
    }

    // MOVE

    if (!inRange(Player1, Player2))
    {
            if (PRESSED(KEY_D) && !Player1->disabled)
            {
                Player1->updateX(5);
                hover1.x = Player1->getX()-25;
                p1Move = true;
            }
            if (PRESSED(VK_LEFT) && !Player2->disabled)
            {
                Player2->updateX(-5);
                hover2.x = Player2->getX()-25;
                p2Move = true;
            }
    }
    if (PRESSED(KEY_A) && !Player1->disabled)
    {
        Player1->updateX(-5);
        hover1.x = Player1->getX() - 25;
        p1Move = true;
    }
    if (PRESSED(VK_RIGHT) && !Player2->disabled)
    {
        Player2->updateX(5);
        hover2.x = Player2->getX() - 25;
        p2Move = true;
    }
}

