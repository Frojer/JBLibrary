#include"JBBASComponent.h"
#include"JBBASObject.h"
#include"../Global/JBGlobalFunc.h"

using namespace JBL;
using namespace JBL::SYSTEM;

JBBASComponent::JBBASComponent(){}
JBBASComponent::~JBBASComponent(){
    ins_owner = nullptr;
}

bool JBBASComponent::init(){ return true; }
bool JBBASComponent::update(){ return true; }