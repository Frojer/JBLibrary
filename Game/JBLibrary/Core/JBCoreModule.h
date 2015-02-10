#pragma once

#include"../Global/JBGlobalFunc.h"

#ifdef _DEBUG
#include"JBCORLogWindow.h"
#endif
#include"JBCORWindow.h"
#include"JBCORDraw.h"
#include"JBCORRender.h"

namespace JBL{
#ifdef _DEBUG
    extern _UNIQUE_PTR<JBCORLogWindow> glb_instLog; ///< 로그 인스턴스
#endif
    extern _UNIQUE_PTR<JBCORWindow> glb_instWindow; ///< 윈도우 인스턴스
    extern _UNIQUE_PTR<JBCORDraw> glb_instDraw; ///< 그리기(DX) 인스턴스
    extern _UNIQUE_PTR<JBCORRender> glb_instRender; ///< 렌더러 인스턴스
};