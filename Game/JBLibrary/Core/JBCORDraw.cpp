#include"JBCoreModule.h"

using namespace JBL;
using namespace JBL::SYSTEM;

#define JBL_DXGI_FORMAT_R8G8B8A8 DXGI_FORMAT_R8G8B8A8_UNORM

JBCORDraw::JBCORDraw(JBCORWindow* windowInst) : JBBASWndProc(){
    ins_windowInst = windowInst;


    // 그래픽 인터페이스 생성
    IDXGIFactory* factory = nullptr;
    if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
        throw _ERROR_EXCEPTION(L"JBL::JBCORDraw::JBCORDraw: failed to call CreateDXGIFactory.");
    _LOG_S(L"JBL::JBCORDraw::JBCORDraw: succeeded to call CreateDXGIFactory.");

    // 그래픽 어댑터 생성(그래픽 카드)
    IDXGIAdapter* adapter = nullptr;
    if (FAILED(factory->EnumAdapters(0, &adapter)))
        throw _ERROR_EXCEPTION(L"JBL::JBCORDraw::JBCORDraw: failed to call IDXGIFactory::EnumAdapters.");
    _LOG_S(L"JBL::JBCORDraw::JBCORDraw: succeeded to call IDXGIFactory::EnumAdapters.");

    // 그래픽 출력 장치 열거(모니터)
    IDXGIOutput* adapterOutput = nullptr;
    if (FAILED(adapter->EnumOutputs(0, &adapterOutput)))
        throw _ERROR_EXCEPTION(L"JBL::JBCORDraw::JBCORDraw: failed to call IDXGIAdapter::EnumOutputs.");
    _LOG_S(L"JBL::JBCORDraw::JBCORDraw: succeeded to call IDXGIAdapter::EnumOutputs.");

    // 해당 포맷에 준하는 디스플레이 개수를 구함(모니터)
    _UINT numModes;
    if (FAILED(adapterOutput->GetDisplayModeList(
        JBL_DXGI_FORMAT_R8G8B8A8,
        DXGI_ENUM_MODES_INTERLACED,
        &numModes,
        nullptr
        )))
        throw _ERROR_EXCEPTION(L"JBL::JBCORDraw::JBCORDraw: failed to call IDXGIOutput::GetDisplayModeList(get).");
    _LOG_S(L"JBL::JBCORDraw::JBCORDraw: succeeded to call IDXGIOutput::GetDisplayModeList(get).");

    // 디스플레이 리스트 초기화
    auto displayModeList = _ALLOC<DXGI_MODE_DESC>(numModes);
    if (!displayModeList)throw _ERROR_EXCEPTION(L"JBL::JBLCORDraw::JBCORDraw: failed to allocate memory on displayModeList.");

    // 디스플레이 리스트 채움
    if (FAILED(adapterOutput->GetDisplayModeList(
        JBL_DXGI_FORMAT_R8G8B8A8,
        DXGI_ENUM_MODES_INTERLACED,
        &numModes,
        displayModeList
        )))
        throw _ERROR_EXCEPTION(L"JBL::JBCORDraw::JBCORDraw: failed to call IDXGIOutput::GetDisplayModeList(fill).");
    _LOG_S(L"JBL::JBCORDraw::JBCORDraw: succeeded to call IDXGIOutput::GetDisplayModeList(fill).");

    // 해상도에 맞는 화면 갱신 비를 구함
    auto numerator = decltype(displayModeList->RefreshRate.Numerator){0};
    auto denominator = decltype(displayModeList->RefreshRate.Denominator){0};
    {
        auto modeIterator = displayModeList;
        auto i = decltype(numModes){0};
        while(++i<=numModes){
            if (
                modeIterator->Width == (decltype(modeIterator->Width))glb_workSpace.x &&
                modeIterator->Height == (decltype(modeIterator->Height))glb_workSpace.y
            ){
                numerator = modeIterator->RefreshRate.Numerator;
                denominator = modeIterator->RefreshRate.Denominator;
            }
            ++modeIterator;
        }
    }

    // 어댑터 DESC를 구함
    DXGI_ADAPTER_DESC adapterDesc;
    ZeroMemory(&adapterDesc, sizeof adapterDesc);
    if (FAILED(adapter->GetDesc(&adapterDesc)))
        throw _ERROR_EXCEPTION(L"JBL::JBCORDraw::JBCORDraw: failed to call IDXGIAdapter::GetDesc.");
    _LOG_S(L"JBL::JBCORDraw::JBCORDraw: succeeded to call IDXGIAdapter::GetDesc.");

    // 비디오 메모리 명시
    ins_vRamMemory = adapterDesc.DedicatedVideoMemory;

    // 비디오 카드 이름 명시
    {
        auto len = wcslen(adapterDesc.Description);
        ins_vCardName = _ALLOC<wchar_t>(len + 1);
        if (!ins_vCardName)throw _ERROR_EXCEPTION(L"JBL::JBLCORDraw::JBCORDraw: failed to allocate memory on ins_vCardName.");

        if(wcscpy_s(ins_vCardName, len + 1, adapterDesc.Description))
            throw _ERROR_EXCEPTION(L"JBL::JBLCORDraw::JBCORDraw: failed to call wcscpy_s on ins_vCardName.");
    }

    _FREE(displayModeList);
    _RELEASE(adapterOutput);
    _RELEASE(adapter);
    _RELEASE(factory);


    // 스왑 체인 구성
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof swapChainDesc);
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = (decltype(swapChainDesc.BufferDesc.Width))glb_workSpace.x;
    swapChainDesc.BufferDesc.Height = (decltype(swapChainDesc.BufferDesc.Height))glb_workSpace.y;
    swapChainDesc.BufferDesc.Format = JBL_DXGI_FORMAT_R8G8B8A8;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = glb_state[JBL_STATE_VSYNC] ? numerator : 0;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = glb_state[JBL_STATE_VSYNC] ? denominator : 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = ins_windowInst->getHWND();
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = !glb_state[JBL_STATE_FULLSCREEN];
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Flags = 0;

    // 스왑 체인 및 장치 생성
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
    if (FAILED(D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        &featureLevel, 1,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &ins_swapChain,
        &ins_device,
        nullptr,
        &ins_deviceContext
        )))
        throw _ERROR_EXCEPTION(L"JBL::JBCORDraw::JBCORDraw: failed to call D3D11CreateDeviceAndSwapChain.");
    _LOG_S(L"JBL::JBCORDraw::JBCORDraw: succeeded to call D3D11CreateDeviceAndSwapChain.");
};
JBCORDraw::~JBCORDraw(){
    if (ins_swapChain)ins_swapChain->SetFullscreenState(FALSE, nullptr);

    _RELEASE(ins_deviceContext);
    _RELEASE(ins_device);
    _RELEASE(ins_swapChain);

    _FREE(ins_vCardName);
}

LRESULT JBCORDraw::ins_curProc(HWND hWnd, _UINT msg, WPARAM wParam, LPARAM lParam){
    return ins_nextProc(hWnd, msg, wParam, lParam);
}