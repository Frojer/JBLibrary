#pragma once

#include"JBGLBCustomFloat.hpp"

namespace JBL{
    namespace MATH{
        /// @brief 두 수 사이의 최대 값을 구합니다.
        /// @param a 비교 대상
        /// @param b 비교 대상
        /// @return 더 큰 값을 반환합니다.
        template<typename T> extern inline T glb_max(const T a, const T b){ return a > b ? a : b; }
        /// @brief 셋 이상의 수 사이의 최대 값을 구합니다.
        /// @param a 비교 대상
        /// @param b 비교 대상
        /// @param others 나머지 비교 대상
        /// @return 제일 큰 값을 반환합니다.
        template<typename T, typename... TS> extern T glb_max(const T a, const T b, const TS... others){
            return glb_max<T>(glb_max<T>(a, b), others...);
        }

        /// @brief 두 수 사이의 최소 값을 구합니다.
        /// @param a 비교 대상
        /// @param b 비교 대상
        /// @return 더 작은 값을 반환합니다.
        template<typename T> extern inline T glb_min(const T a, const T b){ return a < b ? a : b; }
        /// @brief 셋 이상의 수 사이의 최소 값을 구합니다.
        /// @param a 비교 대상
        /// @param b 비교 대상
        /// @param others 나머지 비교 대상
        /// @return 제일 작은 값을 반환합니다.
        template<typename T, typename... TS> extern T glb_min(const T a, const T b, const TS... others){
            return glb_min<T>(glb_min<T>(a, b), others...);
        }
    };
};