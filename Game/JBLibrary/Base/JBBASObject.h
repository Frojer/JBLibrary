#pragma once

#include<boost/unordered_map.hpp>
#include"../Global/JBGlobalFunc.h"

namespace JBL{
    class JBBASComponent;
    class JBBASObject{
    private:
        typedef _UNORDERED_MAP<_DWORD, JBBASComponent*, HASH::hashedKeyHasher<_DWORD>> ComponentMap;
    private:
        _SIZE_T ins_id;
        ComponentMap ins_componentTable;
    protected:
        JBBASObject(const _SIZE_T id);
    public:
        virtual ~JBBASObject();
    public:
        bool init();
        bool update();
    protected:
        virtual bool ins_init();
        virtual bool ins_update();
    public:
        void clearComponentTable();
        bool addComponent(JBBASComponent* tar);
        JBBASComponent* getComponent(const _DWORD id);
        const JBBASComponent* getComponent(const _DWORD id)const;
    public:
        inline _SIZE_T getID()const{ return ins_id; }
    };
};