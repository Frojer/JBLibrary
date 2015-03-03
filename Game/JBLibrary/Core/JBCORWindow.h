#pragma once

#include"../Base/JBBASWndProc.h"

namespace JBL{
    /// @brief 윈도우 객체
    class JBCORWindow : public JBBASWndProc{
    private:
        HINSTANCE ins_hInst;
        HWND ins_hWnd;

        POINT ins_formSize;
    public:
        JBCORWindow(const HINSTANCE&);
        virtual ~JBCORWindow();
    public:
        /// @brief glb_workSpace의 크기로 클라이언트 크기를 설정한 뒤, ins_formSize에 폼 크기를 반환합니다.
        ///     \n 윈도우는 중앙으로 옮겨집니다.
        /// @return 성공 여부
        bool resizeWindow();
    public:
        /// @brief 윈도우의 핸들을 반환합니다.
        /// @return 윈도우 핸들
        inline HWND getHWND()const{ return ins_hWnd; }
    private:
        /// @brief 윈도우 클래스에 할당된 메세지 프로세스
        LRESULT ins_curProc(HWND, _UINT, WPARAM, LPARAM);
    };
};