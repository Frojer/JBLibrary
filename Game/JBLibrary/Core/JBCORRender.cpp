#include"JBCoreModule.h"

using namespace JBL;
using namespace JBL::SYSTEM;

#define JBL_DXGI_FORMAT_D24 DXGI_FORMAT_D24_UNORM_S8_UINT

JBCORRender::JBCORRender(JBCORDraw* drawInst) : JBBASWndProc(){
    ins_drawInst = drawInst;


    // 백 버퍼를 구함
    ID3D11Texture2D* backBufferPtr = nullptr;
    if (FAILED(ins_drawInst->getSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferPtr)))
        throw _ERROR_EXCEPTION(L"JBL::JBCORRender: failed to call IDXGISwapChain::GetBuffer(backBuf).");
    _LOG_S(L"JBL::JBCORRender: succeeded to call IDXGISwapChain::GetBuffer(backBuf).");

    // 렌더 타겟 뷰를 구함
    if (FAILED(ins_drawInst->getDevice()->CreateRenderTargetView(backBufferPtr, nullptr, &ins_renderTargetView)))
        throw _ERROR_EXCEPTION(L"JBL::JBCORRender: failed to call ID3D11Device::CreateRenderTargetView.");
    _LOG_S(L"JBL::JBCORRender: succeeded to call ID3D11Device::CreateRenderTargetView.");

    _RELEASE(backBufferPtr);

    // 깊이 버퍼 DESC 구성
    D3D11_TEXTURE2D_DESC depthBufferDesc;
    ZeroMemory(&depthBufferDesc, sizeof depthBufferDesc);
    depthBufferDesc.Width = (decltype(depthBufferDesc.Width))glb_workSpace.x;
    depthBufferDesc.Height = (decltype(depthBufferDesc.Height))glb_workSpace.y;
    depthBufferDesc.MipLevels = 1;
    depthBufferDesc.ArraySize = 1;
    depthBufferDesc.Format = JBL_DXGI_FORMAT_D24;
    depthBufferDesc.SampleDesc.Count = 1;
    depthBufferDesc.SampleDesc.Quality = 0;
    depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthBufferDesc.CPUAccessFlags = 0;
    depthBufferDesc.MiscFlags = 0;

    // 깊이 스텐실 버퍼 생성
    if (FAILED(ins_drawInst->getDevice()->CreateTexture2D(
        &depthBufferDesc,
        nullptr,
        &ins_depthStencilBuffer
        )))
        throw _ERROR_EXCEPTION(L"JBL::JBCORRender: failed to call ID3D11Device::CreateTexture2D(depthStencilBuf).");
    _LOG_S(L"JBL::JBCORRender: succeeded to call ID3D11Device::CreateTexture2D(depthStencilBuf).");

    // 깊이 스텐실 상태 DESC 구성
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof depthStencilDesc);
    depthStencilDesc.DepthEnable = TRUE;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
    depthStencilDesc.StencilEnable = TRUE;
    depthStencilDesc.StencilReadMask = 0xFF;
    depthStencilDesc.StencilWriteMask = 0xFF;
    depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    // 깊이 스텐실 상태 생성
    if (FAILED(ins_drawInst->getDevice()->CreateDepthStencilState(
        &depthStencilDesc,
        &ins_depthStencilState
        )))
        throw _ERROR_EXCEPTION(L"JBL::JBCORRender: failed to call ID3D11Device::CreateDepthStencilState.");
    _LOG_S(L"JBL::JBCORRender: succeeded to call ID3D11Device::CreateDepthStencilState.");

    // 깊이 스텐실 상태 적용
    ins_drawInst->getDeviceContext()->OMSetDepthStencilState(ins_depthStencilState, 1);

    // 깊이 스텐실 뷰 DESC 구성
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    ZeroMemory(&depthStencilViewDesc, sizeof depthStencilViewDesc);
    depthStencilViewDesc.Format = JBL_DXGI_FORMAT_D24;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    // 깊이 스텐실 뷰 생성
    if (FAILED(ins_drawInst->getDevice()->CreateDepthStencilView(
        ins_depthStencilBuffer,
        &depthStencilViewDesc,
        &ins_depthStencilView
        )))
        throw _ERROR_EXCEPTION(L"JBL::JBCORRender: failed to call ID3D11Device::CreateDepthStencilView.");
    _LOG_S(L"JBL::JBCORRender: succeeded to call ID3D11Device::CreateDepthStencilView.");

    // 렌더링 파이프 라인에 ins_renderTargetView 및 ins_depthStencilView 적용
    ins_drawInst->getDeviceContext()->OMSetRenderTargets(1, &ins_renderTargetView, ins_depthStencilView);

    // 래스터라이저 DESC 구성
    D3D11_RASTERIZER_DESC rasterDesc;
    ZeroMemory(&rasterDesc, sizeof rasterDesc);
    rasterDesc.AntialiasedLineEnable = FALSE;
    rasterDesc.CullMode = D3D11_CULL_BACK;
    rasterDesc.DepthBias = 0;
    rasterDesc.DepthBiasClamp = 0.0f;
    rasterDesc.DepthClipEnable = TRUE;
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.FrontCounterClockwise = FALSE;
    rasterDesc.MultisampleEnable = FALSE;
    rasterDesc.ScissorEnable = FALSE;
    rasterDesc.SlopeScaledDepthBias = 0.0f;

    // 래스터라이저 상태 생성
    if (FAILED(ins_drawInst->getDevice()->CreateRasterizerState(&rasterDesc, &ins_rasterState)))
        throw _ERROR_EXCEPTION(L"JBL::JBCORRender: failed to call ID3D11Device::CreateRasterizerState.");
    _LOG_S(L"JBL::JBCORRender: succeeded to call ID3D11Device::CreateRasterizerState.");

    // 래스터라이저 적용
    ins_drawInst->getDeviceContext()->RSSetState(ins_rasterState);
}
JBCORRender::~JBCORRender(){
    if (ins_drawInst->getSwapChain())ins_drawInst->getSwapChain()->SetFullscreenState(FALSE, nullptr);

    _RELEASE(ins_rasterState);
    _RELEASE(ins_depthStencilView);
    _RELEASE(ins_depthStencilState);
    _RELEASE(ins_depthStencilBuffer);
    _RELEASE(ins_renderTargetView);
}

bool JBCORRender::update(){
    static COLOR::RGBA_32BIT backColor(0.f, 0.f, 0.f, 1.f);


    // begin
    ins_drawInst->getDeviceContext()->ClearRenderTargetView(ins_renderTargetView, (float*)backColor.rgba);
    ins_drawInst->getDeviceContext()->ClearDepthStencilView(ins_depthStencilView, D3D11_CLEAR_DEPTH, 1.f, 0);
    //



    // end
    ins_drawInst->getSwapChain()->Present(glb_state[JBL_STATE_VSYNC] ? 1 : 0, 0);
    //

    return true;
}

LRESULT JBCORRender::ins_curProc(HWND hWnd, _UINT msg, WPARAM wParam, LPARAM lParam){
    return ins_nextProc(hWnd, msg, wParam, lParam);
}