#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include "WarriorPlayerOne.h"
#include "WarriorPlayerTwo.h"
#include "SonyaPlayerOne.h"
#include "SonyaPlayerTwo.h"
#include "Constants.h"
#include "Arena.h"
#include "Input.h"
#include "Player.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

Player * Player1;
Player * Player2;

int Player1Select;
int Player2Select;

Arena arena;
Input input;
Object hover1, hover2;
HBITMAP hbmHover, hbmHoverMask;
HBITMAP hbmHover2, hbmHoverMask2;

HBITMAP hbmNewGame, hbmP1S, hbmP2S;

HBITMAP win1_black, win2_black, win1_white, win2_white, nowin_black, nowin_white, enter_white, enter_black;

bool p1Move = false, p2Move = false;

bool arenaSelected = false, player1Selected = false, player2Selected = false, newGame = false;

bool endGame = false;

int game_timer = 0;

void reset(HWND& hwnd)
{
    mciSendString("stop theme1 notify", NULL, 0, hwnd);
    mciSendString("stop theme2 notify", NULL, 0, hwnd);
    mciSendString("stop theme3 notify", NULL, 0, hwnd);
    mciSendString("open sounds/theme.wav type waveaudio alias mydev", NULL, 0, NULL);
    mciSendString("play mydev notify", NULL, 0, NULL);
    arenaSelected = false;
    player1Selected = false;
    player2Selected = false;
    newGame = false;
    endGame = false;
    game_timer = 0;
    Player1->freeResources();
    Player2->freeResources();
    delete Player1;
    delete Player2;
}

void play_sound_main(char* filename, HWND& hwnd){
    static long id_main = 1;
    char cmd[300];
    char name[20];
    sprintf(name, "mainsounds%d", ++id_main);
    sprintf(cmd, "open %s type waveaudio alias %s", filename, name);
    mciSendString(cmd, NULL, NULL, NULL);
    sprintf(cmd, "play %s notify", name);
    mciSendString(cmd, NULL, NULL, hwnd);
}

int hcx, hcy, hcx2, hcy2;
void displayHoverP1(HDC& hdcMem, HDC& hdcBuffer)
{
    SelectObject(hdcMem, hbmHover);
    BitBlt(hdcBuffer, hover1.x, hover1.y, hover1.width, hover1.height, hdcMem, hcx * hover1.width, hcy * hover1.height, SRCPAINT);
    SelectObject(hdcMem, hbmHoverMask);
    BitBlt(hdcBuffer, hover1.x, hover1.y, hover1.width, hover1.height, hdcMem, hcx * hover1.width, hcy * hover1.height, SRCAND);
    hcx++;
    if (hcx > 3)
    {
        hcy++;
        if (hcy > 2)
            hcy = 0;
        hcx = 0;
    }
}

void displayHoverP2(HDC& hdcMem, HDC& hdcBuffer)
{
    SelectObject(hdcMem, hbmHover2);
    BitBlt(hdcBuffer, hover2.x, hover2.y, hover2.width, hover2.height, hdcMem, hcx2 * hover2.width, hcy2 * hover2.height, SRCPAINT);
    SelectObject(hdcMem, hbmHoverMask2);
    BitBlt(hdcBuffer, hover2.x, hover2.y, hover2.width, hover2.height, hdcMem, hcx2 * hover2.width, hcy2 * hover2.height, SRCAND);
    hcx2++;
    if (hcx2 > 3)
    {
        hcy2++;
        if (hcy2 > 2)
        {
            hcy2 = 0;
        }
        hcx2 = 0;
    }
}

void loadFighters()
{
    if (Player1Select == PLAYER1WARRIOR)
    {
        Player1 = new WarriorPlayerOne();
        Player1->LoadResources();
        Player1->type = WARRIOR1;
    }
    if (Player2Select == PLAYER2WARRIOR)
    {
        Player2 = new WarriorPlayerTwo();
        Player2->LoadResources();
        Player2->type = WARRIOR2;
    }
    if (Player1Select == PLAYER1SONYA)
    {
        Player1 = new SonyaPlayerOne();
        Player1->LoadResources();
        Player1->type = SONYA1;
    }
    if (Player2Select == PLAYER2SONYA)
    {
        Player2 = new SonyaPlayerTwo();
        Player2->LoadResources();
        Player2->type = SONYA2;
    }

    BITMAP bitmap;
    GetObject(hbmHover, sizeof(BITMAP), &bitmap);
    hover1.width = bitmap.bmWidth/4;
    hover1.height = bitmap.bmHeight/3;
    hover1.x = Player1->getX()-20;
    hover1.y = 372 - hover1.height-25;

    hover2.width = bitmap.bmWidth/4;
    hover2.height = bitmap.bmHeight/3;
    hover2.x = Player2->getX()-20;
    hover2.y = hover1.y;
}

