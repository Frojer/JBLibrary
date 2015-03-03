#include"JBBASWndProc.h"

using namespace JBL;

_FORWARD_LIST<JBBASWndProc*> JBBASWndProc::ins_classTable;
_FORWARD_LIST<JBBASWndProc*>::const_iterator JBBASWndProc::ins_beginItr = ins_classTable.cend();
_FORWARD_LIST<JBBASWndProc*>::const_iterator JBBASWndProc::ins_beforeEndItr = ins_classTable.cend();

JBBASWndProc::JBBASWndProc(){
    ins_classTable.emplace_front(this);

    ins_curItr = ins_classTable.cbegin();
    ins_beginItr = ins_curItr;
    if (ins_beforeEndItr == ins_classTable.cend())ins_beforeEndItr = ins_curItr;
}
JBBASWndProc::~JBBASWndProc(){
    for (auto i = ins_classTable.before_begin(), e = ins_classTable.end(); i != e; ++i){
        if (i._Ptr->_Next->_Myval == this){
            ins_classTable.erase_after(i);
            break;
        }
    }
}