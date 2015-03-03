#pragma once

#include<boost/functional/hash.hpp>

#include"JBGlobalMacro.hpp"

namespace JBL{
    namespace HASH{
        /// @brief 이미 해싱된 키를 사용하기 위한 unordered_map의 키 해싱 알고리즘입니다.
        template<typename T> struct hashedKeyHasher{ _SIZE_T operator()(const T& k)const{ return _SIZE_T(k); }; };

        /// @brief X65599 해싱 알고리즘을 통한 4바이트 해쉬 값을 생성합니다.
        /// @param s 대상 문자열
        /// @param len 문자열 길이
        /// @return 해쉬 값
        extern inline _DWORD glb_x65599Hash(const char* s, const _SIZE_T len){
            _DWORD h = 0;

            for (auto i = decltype(len){0}; i < len; ++i){
                h *= 65599;
                h += ((*s == '\\') ? ('/') : ((*s >= 'a' && *s <= 'z') ? (*s - 32) : (*s)));
                ++s;
            }

            h ^= h >> 16;

            return h;
        }

        /// @brief boost::unordered_map의 키 해싱 알고리즘을 통한 8바이트 해쉬 값을 생성합니다.
        /// @param s 원본 문자열
        /// @param len 원본 문자열의 길이
        /// @return 해쉬 값
        extern inline _QWORD glb_boostHash(const char* s, const _SIZE_T len){
            _QWORD h = 0;
            _DWORD h2 = 0;

            for (auto i = decltype(len){0}; i < len; ++i){
                h2 ^=
                    ((*s == '\\') ? ('/') : ((*s >= 'a' && *s <= 'z') ? (*s - 32) : (*s))) +
                    0x9e3779b9 + (h2 << 6) + (h2 >> 2)
                    ;
                ++s;
            }

            h ^= ((h2 * 0xc6a4a7935bd1e995) ^ ((h2 * 0xc6a4a7935bd1e995) >> 47)) * 0xc6a4a7935bd1e995;
            h *= 0xc6a4a7935bd1e995;

            return h;
        }
    };
};