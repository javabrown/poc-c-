#include <windows.h>
#include "Win.h"
#include <stdio.h>

const char g_szClassName[] = "myWindowClass";

LRESULT CALLBACK RkWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
		case WM_CREATE:
		{
			//MessageBox(NULL, "WM_CREATE Called", "Close Signal Found!", MB_ICONEXCLAMATION | MB_OK);
	        hCloseBTN = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Close",
	        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 10, 80, 40, hwnd, NULL,
	        GetModuleHandle(NULL), NULL);
		}
		break;
		
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case BN_CLICKED:

				if(hCloseBTN == (HWND)lParam)
				{
				 printf("Hello World");
				  
					int iResult = MessageBox(NULL, "Want to code?", "Close", MB_YESNO | MB_ICONQUESTION);
					if(iResult == IDYES){
						DestroyWindow(hwnd);
					}
					else if(iResult == IDNO){
						return false;
					}
				}
			}
		}
		break;
	

        case WM_LBUTTONDOWN:
        {
            char szFileName[MAX_PATH];
            HINSTANCE hInstance = GetModuleHandle(NULL);

            GetModuleFileName(hInstance, szFileName, MAX_PATH);
            MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
        }
        break;
        case WM_CLOSE:
		{
			MessageBox(NULL, "Window Creation Failed!", "Close Signal Found!", MB_ICONEXCLAMATION | MB_OK);
            DestroyWindow(hwnd);
		}
        break;
        case WM_DESTROY:
		{
			MessageBox(NULL, "Window Creation Failed!", "Distroy Signal Found!", MB_ICONEXCLAMATION | MB_OK);
            PostQuitMessage(0);
		}
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = RkWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "The title of my window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 840, 520,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
	
	//HWND hCloseBTN = CreateWindowEx(WS_EX_WINDOWEDGE, "BUTTON", "Close",
	//	WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 50, 80, 30, hwnd, NULL,
	//	GetModuleHandle(NULL), NULL);
		
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
