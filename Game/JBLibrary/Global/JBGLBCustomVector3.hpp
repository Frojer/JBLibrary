#pragma once

#include<cmath>

#include"JBGlobalMacro.hpp"
#include"JBGLBCustomFloat.hpp"

namespace JBL{
    namespace MATH{
        /// @brief 확장된 벡터 클래스
        class customVector3{
        public:
            _FLOAT x;
            _FLOAT y;
            _FLOAT z;
        public:
            customVector3() : x(), y(), z(){}
            customVector3(const _FLOAT _x, const _FLOAT _y, const _FLOAT _z) : x(_x), y(_y), z(_z){}
            customVector3(const customVector3& v) : x(v.x), y(v.y), z(v.z){}
        public:
            inline customVector3& operator=(const customVector3& v){ x = v.x; y = v.y; z = v.z; return *this; }
        public:
            inline bool operator!()const{ return !x && !y && !z; }
            inline bool operator==(const customVector3& v)const{ return x == v.x && y == v.y && z == v.z; }
            inline bool operator!=(const customVector3& v)const{ return x != v.x && y != v.y && z != v.z; }
        public:
            inline customVector3& operator*=(const _FLOAT& f){ x *= f; y *= f; z *= f; return *this; }
            inline customVector3& operator/=(const _FLOAT& f){ _FLOAT m = 1.f / f; x *= m; y *= m; z *= m; return *this; }
            inline customVector3& operator+=(const customVector3& v){ x += v.x; y += v.y; z += v.z; return *this; }
            inline customVector3& operator-=(const customVector3& v){ x -= v.x; y -= v.y; z -= v.z; return *this; }
        public:
            inline customVector3 operator*(const _FLOAT& f)const{ return customVector3(*this) *= f; }
            inline customVector3 operator/(const _FLOAT& f)const{ return customVector3(*this) /= f; }
            inline customVector3 operator+(const customVector3& v)const{ return customVector3(*this) += v; }
            inline customVector3 operator-(const customVector3& v)const{ return customVector3(*this) -= v; }
        public:
            /// @brief 벡터의 길이(크기)를 구합니다.
            /// @return 연산 결과
            inline _FLOAT length()const{ return _FLOAT(sqrt((x * x) + (y * y) + (z * z))); }

            /// @brief 대상 벡터와의 내적을 구합니다.
            /// @param v 연산 대상
            /// @return 연산 결과
            inline _FLOAT dot(const customVector3& v)const{ return _FLOAT((x * v.x) + (y * v.y) + (z * v.z)); }
        public:
            /// @brief 현재 벡터를 정규화 시킵니다.
            /// @return 변환 결과
            inline customVector3& normalizeSelf(){ return !(*this) ? (*this) *= 0.f : (*this) /= length(); }

            /// @brief 두 벡터의 외적 연산 결과를 저장합니다.
            /// @param lhs 좌측 연산 대상
            /// @param rhs 우측 연산 대상
            /// @return 연산 결과
            inline customVector3& crossSelf(const customVector3& lhs, const customVector3& rhs){
                x = (lhs.y * rhs.z) - (lhs.z * rhs.y);
                y = (lhs.z * rhs.x) - (lhs.x * rhs.z);
                z = (lhs.x * rhs.y) - (lhs.y * rhs.x);
                return *this;
            }
            /// @brief 대상 벡터와의 외적 연산 결과를 저장합니다.
            /// @param v 연산 대상
            /// @return 연산 결과
            inline customVector3& crossSelf(const customVector3& v){ return crossSelf(customVector3(*this), v); }
        public:
            /// @brief 단위 벡터를 구합니다.
            /// @return 연산 결과
            inline customVector3 normalize()const{ return customVector3(*this).normalizeSelf(); }

            /// @brief 대상 벡터와의 외적을 구합니다.
            /// @param v 연산 대상
            /// @return 연산 결과
            inline customVector3 cross(const customVector3& v)const{ return customVector3(*this).crossSelf(v); }
        };
    };
};