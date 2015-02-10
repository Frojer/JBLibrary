#ifdef _DEBUG
#pragma once

#include<windows.h>
#include"../Global/JBGLBString.h"

namespace JBL{
    /// @brief 로그를 표시하기 위한 클래스
    class JBCORLogWindow{
    private:
        HWND ins_thisHwnd;
    public:
        JBCORLogWindow(const HINSTANCE&);
        virtual ~JBCORLogWindow();
    public:
        /// @brief 로그창의 핸들을 반환합니다.
        /// @return 로그 핸들
        inline HWND getHWND()const{ return ins_thisHwnd; }
    public:
        /// @brief 로그를 표시합니다.
        /// @param str 메세지(멀티바이트)
        /// @param attribute 메세지 구분(0: 일반, 1: 성공, 2: 경고, 3: 실패, 4: 정보)
        inline void addLog(const _STRING& str, const char attribute){ return ins_pushLog(STRING::glb_ansiToWide(str.c_str()), attribute); }
        /// @brief 로그를 표시합니다.
        /// @param str 메세지(와이드바이트)
        /// @param attribute 메세지 구분(0: 일반, 1: 성공, 2: 경고, 3: 실패, 4: 정보)
        inline void addLog(const _WSTRING& str, const char attribute){ return ins_pushLog(str, attribute); }
    private:
        void ins_pushLog(const _WSTRING&, const char);
        void ins_addLog(const _WSTRING&, const char);
        void ins_eraseFirstLog();
    private:
        /// @brief 로그 다이얼로그 메세지 프로세스
        static INT_PTR CALLBACK ins_mainProc(HWND hDlg, _UINT msg, WPARAM wParam, LPARAM lParam);
    };
};
#endif