#pragma once

#include<windows.h>
#include"JBGLBCustomString.hpp"
#include"JBGlobalMacro.hpp"

namespace JBL{
    namespace STRING{
        /// @brief 와이드바이트 문자열을 멀티바이트 문자열로 반환합니다.
        /// @param str 변환할 대상(와이드바이트)
        /// @param codePage 인코딩 페이지
        /// @return 변환 결과(멀티바이트)
        extern _STRING glb_wideToAnsi(const wchar_t* str, const _UINT codePage = CP_ACP);
        /// @brief 멀티바이트 문자열을 와이드바이트 문자열로 반환합니다.
        /// @param str 변환할 대상(멀티바이트)
        /// @param codePage 인코딩 페이지
        /// @return 변환 결과(와이드바이트)
        extern _WSTRING glb_ansiToWide(const char* str, const _UINT codePage = CP_ACP);

        /// @brief printf와 같이 인자들이 각종 구분자에 따라 변환된 문자열을 반환합니다.
        /// @param bufSz 반환될 문자열의 최대 크기
        /// @param str 구분자를 포함한 문자열(멀티바이트)
        /// @param ... 구분자에 해당하는 인자
        /// @return 변환 결과(멀티바이트)
        extern _STRING glb_strFormat(const _SIZE_T bufSz, const char* str, ...);
        /// @brief printf와 같이 인자들이 각종 구분자에 따라 변환된 문자열을 반환합니다.
        /// @param bufSz 반환될 문자열의 최대 크기
        /// @param str 구분자를 포함한 문자열(와이드바이트)
        /// @param ... 구분자에 해당하는 인자
        /// @return 변환 결과(와이드바이트)
        extern _WSTRING glb_strFormat(const _SIZE_T bufSz, const wchar_t* str, ...);
    };
};