#pragma once

#include"../Global/JBGlobalFunc.h"
#include"../Base/JBBASComponent.h"

namespace JBL{
    class JBCOMRender : public JBBASComponent{
    public:
        JBCOMRender();
        ~JBCOMRender();
    public:
        bool init();
        bool update();
    public:
        __forceinline _DWORD getComponentID()const{ return _HASH_X65599("JBCOMRender"); }
    };
};