void load()
{
    arena.LoadResources();
    arena.setArena(MOON_ARENA);

    hbmHover = (HBITMAP) LoadImage(NULL, "effects/hover_left_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hbmHoverMask = (HBITMAP) LoadImage(NULL, "effects/hover_left_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    hbmHover2 = (HBITMAP) LoadImage(NULL, "effects/hover_right_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hbmHoverMask2 = (HBITMAP) LoadImage(NULL, "effects/hover_right_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    hbmNewGame = (HBITMAP) LoadImage(NULL, "select/title.bmp", IMAGE_BITMAP, SELECT_X, SELECT_Y, LR_LOADFROMFILE);
    hbmP1S = (HBITMAP) LoadImage(NULL, "select/player1.bmp", IMAGE_BITMAP, SELECT_X, SELECT_Y, LR_LOADFROMFILE);
    hbmP2S = (HBITMAP) LoadImage(NULL, "select/player2.bmp", IMAGE_BITMAP, SELECT_X, SELECT_Y, LR_LOADFROMFILE);

    win1_black = (HBITMAP) LoadImage(NULL, "effects/win1_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    win1_white = (HBITMAP) LoadImage(NULL, "effects/win1_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    win2_black = (HBITMAP) LoadImage(NULL, "effects/win2_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    win2_white = (HBITMAP) LoadImage(NULL, "effects/win2_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    nowin_black = (HBITMAP) LoadImage(NULL, "effects/nowin_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    nowin_white = (HBITMAP) LoadImage(NULL, "effects/nowin_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    enter_black = (HBITMAP) LoadImage(NULL, "effects/enter_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    enter_white = (HBITMAP) LoadImage(NULL, "effects/enter_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void display(HWND hwnd)
{
    HDC hdc = GetDC(hwnd);
    RECT rect;
    GetClientRect(hwnd, &rect);

    HDC hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
    HBITMAP hbmOldBuffer = (HBITMAP) SelectObject(hdcBuffer, hbmBuffer);
    HDC hdcMem = CreateCompatibleDC(hdc);

    HBITMAP hbmOld = (HBITMAP) SelectObject (hdcMem, arena.GetArenaHbm());

    arena.Display(hdcMem, hdcBuffer);
    Player2->Display(hdcMem, hdcBuffer);
    Player1->Display(hdcMem, hdcBuffer);

    if (p1Move)
    {
        displayHoverP1(hdcMem, hdcBuffer);
        p1Move = false;
    }
    if (p2Move)
    {
        displayHoverP2(hdcMem, hdcBuffer);
        p2Move = false;
    }

    if (Player1->hp <= 5 || ((Player1->hp < Player2->hp) && game_timer >= GAME_TIMER))
    {
        SelectObject(hdcMem, win2_black);
        BitBlt(hdcBuffer, (DEFAULT_WINDOW_X-293)/2, (DEFAULT_WINDOW_Y-35)/2, 293, 35, hdcMem, 0, 0, SRCPAINT);
        SelectObject(hdcMem, win2_white);
        BitBlt(hdcBuffer, (DEFAULT_WINDOW_X-293)/2, (DEFAULT_WINDOW_Y-35)/2, 293, 35, hdcMem, 0, 0, SRCAND);

        SelectObject(hdcMem, enter_black);
        BitBlt(hdcBuffer, (DEFAULT_WINDOW_X-245)/2, (DEFAULT_WINDOW_Y-28)/2+70, 245, 28, hdcMem, 0, 0, SRCPAINT);
        SelectObject(hdcMem, enter_white);
        BitBlt(hdcBuffer, (DEFAULT_WINDOW_X-245)/2, (DEFAULT_WINDOW_Y-28)/2+70, 245, 28, hdcMem, 0, 0, SRCAND);

        Player1->disabled = true;
        Player2->disabled = true;
    }
    else if (Player2->hp <= 0 || ((Player2->hp < Player1->hp) && game_timer >= GAME_TIMER))
    {
        SelectObject(hdcMem, win1_black);
        BitBlt(hdcBuffer, (DEFAULT_WINDOW_X-293)/2, (DEFAULT_WINDOW_Y-35)/2, 293, 35, hdcMem, 0, 0, SRCPAINT);
        SelectObject(hdcMem, win1_white);
        BitBlt(hdcBuffer, (DEFAULT_WINDOW_X-293)/2, (DEFAULT_WINDOW_Y-35)/2, 293, 35, hdcMem, 0, 0, SRCAND);

        SelectObject(hdcMem, enter_black);
        BitBlt(hdcBuffer, (DEFAULT_WINDOW_X-245)/2, (DEFAULT_WINDOW_Y-28)/2+70, 245, 28, hdcMem, 0, 0, SRCPAINT);
        SelectObject(hdcMem, enter_white);
        BitBlt(hdcBuffer, (DEFAULT_WINDOW_X-245)/2, (DEFAULT_WINDOW_Y-28)/2+70, 245, 28, hdcMem, 0, 0, SRCAND);

        Player1->disabled = true;
        Player2->disabled = true;
    }
    else if ((Player1->hp == Player2->hp) && game_timer >= GAME_TIMER)
    {
        SelectObject(hdcMem, nowin_black);
        BitBlt(hdcBuffer, (DEFAULT_WINDOW_X-182)/2, (DEFAULT_WINDOW_Y-35)/2, 293, 35, hdcMem, 0, 0, SRCPAINT);
        SelectObject(hdcMem, nowin_white);
        BitBlt(hdcBuffer, (DEFAULT_WINDOW_X-182)/2, (DEFAULT_WINDOW_Y-35)/2, 293, 35, hdcMem, 0, 0, SRCAND);

        SelectObject(hdcMem, enter_black);
        BitBlt(hdcBuffer, (DEFAULT_WINDOW_X-245)/2, (DEFAULT_WINDOW_Y-28)/2+70, 245, 28, hdcMem, 0, 0, SRCPAINT);
        SelectObject(hdcMem, enter_white);
        BitBlt(hdcBuffer, (DEFAULT_WINDOW_X-245)/2, (DEFAULT_WINDOW_Y-28)/2+70, 245, 28, hdcMem, 0, 0, SRCAND);

        Player1->disabled = true;
        Player2->disabled = true;
    }

    SelectObject(hdcMem, hbmOld);
    DeleteDC(hdcMem);

    BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcBuffer, 0, 0, SRCCOPY);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteDC(hdcBuffer);
    DeleteObject(hbmBuffer);
    ReleaseDC(hwnd, hdc);
}

void displayArenaSelect(HWND hwnd)
{
    HDC hdc = GetDC(hwnd);
    RECT rect;
    GetClientRect(hwnd, &rect);

    HDC hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
    HBITMAP hbmOldBuffer = (HBITMAP) SelectObject(hdcBuffer, hbmBuffer);
    HDC hdcMem = CreateCompatibleDC(hdc);

    HBITMAP hbmOld = (HBITMAP) SelectObject (hdcMem, arena.hbmSelect);

    arena.selectArena(hwnd, hdcMem, hdcBuffer);

    SelectObject(hdcMem, hbmOld);
    DeleteDC(hdcMem);

    BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcBuffer, 0, 0, SRCCOPY);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteDC(hdcBuffer);
    DeleteObject(hbmBuffer);
    ReleaseDC(hwnd, hdc);
}

void displayPlayerSelect(HWND hwnd, int player)
{
    HDC hdc = GetDC(hwnd);
    RECT rect;
    GetClientRect(hwnd, &rect);

    HDC hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
    HBITMAP hbmOldBuffer = (HBITMAP) SelectObject(hdcBuffer, hbmBuffer);
    HDC hdcMem = CreateCompatibleDC(hdc);

    HBITMAP hbmOld;

    if (player == 0)
    {
        hbmOld = (HBITMAP) SelectObject (hdcMem, hbmNewGame);
        BitBlt(hdcBuffer, 0, 0, SELECT_X, SELECT_Y, hdcMem, 0, 0, SRCCOPY);
    }
    else if (player == 1)
    {
        hbmOld = (HBITMAP) SelectObject (hdcMem, hbmP1S);
        BitBlt(hdcBuffer, 0, 0, SELECT_X, SELECT_Y, hdcMem, 0, 0, SRCCOPY);
    }
    else if (player == 2)
    {
        hbmOld = (HBITMAP) SelectObject (hdcMem, hbmP2S);
        BitBlt(hdcBuffer, 0, 0, SELECT_X, SELECT_Y, hdcMem, 0, 0, SRCCOPY);
    }

    SelectObject(hdcMem, hbmOld);
    DeleteDC(hdcMem);

    BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcBuffer, 0, 0, SRCCOPY);
    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteDC(hdcBuffer);
    DeleteObject(hbmBuffer);
    ReleaseDC(hwnd, hdc);
}

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Mortal Kombat (Lite Version)"),       /* Title Text */
           WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           608,                 /* The programs width */
           372,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (TRUE)
    {
        DWORD time_begin;
        while (PeekMessage (&messages, NULL, 0, 0, PM_REMOVE))
        {
            if (messages.message == WM_QUIT)
                break;
            /* Translate virtual-key messages into character messages */
            TranslateMessage(&messages);
            /* Send message to WindowProcedure */
            DispatchMessage(&messages);
        }
        time_begin = GetTickCount();

        if (!newGame)
            displayPlayerSelect(hwnd, 0);
        else if (!player1Selected)
            displayPlayerSelect(hwnd, 1);
        else if (!player2Selected)
            displayPlayerSelect(hwnd, 2);
        else if (!arenaSelected)
            displayArenaSelect(hwnd);
        else
        {
            display(hwnd);
            input.CheckInput(Player1, Player2, hwnd);

            if (game_timer >= GAME_TIMER && !endGame)
            {
                endGame = true;
                if (Player1->hp < Player2->hp)
                {
                    if (Player2->type == WARRIOR2)
                        play_sound_main("sounds/scorpion_win.wav", hwnd);
                    else
                        play_sound_main("sounds/sonya_win.wav", hwnd);
                }
                else if (Player1->hp > Player2->hp)
                {
                    if (Player1->type == WARRIOR1)
                        play_sound_main("sounds/scorpion_win.wav", hwnd);
                    else
                        play_sound_main("sounds/sonya_win.wav", hwnd);
                }
            }

            if ((Player1->hp <= 5 || Player2->hp <= 0) && !endGame)
            {
                endGame = true;
                if (Player1->hp <= 5)
                {
                    if (Player2->type == WARRIOR2)
                        play_sound_main("sounds/scorpion_win.wav", hwnd);
                    else
                        play_sound_main("sounds/sonya_win.wav", hwnd);
                }
                else if (Player2->hp <= 0)
                {
                    if (Player1->type == WARRIOR1)
                        play_sound_main("sounds/scorpion_win.wav", hwnd);
                    else
                        play_sound_main("sounds/sonya_win.wav", hwnd);
                }
            }
        }
        while (GetTickCount() - time_begin < 40)
        {
            Sleep(5);
        }
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    unsigned int t;
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            Player1Select = PLAYER1SONYA;
            Player2Select = PLAYER2WARRIOR;
            t=SetTimer(hwnd,TIMER_ID_1,1000,NULL);
            SetWindowPos(hwnd,0,0,0,SELECT_X+8,SELECT_Y+32,0);
            load();
            mciSendString("open sounds/theme.wav type waveaudio alias mydev", NULL, 0, NULL);
            mciSendString("play mydev notify", NULL, 0, hwnd);
            break;
        case MM_MCINOTIFY:
            mciSendCommand((MCIDEVICEID)lParam, MCI_CLOSE, 0, 0);
            break;
        case WM_LBUTTONDOWN:
            {
                int xPos = LOWORD(lParam);
                int yPos = HIWORD(lParam);
                if (!newGame)
                {
                    if (xPos >= 140 && xPos <= 140+430 && yPos >= 270 && yPos <= 270 + 74)
                    {
                        newGame = true;
                        play_sound_main("sounds/choose.wav", hwnd);
                    }
                    else if (xPos >= 146 && xPos <= 146+421 && yPos >= 401 && yPos <= 401 + 77)
                    {
                        exit(0);
                    }
                }
                else if (!player1Selected)
                {
                    if (xPos >= 148 && xPos <= 148+276 && yPos >= 437 && yPos <= 437 + 70)
                    {
                        Player1Select = PLAYER1WARRIOR;
                        player1Selected = true;
                        play_sound_main("sounds/scorpion_name.wav", hwnd);
                    }
                    else if (xPos >= 554 && xPos <= 554+282 && yPos >= 441 && yPos <= 441 + 63)
                    {
                        Player1Select = PLAYER1SONYA;
                        player1Selected = true;
                        play_sound_main("sounds/sonya_name.wav", hwnd);
                    }
                }
                else if (!player2Selected)
                {
                    if (xPos >= 148 && xPos <= 148+276 && yPos >= 437 && yPos <= 437 + 70)
                    {
                        Player2Select = PLAYER2WARRIOR;
                        player2Selected = true;
                        play_sound_main("sounds/scorpion_name.wav", hwnd);
                        loadFighters();
                    }
                    else if (xPos >= 554 && xPos <= 554+282 && yPos >= 441 && yPos <= 441 + 63)
                    {
                        Player2Select = PLAYER2SONYA;
                        player2Selected = true;
                        play_sound_main("sounds/sonya_name.wav", hwnd);
                        loadFighters();
                    }
                }
                if (!arenaSelected)
                {
                    if (xPos >= 63 && xPos <= 63+84 && yPos >= 85 && yPos <= 85 + 24)
                    {
                        arena.setArena(VOLCANO_ARENA);
                        arenaSelected = true;
                        mciSendString("stop mydev notify", NULL, 0, hwnd);
                        mciSendString("open sounds/theme1.wav type waveaudio alias theme1", NULL, 0, NULL);
                        mciSendString("play theme1 notify", NULL, 0, hwnd);
                        play_sound_main("sounds/fight.wav", hwnd);
                        game_timer = 0;
                        arena.counterx = 0;
                        arena.countery = 0;
                        SetWindowPos(hwnd,0,0,0,DEFAULT_WINDOW_X,DEFAULT_WINDOW_Y,0);
                    }
                    else if (xPos >= 450 && xPos <= 450+84 && yPos >= 398 && yPos <= 398 + 24)
                    {
                        arena.setArena(MOON_ARENA);
                        arenaSelected = true;
                        mciSendString("stop mydev notify", NULL, 0, hwnd);
                        mciSendString("open sounds/theme2.wav type waveaudio alias theme2", NULL, 0, NULL);
                        mciSendString("play theme2 notify", NULL, 0, hwnd);
                        play_sound_main("sounds/fight.wav", hwnd);
                        game_timer = 0;
                        arena.counterx = 0;
                        arena.countery = 0;
                        SetWindowPos(hwnd,0,0,0,DEFAULT_WINDOW_X,DEFAULT_WINDOW_Y,0);
                    }
                    else if (xPos >= 840 && xPos <= 840+84 && yPos >= 250 && yPos <= 250 + 24)
                    {
                        arena.setArena(TEMPLE_ARENA);
                        arenaSelected = true;
                        mciSendString("stop mydev notify", NULL, 0, hwnd);
                        mciSendString("open sounds/theme3.wav type waveaudio alias theme3", NULL, 0, NULL);
                        mciSendString("play theme3 notify", NULL, 0, hwnd);
                        play_sound_main("sounds/fight.wav", hwnd);
                        game_timer = 0;
                        arena.counterx = 0;
                        arena.countery = 0;
                        SetWindowPos(hwnd,0,0,0,DEFAULT_WINDOW_X,DEFAULT_WINDOW_Y,0);
                    }
                }
            }
            break;
        case WM_KEYDOWN:
            {
                switch (wParam)
                {
                    case VK_RETURN:
                        if (endGame)
                        {
                            reset(hwnd);
                            SetWindowPos(hwnd,0,0,0,SELECT_X+8,SELECT_Y+32,0);
                        }
                    break;
                }
                break;
            }
        case WM_TIMER:
            ++game_timer;
            arena.counterx += 2;
            if (arena.counterx > 5)
            {
                arena.countery++;
                if (arena.countery > 29)
                    arena.countery = 0;
                arena.counterx = 0;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            KillTimer(hwnd, TIMER_ID_1);
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
