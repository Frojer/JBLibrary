#include"../../resource.h"

#include<vector>

#include<windows.h>
#include<commctrl.h>

#include"JBCoreModule.h"
#include"../Global/JBGlobalFunc.h"

using namespace JBL;

#define NUMBER_BUFFER_SIZE 64

#define FONT_NAME L"Courier New"
#define FONT_SIZE 9

#define COLOR_BACK_LIGHT 0x1e1e1e
#define COLOR_BACK_DARK 0x1c1c1c

#define COLOR_BACK_SELECT_STRING 0x333333

#define COLOR_BACK_SELECT_NUM 0x4aab2e
#define COLOR_BACK_NUM 0x592447

#define COLOR_OBJ_STRING_NORMAL 0xdadada
#define COLOR_OBJ_STRING_SUCCESS 0xc27d35
#define COLOR_OBJ_STRING_WARNNING 0x35c0c2
#define COLOR_OBJ_STRING_FAIL 0x3535c2
#define COLOR_OBJ_STRING_INFO 0x38c235

#define COLOR_OBJ_SELECT_NUM 0x5d5025
#define COLOR_OBJ_NUM 0x877fd7

#define BOX_PADDING_X 2
#define BOX_PADDING_Y 1

#define MAX_ITEM_COUNT 128

struct LIST_ITEM{
    wchar_t* num;
    wchar_t* str;
    char attribute;
    _WORD hig;
};
_VECTOR<LIST_ITEM> stringTable;
_SIZE_T totalCount = 0;

HFONT defaultFont = nullptr;

HWND listStringHwnd = nullptr;
HWND listNumHwnd = nullptr;

JBCORLogWindow::JBCORLogWindow(const HINSTANCE& hInst){
    ins_thisHwnd = CreateDialog(
        hInst,
        MAKEINTRESOURCE(IDD_LOGDLG),
        nullptr,
        ins_mainProc
        );
    if (!ins_thisHwnd)throw _ERROR_EXCEPTION(L"JBL::JBCORLogWindow: failed to call CreateDialog.");

    listStringHwnd = GetDlgItem(ins_thisHwnd, IDC_LIST);
    if (!listStringHwnd)throw _ERROR_EXCEPTION(L"JBL::JBCORLogWindow: failed to call GetDlgItem(IDC_LIST).");

    listNumHwnd = GetDlgItem(ins_thisHwnd, IDC_LISTNUM);
    if (!listNumHwnd)throw _ERROR_EXCEPTION(L"JBL::JBCORLogWindow: failed to call GetDlgItem(IDC_LISTNUM).");

    ShowWindow(ins_thisHwnd, SW_SHOW);
}
JBCORLogWindow::~JBCORLogWindow(){
    DestroyWindow(ins_thisHwnd);
    ins_thisHwnd = nullptr;

    while (!stringTable.empty()){
        auto i = stringTable.cbegin();
        auto tar = i->str;
        _FREE(tar);
        stringTable.erase(i);
    }
}

