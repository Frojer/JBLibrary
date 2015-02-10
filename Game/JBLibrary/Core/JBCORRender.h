#pragma once

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>
#include"../Base/JBBASWndProc.h"

namespace JBL{
    class JBCORDraw;

    /// @brief 렌더링 객체
    class JBCORRender : public JBBASWndProc{
    private:
        JBCORDraw* ins_drawInst;
    private:
        ID3D11Texture2D* ins_depthStencilBuffer;
        ID3D11RenderTargetView* ins_renderTargetView;
        ID3D11DepthStencilState* ins_depthStencilState;
        ID3D11DepthStencilView* ins_depthStencilView;
        ID3D11RasterizerState* ins_rasterState;
    public:
        JBCORRender(JBCORDraw* drawInst);
        virtual ~JBCORRender();
    public:
        bool update();
    private:
        /// @brief 윈도우 클래스에 할당된 메세지 프로세스
        LRESULT ins_curProc(HWND, _UINT, WPARAM, LPARAM);
    };
};