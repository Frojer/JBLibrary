#pragma once

#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : Warning Msg: "

#include"../JBLinkLIB.hpp"

#include<windows.h>

#include<boost/function.hpp>
#include<boost/bind.hpp>

#include<boost/move/unique_ptr.hpp>
#include<boost/move/make_unique.hpp>

#include<boost/shared_ptr.hpp>
#include<boost/make_shared.hpp>

#include"JBGlobalMacro.hpp"
#include"../JBDefault.hpp"
#include"JBGLBMemory.h"
#include"JBGLBSystem.h"
#include"JBGLBIO.h"
#include"JBGLBMath.h"
#include"JBGLBColor.h"
#include"JBGLBHash.hpp"
#include"JBGLBString.h"
#include"JBGLBFileLibrary.h"

namespace JBL{};