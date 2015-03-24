#pragma once

#include"../JBDirectXHeader.hpp"
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
            __forceinline customVector3& operator=(const customVector3& v){ x = v.x; y = v.y; z = v.z; return *this; }
        public:
            __forceinline bool operator!()const{ return !x && !y && !z; }
            __forceinline bool operator==(const customVector3& v)const{ return x == v.x && y == v.y && z == v.z; }
            __forceinline bool operator!=(const customVector3& v)const{ return x != v.x && y != v.y && z != v.z; }
        public:
            __forceinline customVector3& operator*=(const _FLOAT& f){ x *= f; y *= f; z *= f; return *this; }
            __forceinline customVector3& operator/=(const _FLOAT& f){ _FLOAT m = 1.f / f; x *= m; y *= m; z *= m; return *this; }
            __forceinline customVector3& operator+=(const customVector3& v){ x += v.x; y += v.y; z += v.z; return *this; }
            __forceinline customVector3& operator-=(const customVector3& v){ x -= v.x; y -= v.y; z -= v.z; return *this; }
        public:
            __forceinline customVector3 operator*(const _FLOAT& f)const{ return customVector3(*this) *= f; }
            __forceinline customVector3 operator/(const _FLOAT& f)const{ return customVector3(*this) /= f; }
            __forceinline customVector3 operator+(const customVector3& v)const{ return customVector3(*this) += v; }
            __forceinline customVector3 operator-(const customVector3& v)const{ return customVector3(*this) -= v; }
        public:
            /// @brief 벡터의 길이(크기)를 구합니다.
            /// @return 연산 결과
            __forceinline _FLOAT length()const{ return _FLOAT(D3DXVec3Length((const D3DXVECTOR3*)this)); }

            /// @brief 대상 벡터와의 내적을 구합니다.
            /// @param v 연산 대상
            /// @return 연산 결과
            __forceinline _FLOAT dot(const customVector3& v)const{ return _FLOAT(D3DXVec3Dot((const D3DXVECTOR3*)this, (const D3DXVECTOR3*)&v)); }
        public:
            /// @brief 현재 벡터를 정규화 시킵니다.
            /// @return 변환 결과
            __forceinline customVector3& normalizeSelf(){
                D3DXVec3Normalize((D3DXVECTOR3*)this, (const D3DXVECTOR3*)this);
                return *this;
            }

            /// @brief 두 벡터의 외적 연산 결과를 저장합니다.
            /// @param lhs 좌측 연산 대상
            /// @param rhs 우측 연산 대상
            /// @return 연산 결과
            __forceinline customVector3& crossSelf(const customVector3& lhs, const customVector3& rhs){
                D3DXVec3Cross((D3DXVECTOR3*)this, (const D3DXVECTOR3*)&lhs, (const D3DXVECTOR3*)&rhs);
                return *this;
            }
            /// @brief 대상 벡터와의 외적 연산 결과를 저장합니다.
            /// @param v 연산 대상
            /// @return 연산 결과
            __forceinline customVector3& crossSelf(const customVector3& v){ return crossSelf(customVector3(*this), v); }
        public:
            /// @brief 단위 벡터를 구합니다.
            /// @return 연산 결과
            __forceinline customVector3 normalize()const{ return customVector3(*this).normalizeSelf(); }

            /// @brief 대상 벡터와의 외적을 구합니다.
            /// @param v 연산 대상
            /// @return 연산 결과
            __forceinline customVector3 cross(const customVector3& v)const{ return customVector3(*this).crossSelf(v); }
        };
    };
};