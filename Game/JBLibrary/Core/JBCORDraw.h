#pragma once

#include"../JBDirectXHeader.hpp"
#include"../Base/JBBASWndProc.h"

namespace JBL{
    class JBCORWindow;

    /// @brief DirectX11 객체
    class JBCORDraw : public JBBASWndProc{
    private:
        JBCORWindow* ins_windowInst;
    private:
        _SIZE_T ins_vRamMemory;
        wchar_t* ins_vCardName;
    private:
        IDXGISwapChain* ins_swapChain;
        ID3D11Device* ins_device;
        ID3D11DeviceContext* ins_deviceContext;
    public:
        JBCORDraw(JBCORWindow* windowInst);
        virtual ~JBCORDraw();
    public:
        __forceinline void getVideoCardInfo(_WSTRING& name, _SIZE_T* ram){ name = ins_vCardName; if (ram)*ram = ins_vRamMemory; };
    public:
        __forceinline IDXGISwapChain* getSwapChain(){ return ins_swapChain; };
        __forceinline ID3D11Device* getDevice(){ return ins_device; };
        __forceinline ID3D11DeviceContext* getDeviceContext(){ return ins_deviceContext; };
    private:
        /// @brief 윈도우 클래스에 할당된 메세지 프로세스
        LRESULT ins_curProc(HWND, _UINT, WPARAM, LPARAM);
    };
};