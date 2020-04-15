#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <stdio.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
POINT slovoE [ ] =
{
    {114,157},
    {70,157},
    {70,187},
    {104,187},
    {70,187},
    {70,217},
    {114,217}
};
POINT points [3];
POINT slovoD [] = { {204,187},{164,187},{164,217},{204,217} };
POINT slovoR [] = { {304,217},{304,187},{304,187},{324,187} };

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
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, /* default window */
               100,       /* Windows decides the position */
               100,       /* where the window ends up on the screen */
               408,                 /* The programs width */
               408,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int cxClient, cyClient;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)                  /* handle the messages */
    {
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);

        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd,&ps);
        points[0] = {cxClient/2-150,128};
        points[1] = {cxClient/2,50};
        points[2] = {cxClient/2+150,128};

        SelectObject(hdc, (HBRUSH)CreateSolidBrush(RGB(100,180,100)));
        SelectObject(hdc,(HPEN)CreatePen(PS_SOLID,1,RGB(0,255,0)));
        //printf("%d\n",(cxClient/2)+150 - ((cxClient/2)-150) );
        //printf("%d",cyClient-(cyClient/8)-(cyClient-(cyClient/3)));
        Rectangle(hdc,(cxClient/2)-150,cyClient-(cyClient/3),(cxClient/2)+150,cyClient-(cyClient/8));

        DeleteObject(SelectObject(hdc,(HBRUSH) CreateHatchBrush(HS_DIAGCROSS,RGB(200,0,0))));
        DeleteObject(SelectObject(hdc, (HPEN) CreatePen(PS_SOLID,1,RGB(200,0,0))));
        SetBkColor(hdc,RGB(255,100,100));
        Polygon(hdc,points,3);

        DeleteObject(SelectObject(hdc,(HBRUSH) GetStockObject(WHITE_BRUSH)));
        DeleteObject(SelectObject(hdc, (HPEN) GetStockObject(BLACK_PEN)));
        Rectangle(hdc,(cxClient/2)-150, (cyClient/2)-50,(cxClient/2)+150,(cyClient/2)+50);
        // printf("%d",(cyClient/2)-50);

        SelectObject(hdc,(HPEN) CreatePen(PS_SOLID, 10, RGB(0,0,0)));
        MoveToEx(hdc,slovoE[1].x,slovoE[1].y,NULL);
        PolylineTo(hdc,slovoE,7);

        MoveToEx(hdc,144,slovoE[6].y,NULL);
        LineTo(hdc,144,157);

        MoveToEx(hdc,204,slovoE[6].y,NULL);
        LineTo(hdc,204,157);

        MoveToEx(hdc,slovoD[0].x,slovoD[0].y,NULL);
        PolyBezier(hdc,slovoD,4);

        for(auto i = 0; i<4;++i)
        {
            slovoD[i].x += 60;
            if(i<2)
            slovoD[i].y +=5;
        }
        slovoD[3].x +=10;

        //MoveToEx(hdc,slovoD[0].x,slovoD[0].y,NULL);
        PolyBezier(hdc,slovoD,4);

        slovoD[1].x = slovoD[0].x;
        slovoD[1].y = slovoD[2].y = 170;
        slovoD[2].x = slovoD[3].x = slovoD[0].x-25;
        slovoD[3].y = slovoD[0].y-20;

        //MoveToEx(hdc,slovoD[0].x,217,NULL);
        PolyBezier(hdc,slovoD,4);

        MoveToEx(hdc,slovoD[0].x,slovoD[0].y,NULL);
        LineTo(hdc,slovoD[0].x,217);

        MoveToEx(hdc,304,217,NULL);
        LineTo(hdc,304,183);

        PolyBezier(hdc,slovoR,4);

        slovoD[0].x = slovoD[3].x = 204;
        slovoD[0].y = slovoD[1].y = 187;
        slovoD[1].x = slovoD[2].x = 164;
        slovoD[2].y = slovoD[3].y = 217;
        DeleteObject(SelectObject(hdc, (HPEN) GetStockObject(BLACK_PEN)));

        EndPaint(hwnd,&ps);
        break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
