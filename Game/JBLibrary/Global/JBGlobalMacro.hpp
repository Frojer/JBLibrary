#pragma once

// output
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __LOC__ __FILE__ "("__STR1__(__LINE__)") : Warning Msg: "
//

// for debug
#ifdef _DEBUG
#define _SETFOCUS_LOG { if(JBL::glb_instLog)JBL::SYSTEM::glb_setFocus(JBL::glb_instLog->getHWND()); if(JBL::glb_instWindow)JBL::SYSTEM::glb_setFocus(JBL::glb_instWindow->getHWND()); }
#define _LOG(d) { if(JBL::glb_instLog)JBL::glb_instLog->addLog(d, 0); if(JBL::glb_instWindow)JBL::SYSTEM::glb_setFocus(JBL::glb_instWindow->getHWND()); }
#define _LOG_S(d) { if(JBL::glb_instLog)JBL::glb_instLog->addLog(d, 1); if(JBL::glb_instWindow)JBL::SYSTEM::glb_setFocus(JBL::glb_instWindow->getHWND()); }
#define _LOG_W(d) { if(JBL::glb_instLog)JBL::glb_instLog->addLog(d, 2); if(JBL::glb_instWindow)JBL::SYSTEM::glb_setFocus(JBL::glb_instWindow->getHWND()); }
#define _LOG_F(d) { if(JBL::glb_instLog)JBL::glb_instLog->addLog(d, 3); if(JBL::glb_instWindow)JBL::SYSTEM::glb_setFocus(JBL::glb_instWindow->getHWND()); }
#define _LOG_I(d) { if(JBL::glb_instLog)JBL::glb_instLog->addLog(d, 4); if(JBL::glb_instWindow)JBL::SYSTEM::glb_setFocus(JBL::glb_instWindow->getHWND()); }

#include<cassert>
#define _DASSERT(d) assert(d)
#define _SASSERT(d, msg) static_assert(d, msg)
#else
#define _SETFOCUS_LOG
#define _LOG
#define _LOG_S
#define _LOG_W
#define _LOG_F
#define _LOG_I

#define _DASSERT
#define _SASSERT
#endif
//

// basic
#ifdef _WIN64
#define _INT __w64 int
#define _UINT __w64 unsigned int
#define _SIZE_T unsigned __int64
#else
#define _INT int
#define _UINT unsigned int
#define _SIZE_T unsigned int
#endif
#define _USHORT unsigned short
#define _ULONG unsigned long
#define _BYTE unsigned char
#define _WORD unsigned short
#define _DWORD unsigned long
#define _QWORD unsigned long long

#define _MOVE boost::move
#define _FORWARD boost::forward

#define _FUNC boost::function

#define _PAIR std::pair
#define _MAKE_PAIR std::make_pair

#define _UNIQUE_PTR boost::movelib::unique_ptr
template<typename T> using _UNIQUE_PTR_M = _UNIQUE_PTR < T, _FUNC<void(T*)> >;
#define _MAKE_UNIQUE boost::movelib::make_unique

#define _SHARED_PTR boost::shared_ptr
#define _MAKE_SHARED boost::make_shared

#define _FORWARD_LIST std::forward_list
#define _LIST std::list
#define _VECTOR std::vector
#define _MAP std::map
#define _UNORDERED_MAP boost::unordered_map
//

// memory
#define _ERROR_EXCEPTION JBL::MEMORY::__ERROR_EXCEPTION

#define _ALLOC JBL::MEMORY::__ALLOC
#define _NEW JBL::MEMORY::__NEW
#define _NEW_ALIGNED_CUSTOM JBL::MEMORY::__NEW_ALIGNED_CUSTOM
#define _NEW_ALIGNED16 JBL::MEMORY::__NEW_ALIGNED16

#define _FREE(d) { if (d){ free(d); d = nullptr; } }
#define _DELETE(d) { if (d){ delete d; d = nullptr; } }
#define _DELETE_ARRAY(d) { if (d){ delete[] d; d = nullptr; } }
#define _DELETE_ALIGNED(d) { if (d){ JBL::MEMORY::__DELETE_ALIGNED(d); d = nullptr; } }
#define _RELEASE(d) { if (d){ d->Release(); d = nullptr; } }
//

// hash
#define _HASH_X65599_M JBL::HASH::glb_x65599Hash
#define _HASH_X65599(s) _HASH_X65599_M(s, strlen(s))

#define _HASH_BOOSTUMAP_M JBL::HASH::glb_boostHash
#define _HASH_BOOSTUMAP(s) _HASH_BOOSTUMAP_M(s, strlen(s))
//

// string
#define _STRING_NPOS ((_SIZE_T)(-1))
#define _STRING JBL::STRING::customString<char>
#define _WSTRING JBL::STRING::customString<wchar_t>
//

// math
#define _FLOAT JBL::MATH::__FLOAT

#define _MAX JBL::MATH::glb_max
#define _MIN JBL::MATH::glb_min
//

// file_library
#define _PATH2HASH_M _HASH_BOOSTUMAP_M
#define _PATH2HASH _HASH_BOOSTUMAP
//