/// @brief 로그 메세지 추가 및 포커스를 갱신합니다.
/// @param str 메세지(와이드바이트)
/// @param attribute 메세지 구분(0: 일반, 1: 성공, 2: 경고, 3: 실패, 4: 정보)
void JBCORLogWindow::ins_pushLog(const _WSTRING& str, const char attribute){
    auto pos = stringTable.size();
    if (pos >= MAX_ITEM_COUNT){
        ins_eraseFirstLog();
        --pos;
    }
    ins_addLog(str, attribute);

    SNDMSG(listNumHwnd, LB_SETCURSEL, pos, 0);
    SNDMSG(listStringHwnd, LB_SETCURSEL, pos, 0);
}
/// @brief 로그 메세지를 추가합니다.
/// @param str 메세지(와이드바이트)
/// @param attribute 메세지 구분(0: 일반, 1: 성공, 2: 경고, 3: 실패, 4: 정보)
void JBCORLogWindow::ins_addLog(const _WSTRING& str, const char attribute){
    LIST_ITEM add;
    add.attribute = attribute;

    _WSTRING _new;
    {
#ifdef _WIN64
        _new = _MOVE(STRING::glb_strFormat(NUMBER_BUFFER_SIZE, L"%llu", ++totalCount));
#else
        _new = _MOVE(STRING::glb_strFormat(NUMBER_BUFFER_SIZE, L"%u", ++totalCount));
#endif

        auto len = _new.length() + 1;
        add.num = _ALLOC<wchar_t>(len);
        wcscpy_s(add.num, len, _new.c_str());


        _new.clear();
        for (_SIZE_T i = 0, e = str.length(); i < e; ++i){
            if (str[i] == L'\n')_new += L"\r\n";
            else if (str[i] == L'\\')_new += L'/';
            else _new += str[i];
        }

        len = _new.length() + 1;
        add.str = _ALLOC<wchar_t>(len);
        wcscpy_s(add.str, len, _new.c_str());
    }

    {
        RECT listRT;
        GetClientRect(listStringHwnd, &listRT);

        auto dc = GetDC(listStringHwnd);

        auto fntOld = (HFONT)SelectObject(dc, defaultFont);
        RECT rt = { 0, 0, listRT.right - listRT.left, 0 };
        rt.left += BOX_PADDING_X; rt.top += BOX_PADDING_Y;
        rt.right -= BOX_PADDING_X; rt.bottom -= BOX_PADDING_Y;
        DrawTextEx(
            dc, (wchar_t*)_new.c_str(), (_INT)(_new.length()), &rt,
            DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_TOP | DT_WORDBREAK, nullptr
            );
        rt.left -= BOX_PADDING_X; rt.top -= BOX_PADDING_Y;
        rt.right += BOX_PADDING_X; rt.bottom += BOX_PADDING_Y;
        SelectObject(dc, fntOld);

        ReleaseDC(listStringHwnd, dc);

        add.hig = _WORD(rt.bottom);
    }

    stringTable.emplace_back(add);

    SNDMSG(listNumHwnd, LB_ADDSTRING, 0, (LPARAM)stringTable.back().num);
    SNDMSG(listStringHwnd, LB_ADDSTRING, 0, (LPARAM)stringTable.back().str);
}
/// @brief 가장 처음에 추가된 로그를 삭제합니다.
void JBCORLogWindow::ins_eraseFirstLog(){
    SNDMSG(listNumHwnd, LB_DELETESTRING, 0, 0);
    SNDMSG(listStringHwnd, LB_DELETESTRING, 0, 0);

    auto i = stringTable.cbegin();
    wchar_t* tar = i->str;
    _FREE(tar);
    stringTable.erase(i);
}

