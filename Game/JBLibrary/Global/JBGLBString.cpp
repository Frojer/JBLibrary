#include"JBGlobalFunc.h"

using namespace JBL;
using namespace JBL::SYSTEM;

_STRING STRING::glb_wideToAnsi(const wchar_t* str, const _UINT codePage){
    auto len = WideCharToMultiByte(codePage, 0, str, -1, nullptr, 0, nullptr, nullptr);

    auto out = _ALLOC<char>(len + 1);
#ifdef _DEBUG
    if (!out)throw _ERROR_EXCEPTION(L"JBL::STRING::glb_wideToAnsi: failed to allocate memory.");
#endif

    WideCharToMultiByte(codePage, 0, str, -1, out, len, nullptr, nullptr);

    return _STRING(_MOVE(out));
}
_WSTRING STRING::glb_ansiToWide(const char* str, const _UINT codePage){
    auto len = MultiByteToWideChar(codePage, 0, str, -1, nullptr, 0);

    auto out = _ALLOC<wchar_t>(len + 1);
#ifdef _DEBUG
    if (!out)throw _ERROR_EXCEPTION(L"JBL::STRING::glb_ansiToWide: failed to allocate memory.");
#endif

    MultiByteToWideChar(codePage, 0, str, -1, out, len);

    return _WSTRING(_MOVE(out));
}

_STRING STRING::glb_strFormat(const _SIZE_T bufSz, const char* str, ...){
    va_list iterat;
    va_start(iterat, str);

    auto out = _ALLOC<char>(bufSz);
#ifdef _DEBUG
    if (!out)throw _ERROR_EXCEPTION(L"JBL::STRING::glb_strFormat: failed to allocate memory.");
#endif

    vsprintf_s(out, bufSz, str, iterat);

    va_end(iterat);

    return _STRING(_MOVE(out));
}
_WSTRING STRING::glb_strFormat(const _SIZE_T bufSz, const wchar_t* str, ...){
    va_list iterat;
    va_start(iterat, str);

    auto out = _ALLOC<wchar_t>(bufSz);
#ifdef _DEBUG
    if (!out)throw _ERROR_EXCEPTION(L"JBL::STRING::glb_strFormat: failed to allocate memory.");
#endif

    vswprintf_s(out, bufSz, str, iterat);

    va_end(iterat);

    return _WSTRING(_MOVE(out));
}