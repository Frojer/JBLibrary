#include"JBCoreModule.h"
#include"../../resource.h"

using namespace JBL;
using namespace JBL::SYSTEM;

JBCORWindow::JBCORWindow(const HINSTANCE& hInst) : JBBASWndProc(){
    ins_hInst = hInst;

    WNDCLASSEX cls;
    cls.cbSize = sizeof WNDCLASSEX;
    cls.style = CS_HREDRAW | CS_VREDRAW;
    cls.lpfnWndProc = ins_firstProc;
    cls.cbClsExtra = 0;
    cls.cbWndExtra = 0;
    cls.hInstance = ins_hInst;
    cls.hCursor = LoadCursor(ins_hInst, IDC_ARROW);
    cls.hIcon = LoadIcon(ins_hInst, MAKEINTRESOURCE(IDI_GAME));
    cls.hIconSm = cls.hIcon;
    cls.hIconSm = nullptr;
    cls.hbrBackground = (decltype(cls.hbrBackground))GetStockObject(BLACK_BRUSH);
    cls.lpszClassName = glb_className;
    cls.lpszMenuName = nullptr;
    if (!RegisterClassEx(&cls))throw _ERROR_EXCEPTION(L"JBL::JBCORWindow::JBCORWindow: failed to call RegisterClassEx.");
    _LOG_S(L"JBL::JBCORWindow::JBCORWindow: succeeded to call RegisterClassEx.");

    ins_hWnd = CreateWindowEx(
        WS_OVERLAPPED,
        glb_className,
        glb_titleName,
        WS_SYSMENU | WS_CAPTION,
        0, 0,
        glb_workSpace.x, glb_workSpace.y,
        nullptr, nullptr,
        ins_hInst,
        nullptr
        );
    if (!ins_hWnd)throw _ERROR_EXCEPTION(L"JBL::JBCORWindow::JBCORWindow: failed to call CreateWindowEx.");
    _LOG_S(L"JBL::JBCORWindow::JBCORWindow: succeeded to call CreateWindowEx.");

    if (!resizeWindow())throw _ERROR_EXCEPTION();
}
JBCORWindow::~JBCORWindow(){
    PostQuitMessage(0);
    UnregisterClass(glb_className, ins_hInst);
}

bool JBCORWindow::resizeWindow(){
    ins_formSize = glb_workSpace;

    RECT client;
    GetClientRect(ins_hWnd, &client);

    ins_formSize.x = ins_formSize.x * 2 - (client.right - client.left);
    ins_formSize.y = ins_formSize.y * 2 - (client.bottom - client.top);

    POINT screen = glb_getScreenSize();
    if (!MoveWindow(
        ins_hWnd,
        (screen.x - ins_formSize.x) / 2,
        (screen.y - ins_formSize.y) / 2,
        ins_formSize.x,
        ins_formSize.y,
        FALSE
        )){
        glb_infoMsg(IF_ERROR, L"JBL::JBCORWindow::resizeWindow: failed to call MoveWindow.");
        return false;
    }
    _LOG_S(L"JBL::JBCORWindow::resizeWindow: succeeded to call MoveWindow.");

    ShowWindow(ins_hWnd, SW_SHOW);

    if (!UpdateWindow(ins_hWnd)){
        glb_infoMsg(IF_ERROR, L"JBL::JBCORWindow::resizeWindow: failed to call UpdateWindow.");
        return false;
    }
    _LOG_S(L"JBL::JBCORWindow::resizeWindow: succeeded to call UpdateWindow.");

    return true;
}

LRESULT JBCORWindow::ins_curProc(HWND hWnd, _UINT msg, WPARAM wParam, LPARAM lParam){
    switch (msg){
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_ACTIVATEAPP:
        if (wParam == TRUE){
            _SETFOCUS_LOG;
            _LOG_I(L"JBL::JBCORWindow::ins_curProc: window is activated.");
        }
        else{
            _LOG_I(L"JBL::JBCORWindow::ins_curProc: window is deactivated.");
        }
        break;
    }
    return ins_nextProc(hWnd, msg, wParam, lParam);
}