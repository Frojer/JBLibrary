#pragma once

#include<windows.h>
#include<forward_list>
#include"../Global/JBGlobalFunc.h"

namespace JBL{
    class JBCORWindow;

    /// @brief 싱글톤 형태의 주요 객체들이 윈도우 메세지를 처리할 수 있도록 윈도우 프로세스를 리스트로 구성합니다.
    /// @details 이 객체의 소멸 순서는 생성 순서의 반대가 되기 때문에 _UNIQUE_PTR과 같은 스마트 포인터를 활용하여 자동 소멸이 이루어 지도록 합시다.
    class JBBASWndProc{
    private:
        static _FORWARD_LIST<JBBASWndProc*> ins_classTable;
        static _FORWARD_LIST<JBBASWndProc*>::const_iterator ins_beginItr;
        static _FORWARD_LIST<JBBASWndProc*>::const_iterator ins_beforeEndItr;
    private:
        _FORWARD_LIST<JBBASWndProc*>::const_iterator ins_curItr;
    protected:
        JBBASWndProc();
        virtual ~JBBASWndProc();
    protected:
        /// @brief 가장 마지막에 생성된 객체의 윈도우 프로세스를 반환합니다. 윈도우 초기화 당시에 대입되는 것을 권장합니다.
        static inline LRESULT CALLBACK ins_firstProc(HWND hWnd, _UINT msg, WPARAM wParam, LPARAM lParam){
            return (*ins_beginItr)->ins_curProc(hWnd, msg, wParam, lParam);
        }
    protected:
        /// @brief 다음 노드에 존재하는 윈도우 프로세스를 반환합니다.
        inline LRESULT ins_nextProc(HWND hWnd, _UINT msg, WPARAM wParam, LPARAM lParam){
            return ins_curItr != ins_beforeEndItr ?
                ins_curItr._Ptr->_Next->_Myval->ins_curProc(hWnd, msg, wParam, lParam) :
                DefWindowProc(hWnd, msg, wParam, lParam);
        }
    protected:
        /// @brief 순수 가상 함수로써 상속받은 다른 객체에서 정의가 이루어져야 할 부분입니다.
        ///     \n 반환은 반드시 ins_nextProc(...)가 되어야 합니다.
        virtual LRESULT ins_curProc(HWND, _UINT, WPARAM, LPARAM) = 0;
    };
};