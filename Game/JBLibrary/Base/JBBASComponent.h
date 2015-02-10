#pragma once

#include"../Global/JBGlobalFunc.h"

namespace JBL{
    class JBBASObject;
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
        inline void setOwner(JBBASObject* owner){ ins_owner = owner; }
        inline JBBASObject* getOwner()const{ return ins_owner; }
    public:
        virtual _DWORD getComponentID()const = 0;
    };
};