INT_PTR CALLBACK JBCORLogWindow::ins_mainProc(HWND hDlg, _UINT msg, WPARAM wParam, LPARAM lParam){
    static HBRUSH backColorLight = nullptr;
    static HBRUSH backColorDark = nullptr;

    switch (msg){
    case WM_INITDIALOG:
    {
        InitCommonControls();

        auto listHwnd = GetDlgItem(hDlg, IDC_LIST);

        {
            LOGFONT fntLog = { 0 };
            wcscpy_s(fntLog.lfFaceName, ARRAYSIZE(fntLog.lfFaceName), FONT_NAME);

            auto dc = GetDC(listHwnd);
            fntLog.lfHeight = -MulDiv(FONT_SIZE, GetDeviceCaps(dc, LOGPIXELSY), 72);
            ReleaseDC(listHwnd, dc);

            defaultFont = CreateFontIndirect(&fntLog);
        }

        {
            backColorLight = CreateSolidBrush(COLOR_BACK_LIGHT);
            backColorDark = CreateSolidBrush(COLOR_BACK_DARK);
        }

        break;
    }
    case WM_DESTROY:
    {
        DeleteObject(defaultFont);

        DeleteObject(backColorLight);
        DeleteObject(backColorDark);
        break;
    }

    case WM_CTLCOLORLISTBOX:
    {
        auto hWnd = (HWND)lParam;

        if (hWnd == listStringHwnd){
            return (LRESULT)(stringTable.size() % 2 ? backColorLight : backColorDark);
        }
        else if (hWnd == listNumHwnd){
            return (LRESULT)(stringTable.size() % 2 ? backColorDark : backColorLight);
        }
        break;
    }

    case WM_MEASUREITEM:
    {
        auto mur = (LPMEASUREITEMSTRUCT)lParam;

        if (mur->CtlType == ODT_LISTBOX){
            switch (mur->CtlID){
            case IDC_LIST:
            case IDC_LISTNUM:
                mur->itemHeight = stringTable[mur->itemID].hig;
                break;
            }
        }
        break;
    }
    case WM_DRAWITEM:
    {
        auto lDraw = (LPDRAWITEMSTRUCT)lParam;

        if (lDraw->CtlType == ODT_LISTBOX){
            auto dc = lDraw->hDC;
            auto lItem = lDraw->itemID;

            auto oldTexCol = GetTextColor(dc);
            auto oldBkCol = GetBkColor(dc);

            auto fntOld = (HFONT)SelectObject(dc, defaultFont);

            if (lDraw->CtlID == IDC_LIST){
                switch (stringTable[lItem].attribute){
                case 0: SetTextColor(dc, COLOR_OBJ_STRING_NORMAL); break;
                case 1: SetTextColor(dc, COLOR_OBJ_STRING_SUCCESS); break;
                case 2: SetTextColor(dc, COLOR_OBJ_STRING_WARNNING); break;
                case 3: SetTextColor(dc, COLOR_OBJ_STRING_FAIL); break;
                case 4: SetTextColor(dc, COLOR_OBJ_STRING_INFO); break;
                }
                if ((lDraw->itemAction | ODA_SELECT) && (lDraw->itemState & ODS_SELECTED))SetBkColor(dc, COLOR_BACK_SELECT_STRING);
                else if (lItem % 2)SetBkColor(dc, COLOR_BACK_LIGHT);
                else SetBkColor(dc, COLOR_BACK_DARK);

                auto hbr = lItem % 2 ? CreateSolidBrush(COLOR_BACK_LIGHT) : CreateSolidBrush(COLOR_BACK_DARK);
                FillRect(dc, &lDraw->rcItem, hbr);
                DeleteObject(hbr);

                lDraw->rcItem.left += BOX_PADDING_X; lDraw->rcItem.top += BOX_PADDING_Y;
                lDraw->rcItem.right -= BOX_PADDING_X; lDraw->rcItem.bottom -= BOX_PADDING_Y;
                DrawTextEx(
                    dc, stringTable[lItem].str, (_INT)(wcslen(stringTable[lItem].str)), &lDraw->rcItem,
                    DT_LEFT | DT_NOPREFIX | DT_TOP | DT_WORDBREAK, nullptr
                    );
                lDraw->rcItem.left -= BOX_PADDING_X; lDraw->rcItem.top -= BOX_PADDING_Y;
                lDraw->rcItem.right += BOX_PADDING_X; lDraw->rcItem.bottom += BOX_PADDING_Y;
            }
            else if (lDraw->CtlID == IDC_LISTNUM){
                static HBRUSH hbr = nullptr;
                if ((lDraw->itemAction | ODA_SELECT) && (lDraw->itemState & ODS_SELECTED)){
                    SetTextColor(dc, COLOR_OBJ_SELECT_NUM);
                    SetBkColor(dc, COLOR_BACK_SELECT_NUM);
                    hbr = CreateSolidBrush(COLOR_BACK_SELECT_NUM);
                }
                else{
                    SetTextColor(dc, COLOR_OBJ_NUM);
                    SetBkColor(dc, COLOR_BACK_NUM);
                    hbr = CreateSolidBrush(COLOR_BACK_NUM);
                }
                FillRect(dc, &lDraw->rcItem, hbr);
                DeleteObject(hbr);

                lDraw->rcItem.left += BOX_PADDING_X; lDraw->rcItem.top += BOX_PADDING_Y;
                lDraw->rcItem.right -= BOX_PADDING_X; lDraw->rcItem.bottom -= BOX_PADDING_Y;
                DrawTextEx(
                    dc, stringTable[lItem].num, (_INT)(wcslen(stringTable[lItem].num)), &lDraw->rcItem,
                    DT_RIGHT | DT_NOPREFIX | DT_TOP | DT_WORDBREAK, nullptr
                    );
                lDraw->rcItem.left -= BOX_PADDING_X; lDraw->rcItem.top -= BOX_PADDING_Y;
                lDraw->rcItem.right += BOX_PADDING_X; lDraw->rcItem.bottom += BOX_PADDING_Y;
            }

            SelectObject(dc, fntOld);

            SetBkColor(dc, oldBkCol);
            SetTextColor(dc, oldTexCol);
        }
        break;
    }
    break;

    case WM_COMMAND:
    {
        auto _event = HIWORD(wParam);
        auto _id = LOWORD(wParam);

        switch (_event){
        case LBN_SELCHANGE:
        case LBN_SETFOCUS:
        {
            _INT index = -1;
            auto hWnd = (HWND)lParam;

            if (_id == IDC_LIST){
                index = (_INT)(SNDMSG(hWnd, LB_GETCURSEL, 0, 0));
                SNDMSG(GetDlgItem(hDlg, IDC_LISTNUM), LB_SETCURSEL, index, 0);
            }
            else if (_id == IDC_LISTNUM){
                index = (_INT)(SNDMSG(hWnd, LB_GETCURSEL, 0, 0));
                SNDMSG(GetDlgItem(hDlg, IDC_LIST), LB_SETCURSEL, index, 0);
            }
            break;
        }
        }
        break;
    }

    default:
        return FALSE;
    }

    return TRUE;
}