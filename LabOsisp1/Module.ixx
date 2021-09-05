
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>


// Global variables
int x=0, y=0;
// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");
// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("lab1");
HINSTANCE hInst;
HDC hDC, hCompatibleDC;
//HANDLE hBitmap;
// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND hWnd;

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    //—труктура содержит сведени€ о окне: значок приложени€, цвет фона окна, им€, отображаемое в строке заголовка, помимо прочего. ¬ажно, что он содержит указатель на функцию окна.
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    HWND hWnd = CreateWindowEx(WS_EX_COMPOSITED,szWindowClass,szTitle,WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,CW_USEDEFAULT, CW_USEDEFAULT,1000, 500, NULL,NULL,hInstance,NULL);
    //hBitmap = LoadImage(NULL, L"Image.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }
    ShowWindow(hWnd,nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   //код дл€ управлени€ сообщени€ми, получаемые приложением от Windows при возникновении событий.например,
    //если пользователь нажмет кнопку "ок" в приложении, Windows отправит вам сообщение, 
    //и вы сможете написать код внутри WndProc функции, который подходит дл€ любой работы.
    //ќн называетс€ обработкой событи€.¬ы обрабатываете только те событи€, которые относ€тс€ к вашему приложению.
          
    TCHAR greeting[] = _T("");    
    HANDLE hBitmap;
    
    PAINTSTRUCT ps;
    HBRUSH hBrush;    
    static int wheelDelta = 0;

    switch (message)
    {

    case WM_CREATE: {

                break;
    }
    case WM_MOUSEWHEEL: {
        wheelDelta += GET_WHEEL_DELTA_WPARAM(wParam);
        for (; wheelDelta > WHEEL_DELTA; wheelDelta -= WHEEL_DELTA)//up scroll
        {
            if (GetKeyState(VK_SHIFT) < 0) {
                if (x != 880)
                    x += 5;
                else {
                    for (int i = 0; i < 8; i += 1) {
                        Sleep(20);
                        x -= 5;
                        InvalidateRect(hWnd, NULL, TRUE);
                        UpdateWindow(hWnd);
                    }
                }
            }
            else {
                if (y != 0) 
                    y -= 5;
                else {
                    for (int i = 0; i < 8; i += 1) {
                        Sleep(20);
                        y += 5;
                        InvalidateRect(hWnd, NULL, TRUE);
                        UpdateWindow(hWnd);
                    }
                }
                
            }
        }

        for (; wheelDelta < 0; wheelDelta += WHEEL_DELTA)//down scroll
        {

            if (GetKeyState(VK_SHIFT) < 0) {
                if (x != 0)
                    x -= 5;
                else {
                    for (int i = 0; i < 8; i += 1) {
                        Sleep(20);
                        x += 5;
                        InvalidateRect(hWnd, NULL, TRUE);
                        UpdateWindow(hWnd);
                    }
                }
            }
            else if (y != 360) {
                y += 5;
            }
            else {
                for (int i = 0; i < 8; i += 1) {
                    Sleep(20);
                    y -= 5;
                    InvalidateRect(hWnd, NULL, TRUE);
                    UpdateWindow(hWnd);
                }
            }

        }
        InvalidateRect(hWnd, NULL, TRUE);
        UpdateWindow(hWnd);
    }
    case WM_KEYDOWN: {
        switch (wParam) {
        case VK_LEFT:
            if (x != 0)
                x -= 5;
            else {
                for (int i = 0; i < 8; i += 1) {
                    Sleep(20);
                    x += 5;
                    InvalidateRect(hWnd, NULL, TRUE);
                    UpdateWindow(hWnd);
                }                
            }
            break;

        case VK_RIGHT:
            if (x != 880)
                x += 5; 
            else {
                for (int i = 0; i < 8; i += 1) {
                    Sleep(20);
                    x -= 5;
                    InvalidateRect(hWnd, NULL, TRUE);
                    UpdateWindow(hWnd);
                }
            }
            break;

        case VK_UP:
            if (y != 0)
                y -= 5;
            else {
                for (int i = 0; i < 8; i += 1) {
                    Sleep(20);
                    y += 5;
                    InvalidateRect(hWnd, NULL, TRUE);
                    UpdateWindow(hWnd);
                }
            }
            break;

        case VK_DOWN:
            if (y != 360)
                y += 5;
            else {
                for (int i = 0; i < 8; i += 1) {
                    Sleep(20);
                    y -= 5;
                    InvalidateRect(hWnd, NULL, TRUE);
                    UpdateWindow(hWnd);
                }
            }
            break;

        default:
            break;
        }
        InvalidateRect(hWnd, NULL, TRUE);
        UpdateWindow(hWnd);
    }    
    case WM_MOUSEMOVE: {

        if (wParam == MK_LBUTTON) {
            x = LOWORD(lParam) / 10;
            y = HIWORD(lParam) / 10;
            x *= 10;
            y *= 10;
            if (x > 880 && x < 1000) {
                x = 880;
                for (int i = 0; i < 8; i += 1) {
                    Sleep(20);
                    x -= 5;
                    InvalidateRect(hWnd, NULL, TRUE);
                    UpdateWindow(hWnd);
                }
            }
            if (y > 360) {
                y = 360;
                for (int i = 0; i < 8; i += 1) {
                    Sleep(20);
                    y -= 5;
                    InvalidateRect(hWnd, NULL, TRUE);
                    UpdateWindow(hWnd);
                }
            }
            if (x == 0) {
                for (int i = 0; i < 8; i += 1) {
                    Sleep(20);
                    x += 5;
                    InvalidateRect(hWnd, NULL, TRUE);
                    UpdateWindow(hWnd);
                }
            }
            if (y == 0) {
                for (int i = 0; i < 8; i += 1) {
                    Sleep(20);
                    y += 5;
                    InvalidateRect(hWnd, NULL, TRUE);
                    UpdateWindow(hWnd);
                }
            }
            InvalidateRect(hWnd, NULL, TRUE);
            UpdateWindow(hWnd);
        }
    }
    case WM_PAINT:{               
                    
            hBitmap = (HBITMAP)LoadImage(NULL, L"Image.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            GetObject(hBitmap, sizeof(BITMAP), NULL);
            hDC = BeginPaint(hWnd, &ps);
            hCompatibleDC = CreateCompatibleDC(hDC);
            SelectObject(hCompatibleDC, hBitmap);          
            BitBlt(hDC, x, y, 100, 100, hCompatibleDC, NULL, NULL, SRCCOPY);
            DeleteObject(hCompatibleDC);
            DeleteDC(hDC);
            EndPaint(hWnd, &ps);
            DeleteObject(hBitmap);

    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
     
    return 0;
}

