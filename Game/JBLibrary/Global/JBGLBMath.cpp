#include"JBGlobalFunc.h"

using namespace JBL;
using namespace SYSTEM;

MATH::__FLOAT::__FLOAT() : val((_DWORD)0L){}
MATH::__FLOAT::__FLOAT(const __FLOAT& f) : val(f.val.f){}
MATH::__FLOAT::__FLOAT(const float& f) : val(f){}