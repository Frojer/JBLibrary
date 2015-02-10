#include"JBBASObject.h"
#include"JBBASComponent.h"
#include"../Global/JBGlobalFunc.h"
#include"../Core/JBCoreModule.h"

#define ERROR_BUFFER_SIZE 128

using namespace JBL;
using namespace JBL::SYSTEM;

JBBASObject::JBBASObject(const _SIZE_T id){
    ins_id = id;
}
JBBASObject::~JBBASObject(){
    clearComponentTable();
}

bool JBBASObject::init(){
    for (auto i : ins_componentTable){
        if (!i.second->init()){
#ifdef _WIN64
            _LOG_F(STRING::glb_strFormat(
                ERROR_BUFFER_SIZE,
                L"JBL::JBBASObject(%llu): failed to call JBL::JBBASComponent(%u)::init.",
                ins_id, i.first
                ));
#else
            _LOG_F(STRING::glb_strFormat(
                ERROR_BUFFER_SIZE,
                L"JBL::JBBASObject(%u): failed to call JBL::JBBASComponent(%u)::init.",
                ins_id, i.first
                ));
#endif
            return false;
        }
    }

    if (!ins_init())return false;

    return true;
}
bool JBBASObject::update(){
    for (auto i : ins_componentTable){
        if (!i.second->update()){
#ifdef _WIN64
            _LOG_F(STRING::glb_strFormat(
                ERROR_BUFFER_SIZE,
                L"JBL::JBBASObject(%llu): failed to call JBL::JBBASComponent(%u)::update.",
                ins_id, i.first
                ));
#else
            _LOG_F(STRING::glb_strFormat(
                ERROR_BUFFER_SIZE,
                L"JBL::JBBASObject(%u): failed to call JBL::JBBASComponent(%u)::update.",
                ins_id, i.first
                ));
#endif
            return false;
        }
    }

    if (!ins_update())return false;

    return true;
}

bool JBBASObject::ins_init(){ return true; }
bool JBBASObject::ins_update(){ return true; }

void JBBASObject::clearComponentTable(){
    if (ins_componentTable.empty())return;

    ComponentMap::iterator i = ins_componentTable.begin();
    while (i != ins_componentTable.end()){
        _DELETE(i->second);
        i = ins_componentTable.erase(i);
    }
}
bool JBBASObject::addComponent(JBBASComponent* tar){
    if (!tar)return false;

    auto id = tar->getComponentID();
    if (ins_componentTable.find(id) == ins_componentTable.cend())return false;

    tar->setOwner(this);
    ins_componentTable.emplace(id, tar);
    return true;
}
JBBASComponent* JBBASObject::getComponent(const _DWORD id){
    ComponentMap::iterator f = ins_componentTable.find(id);
    if (f == ins_componentTable.end())return nullptr;
    return f->second;
}
const JBBASComponent* JBBASObject::getComponent(const _DWORD id)const{
    ComponentMap::const_iterator f = ins_componentTable.find(id);
    if (f == ins_componentTable.cend())return nullptr;
    return f->second;
}