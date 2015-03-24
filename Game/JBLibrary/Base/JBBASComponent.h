#pragma once

#include"../Global/JBGlobalFunc.h"

namespace JBL{
    class JBBASObject;

    /// @brief 오브젝트의 컴포넌트입니다.
    /// @details 각 컴포넌트는 4bytes의 식별 키를 가지는 해쉬 맵으로 관리됩니다.
    class JBBASComponent{
    private:
        JBBASObject* ins_owner;
    protected:
        JBBASComponent();
    public:
        virtual ~JBBASComponent();
    public:
        virtual bool init();
        virtual bool update();
    public:
        __forceinline void setOwner(JBBASObject* owner){ ins_owner = owner; }
        __forceinline JBBASObject* getOwner()const{ return ins_owner; }
    public:
        virtual _DWORD getComponentID()const = 0;
    };
};