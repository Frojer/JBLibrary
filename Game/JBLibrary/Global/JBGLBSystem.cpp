#include<io.h>
#include<direct.h>

#include"JBGlobalFunc.h"
#include"../Core/JBCoreModule.h"

using namespace JBL;

_INT SYSTEM::glb_infoMsg(const MESSAGE_TYPE type, const char* msg){
    _UINT flag;
    switch (type){
    case IF_ERROR:
        flag = MB_OK | MB_ICONERROR;
        break;
    case IF_WARNING:
        flag = MB_OK | MB_ICONWARNING;
        break;
    case IF_INFO:
        flag = MB_OK | MB_ICONINFORMATION;
        break;
    }

#ifdef _DEBUG
    _STRING er;
    switch (type){
    case IF_ERROR:
        er = "[ERROR] ";
        _LOG_F(msg);
        break;
    case IF_WARNING:
        er = "[WARNING] ";
        _LOG_W(msg);
        break;
    case IF_INFO:
        er = "[INFO] ";
        _LOG(msg);
        break;
    }
    er += msg;
    OutputDebugStringA(er.c_str());
#endif
    return MessageBoxA(nullptr, msg, "JBL::Message", flag);
}
_INT SYSTEM::glb_infoMsg(const MESSAGE_TYPE type, const wchar_t* msg){
    _UINT flag;
    switch (type){
    case IF_ERROR:
        flag = MB_OK | MB_ICONERROR;
        break;
    case IF_WARNING:
        flag = MB_OK | MB_ICONWARNING;
        break;
    case IF_INFO:
        flag = MB_OK | MB_ICONINFORMATION;
        break;
    }

#ifdef _DEBUG
    _WSTRING er;
    switch (type){
    case IF_ERROR:
        er = L"[ERROR] ";
        _LOG_F(msg);
        break;
    case IF_WARNING:
        er = L"[WARNING] ";
        _LOG_W(msg);
        break;
    case IF_INFO:
        er = L"[INFO] ";
        _LOG(msg);
        break;
    }
    er += msg;
    OutputDebugStringW(er.c_str());
#endif
    return MessageBoxW(nullptr, msg, L"JBL::Message", flag);
}

bool SYSTEM::glb_makeDir(const char* path, const _SIZE_T len){
    _SIZE_T lastSlash = 0;

    auto p = path + (len - 1);
    for (lastSlash = len - 1; lastSlash > 0; --lastSlash){
        if (*p == '\\' || *p == '/')break;
        --p;
    }
    ++lastSlash;

    static char* tmpBuf = nullptr;
    static _SIZE_T tmpBufSz = 0;

    p = path;
    for (auto i = decltype(lastSlash){0}; i < lastSlash; ++i){
        if (*p == '\\' || *p == '/'){
            if (i + 1 > tmpBufSz){
                tmpBufSz = i + 1;
                _FREE(tmpBuf);
                tmpBuf = _ALLOC<char>(tmpBufSz);
                if (!tmpBuf)goto UTIL_MKPATH_A_FAIL;
            }
            tmpBuf[i] = '\0';

            if (strncpy_s(tmpBuf, i + 1, path, i))goto UTIL_MKPATH_A_FAIL;

            if (_access(tmpBuf, 0) < 0){
                if (_mkdir(tmpBuf) < 0)goto UTIL_MKPATH_A_FAIL;
            }
        }
        ++p;
    }

    _FREE(tmpBuf); tmpBufSz = 0;
    return true;

UTIL_MKPATH_A_FAIL:
    _FREE(tmpBuf); tmpBufSz = 0;
    return false;
}
bool SYSTEM::glb_makeDir(const wchar_t* path, const _SIZE_T len){
    _SIZE_T lastSlash = 0;

    auto p = path + (len - 1);
    for (lastSlash = len - 1; lastSlash > 0; --lastSlash){
        if (*p == L'\\' || *p == L'/')break;
        --p;
    }
    ++lastSlash;

    static wchar_t* tmpBuf = nullptr;
    static _SIZE_T tmpBufSz = 0;

    p = path;
    for (auto i = decltype(lastSlash){0}; i < lastSlash; ++i){
        if (*p == L'\\' || *p == L'/'){
            if (i + 1 > tmpBufSz){
                tmpBufSz = i + 1;
                _FREE(tmpBuf);
                tmpBuf = _ALLOC<wchar_t>(tmpBufSz);
                if (!tmpBuf)goto UTIL_MKPATH_W_FAIL;
            }
            tmpBuf[i] = L'\0';

            if (wcsncpy_s(tmpBuf, i + 1, path, i))goto UTIL_MKPATH_W_FAIL;

            if (_waccess(tmpBuf, 0) < 0){
                if (_wmkdir(tmpBuf) < 0)goto UTIL_MKPATH_W_FAIL;
            }
        }
        ++p;
    }

    _FREE(tmpBuf); tmpBufSz = 0;
    return true;

UTIL_MKPATH_W_FAIL:
    _FREE(tmpBuf); tmpBufSz = 0;
    return false;
}

POINT SYSTEM::glb_getScreenSize(){
    auto hdc = GetDC(nullptr);
    POINT pt = { GetDeviceCaps(hdc, HORZRES), GetDeviceCaps(hdc, VERTRES) };
    ReleaseDC(nullptr, hdc);

    return pt;
}

void SYSTEM::glb_setFocus(const HWND& hWnd){
    SetFocus(hWnd);
    SetForegroundWindow(hWnd);
}