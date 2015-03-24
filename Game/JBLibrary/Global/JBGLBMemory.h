#pragma once

#include<cstdlib>

#include"JBGlobalMacro.hpp"
#include"JBGLBSystem.h"

namespace JBL{
    using namespace SYSTEM;
    namespace MEMORY{
        /// @brief 예외 처리를 위한 클래스
        struct __ERROR_EXCEPTION{
            inline __ERROR_EXCEPTION(){}
            /// @param s 에러 메세지(멀티바이트)
            inline __ERROR_EXCEPTION(const char* s){ glb_infoMsg(IF_ERROR, s); }
            /// @param s 에러 메세지(와이드바이트)
            inline __ERROR_EXCEPTION(const wchar_t* s){ glb_infoMsg(IF_ERROR, s); }
        };

        /// @brief 지정된 크기만큼 동적 할당을 진행합니다. 생성된 공간은 0으로 초기화 됩니다.
        /// @param size 할당할 크기 / 자료형 크기
        /// @return 해당 자료형에 따른 시작 주소. 실패시 nullptr를 반환합니다.
        template<typename OBJ> extern __forceinline OBJ* __ALLOC(const _SIZE_T size){
            return (OBJ*)calloc(size, sizeof(OBJ));
        }

        /// @brief 동적 할당 후, 생성자를 호출합니다. throw로 반환된 예외 처리를 진행합니다.
        /// @param argv 생성자에 따른 인자
        /// @return 해당 자료형에 따른 객체. 실패시 nullptr를 반환합니다.
        template<typename OBJ, typename... T> extern __forceinline OBJ* __NEW(T&&... argv){
            OBJ* _new = nullptr;
            try{ _new = new OBJ(_FORWARD<T>(argv)...); }
            catch (...){
                delete _new;
                _new = nullptr;
            }
            return _new;
        }

        /// @brief 지정된 얼라이먼트로 객체를 생성합니다. throw로 반환된 예외 처리를 진행합니다.
        /// @param aliSz 얼라이먼트 크기
        /// @param argv 생성자에 따른 인자
        /// @return 해당 자료형에 따른 객체. 실패시 nullptr를 반환합니다.
        template<typename OBJ, typename... T> extern __forceinline OBJ* __NEW_ALIGNED_CUSTOM(const _SIZE_T aliSz, T&&... argv){
            OBJ* _new = (OBJ*)_aligned_malloc(sizeof(OBJ), aliSz);
            if (_new){
                try{ new (_new)OBJ(_FORWARD<T>(argv)...); }
                catch (...){
                    _aligned_free(_new);
                    _new = nullptr;
                }
            }
            return _new;
        }
        /// @brief 16bytes 얼라이먼트로 객체를 생성합니다. throw로 반환된 예외 처리를 진행합니다.
        /// @param argv 생성자에 따른 인자
        /// @return 해당 자료형에 따른 객체. 실패시 nullptr를 반환합니다.
        template<typename OBJ, typename... T> extern __forceinline OBJ* __NEW_ALIGNED16(T&&... argv){
            return __NEW_ALIGNED_CUSTOM<OBJ, T>(16u, argv...);
        }

        /// @brief 사용자 지정 얼라이먼트로 생성한 객체를 소멸합니다.
        /// @param tar 소멸할 대상
        /// @param argv 소멸자에 따른 인자
        template<typename OBJ, typename... T> extern __forceinline void __DELETE_ALIGNED(OBJ* tar, T&&... argv){
            tar->~OBJ(_FORWARD<T>(argv)...);
            _aligned_free(tar);
        }
    };
};