#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
float cordinates [5];
std::ifstream file;

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
    wincl.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;                 /* Catch double-clicks */
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
        WS_OVERLAPPEDWINDOW, /* default window */
        CW_USEDEFAULT,       /* Windows decides the position */
        CW_USEDEFAULT,       /* where the window ends up on the screen */
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
    static int cxClient,cyClient;
    std::string line;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)                  /* handle the messages */
    {
    case WM_SIZE:
        cyClient = HIWORD(lParam);
        cxClient = LOWORD(lParam);
        break;
    case WM_PAINT:
        file.open("oblici.txt");
        if(!file.is_open())
        {
            perror("Error with opening");
            exit(0);
        }

        hdc = BeginPaint(hwnd,&ps);
        while(std::getline(file,line))
        {
            if(line.empty())
            {
                std::cout << line << std::endl;
            }
            else if (( line.at(0) == 'B' || line.at(0) == 'C' || line.at(0) == 'L'
                       || line.at(0) == 'R' || line.at(0) == 'H' || line.at(0) == 'E'
                       || line.at(0) == 'S' ) && line.at(1)==' ')
            {
                std::cout << line << std::endl;
                int i = 1, start, len, num = 0;
                bool option = false;
                char op;

                while(i<line.size())
                {
                    while(line.at(i)==' ') ++i;

                    if((line.at(i)>'a' && line.at(i)<'z') || (line.at(i)>'A' && line.at(i)<'Z'))
                    {
                        option = true;
                        op = line.at(i);
                        ++i;
                    }

                    while(line.at(i)==' ') ++i;

                    start = i;
                    len = 0;
                    while(i<line.size())
                    {
                        ++len;
                        if(line.at(i)==' ') break;
                        ++i;
                    }
                    cordinates[num] = stof(line.substr(start,len)) /100.0;
                    // std::cout << cordinates[num] << std::endl;
                    ++num;
                }

                switch(line.at(0))
                {
                case 'E':
                    if(num<3)
                    {
                        std::cout << "Need more cordinates at \"" << line << "\"" <<std::endl;
                        exit(0);
                    }
                    else
                    {

                       // std::cout << cordinates[0]-cordinates[2] << " " << cordinates[1]-cordinates[2];
                        Ellipse(hdc,cxClient * (cordinates[0]),
                                cyClient * (cordinates[1]),
                                cxClient * (cordinates[2]),
                                cyClient * (cordinates[3]));
                    }
                    break;
                case 'B':
                case 'H':
                    if(num<3)
                    {
                        std::cout << "Need more cordinates at \"" << line << "\"" <<std::endl;
                        exit(0);
                    }
                    else
                    {
                        for(auto i =0; i<num; ++i)
                            cordinates[i] *= 100.0;
                        if(option && op == 'B')
                        {
                            DeleteObject(SelectObject(hdc,(HBRUSH) CreateHatchBrush(HS_BDIAGONAL,RGB(cordinates[0],
                                                      cordinates[1],
                                                      cordinates[2]))));
                        }
                        else
                        {
                            DeleteObject(SelectObject(hdc,(HBRUSH) CreateSolidBrush(RGB(cordinates[0],
                                                      cordinates[1],
                                                      cordinates[2]))));
                        }
                    }
                    break;
                case 'C':
                    if(option)
                    {
                        switch(op)
                        {
                        case 'S':
                            if(num<4)
                            {
                                std::cout << "Need more cordinates at \"" << line << "\"" <<std::endl;
                                exit(0);
                            }
                            else
                            {
                                for(auto i =0; i<num; ++i)
                                    cordinates[i] *= 100.0;
                                DeleteObject(SelectObject(hdc,(HPEN) CreatePen(PS_DASH,cordinates[0],
                                                          RGB(cordinates[1],
                                                              cordinates[2],
                                                              cordinates[3]))));
                            }
                            break;
                        }
                    }
                    else
                    {
                        if(num<3)
                        {
                            std::cout << "Need more cordinates at \"" << line << "\"" <<std::endl;
                            exit(0);
                        }
                        else
                        {
                            cordinates[2] /= 8.0;
                            //std::cout << cordinates[0]-cordinates[2] << " " << cordinates[1]-cordinates[2];
                            Ellipse(hdc,cxClient * (cordinates[0]-cordinates[2]),
                                    cyClient * (cordinates[1]-cordinates[2]),
                                    cxClient * (cordinates[0]+cordinates[2]),
                                    cyClient * (cordinates[1]+cordinates[2]));
                        }
                    }
                    break;
                case 'L':
                    if(num<4)
                    {
                        std::cout << "Need more cordinates at \"" << line << "\"" <<std::endl;
                        exit(0);
                    }
                    else
                    {
                        MoveToEx(hdc,cxClient*cordinates[0],cyClient*cordinates[1],NULL);
                        LineTo(hdc, cxClient*cordinates[2],cyClient*cordinates[3]);
                    }
                    break;
                case 'R':
                    if(num<4)
                    {
                        std::cout << "Need more cordinates at \"" << line << "\"" <<std::endl;
                        exit(0);
                    }
                    else
                    {
                        Rectangle(hdc, cxClient * cordinates[0],
                                  cyClient * cordinates[1],
                                  cxClient * cordinates[2],
                                  cyClient * cordinates[3]);
                    }
                    break;
                case 'S':
                    if(num<3)
                    {
                        std::cout << "Need more cordinates at \"" << line << "\"" <<std::endl;
                        exit(0);
                    }
                    else
                    {
                        cordinates[2] /= 8.0;
                        Rectangle(hdc,cxClient * (cordinates[0]-cordinates[2]),
                                    cyClient * (cordinates[1]-cordinates[2]),
                                    cxClient * (cordinates[0]+cordinates[2]),
                                    cyClient * (cordinates[1]+cordinates[2]));
                    }
                    break;
                }
            }
            else
            {
                std::cout << line << std::endl;
            }
        }
        DeleteObject(SelectObject(hdc,(HPEN) GetStockObject(BLACK_PEN)));
        DeleteObject(SelectObject(hdc,(HBRUSH) GetStockObject(WHITE_BRUSH)));
        EndPaint(hwnd,&ps);
        file.close();
        break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
