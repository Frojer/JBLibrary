#include"JBGlobalFunc.h"

using namespace JBL;
using namespace JBL::SYSTEM;

_STRING STRING::glb_wideToAnsi(const wchar_t* str, const _UINT codePage){
    auto len = WideCharToMultiByte(codePage, 0, str, -1, nullptr, 0, nullptr, nullptr);

    auto out = _ALLOC<char>(len + 1);
    if (!out)return _STRING();

    WideCharToMultiByte(codePage, 0, str, -1, out, len, nullptr, nullptr);

    return _STRING(_MOVE(out));
}
_WSTRING STRING::glb_ansiToWide(const char* str, const _UINT codePage){
    auto len = MultiByteToWideChar(codePage, 0, str, -1, nullptr, 0);

    auto out = _ALLOC<wchar_t>(len + 1);
    if (!out)return _WSTRING();

    MultiByteToWideChar(codePage, 0, str, -1, out, len);

    return _WSTRING(_MOVE(out));
}

_STRING STRING::glb_strFormat(const _SIZE_T bufSz, const char* str, ...){
    va_list iterat;
    va_start(iterat, str);

    auto out = _ALLOC<char>(bufSz);
    if (!out)return _STRING();

    vsprintf_s(out, bufSz, str, iterat);

    va_end(iterat);

    return _STRING(_MOVE(out));
}
_WSTRING STRING::glb_strFormat(const _SIZE_T bufSz, const wchar_t* str, ...){
    va_list iterat;
    va_start(iterat, str);

    auto out = _ALLOC<wchar_t>(bufSz);
    if (!out)return _WSTRING();

    vswprintf_s(out, bufSz, str, iterat);

    va_end(iterat);

    return _WSTRING(_MOVE(out));
}