#include"JBCoreModule.h"

using namespace JBL;

#ifdef _DEBUG
_UNIQUE_PTR<JBCORLogWindow> JBL::glb_instLog(nullptr);
#endif
_UNIQUE_PTR<JBCORWindow> JBL::glb_instWindow(nullptr);
_UNIQUE_PTR<JBCORDraw> JBL::glb_instDraw(nullptr);
_UNIQUE_PTR<JBCORRender> JBL::glb_instRender(nullptr);
