﻿// AStar.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "WinMain.h"
#include "Visualization.h"

#define MAX_LOADSTRING 100




// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND gHWnd;
RECT gWindowRect = { 0, 0, Visualization::WINDOW_WIDTH, Visualization::WINDOW_HEIGHT };
Visualization gVisualization;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASTAR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


    // Visualization 타일 세팅 초기화
    gVisualization.Initialize();

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASTAR));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASTAR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASTAR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   gHWnd = CreateWindowEx(0, szTitle, szTitle, WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
       CW_USEDEFAULT, CW_USEDEFAULT, Visualization::WINDOW_WIDTH, Visualization::WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

   if (gHWnd == NULL)
       return FALSE;

   ShowWindow(gHWnd, SW_SHOW);
   UpdateWindow(gHWnd);
   SetFocus(gHWnd);

   AdjustWindowRectEx(&gWindowRect, GetWindowStyle(gHWnd), GetMenu(gHWnd) != NULL,
       GetWindowExStyle(gHWnd));

   int x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (Visualization::WINDOW_WIDTH / 2); //화면의 크기를 얻어서 정 중앙으로
   int y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (Visualization::WINDOW_HEIGHT / 2);

   MoveWindow(gHWnd, x, y,
       gWindowRect.right - gWindowRect.left, gWindowRect.bottom - gWindowRect.top, TRUE);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    HDC memDC;
    HBITMAP selectBitmap;
    HBITMAP oldBitmap;
    PAINTSTRUCT ps;
    //static POINT mousePoint;
    static Visualization::RectInfo rectInfo;
    static BYTE rButtonCount = 0;
    static bool isClip = false;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_LBUTTONDOWN:
        {
            isClip = true;
            rectInfo.point.x = LOWORD(lParam);
            rectInfo.point.y = HIWORD(lParam);
            //ScreenToClient(gHWnd, &rectInfo.point);
            wprintf(L"X: %d Y: %d\n", rectInfo.point.x, rectInfo.point.y);
            rectInfo.index = Visualization::BLOCK_INDEX;
            gVisualization.SetTilePicking(rectInfo);
            InvalidateRect(hWnd, NULL, false);
        }
        break;
    case WM_LBUTTONUP:
        {
            isClip = false;
        }
        break;
    case WM_RBUTTONDOWN:
        {
            if (rButtonCount >= 2)
            {
                rButtonCount = 0;
            }
            rectInfo.point.x = LOWORD(lParam);
            rectInfo.point.y = HIWORD(lParam);
            //ScreenToClient(gHWnd, &rectInfo.point);
            wprintf(L"X: %d Y: %d\n", rectInfo.point.x, rectInfo.point.y);
            if(rButtonCount == 0)
                rectInfo.index = Visualization::START_INDEX;
            else if(rButtonCount == 1)
                rectInfo.index = Visualization::FINISH_INDEX;
            gVisualization.SetTilePicking(rectInfo);
            InvalidateRect(hWnd, NULL, false);
            ++rButtonCount;
        }
        break;
    case WM_MOUSEMOVE:
        {
            if (isClip)
            {
                rectInfo.point.x = LOWORD(lParam);
                rectInfo.point.y = HIWORD(lParam);
                //ScreenToClient(gHWnd, &rectInfo.point);
                wprintf(L"X: %d Y: %d\n", rectInfo.point.x, rectInfo.point.y);
                rectInfo.index = Visualization::BLOCK_INDEX;
                gVisualization.SetTilePicking(rectInfo);
                InvalidateRect(hWnd, NULL, false);
            }
        }
        break;
    case WM_PAINT:
        {
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            hdc = BeginPaint(hWnd, &ps);
            //	DoubleBuffering
            memDC = CreateCompatibleDC(hdc);
            selectBitmap = CreateCompatibleBitmap(hdc, Visualization::WINDOW_WIDTH, Visualization::WINDOW_HEIGHT);
            oldBitmap = (HBITMAP)SelectObject(memDC, selectBitmap);
            //	Begin work
            SetBkMode(memDC, TRANSPARENT);
            SetTextColor(memDC, RGB(255, 255, 255));
            FillRect(memDC, &gWindowRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
            gVisualization.CreateTile(memDC);
            

            BitBlt(hdc, 0, 0, Visualization::WINDOW_WIDTH, Visualization::WINDOW_HEIGHT, memDC, 0, 0, SRCCOPY);

            SelectObject(memDC, oldBitmap);
            DeleteObject(selectBitmap);
            DeleteDC(memDC);
            EndPaint(hWnd, &ps);

        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}