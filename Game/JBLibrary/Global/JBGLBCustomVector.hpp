#pragma once

#include<cmath>

#include"JBGlobalMacro.hpp"
#include"JBGLBCustomFloat.hpp"

namespace JBL{
    namespace MATH{
        /// @brief 확장된 벡터 클래스
        class customVector{
        public:
            _FLOAT x;
            _FLOAT y;
            _FLOAT z;
        public:
            customVector() :x(), y(), z(){}
            customVector(const _FLOAT _x, const _FLOAT _y, const _FLOAT _z) :x(_x), y(_y), z(_z){}
            customVector(const customVector& v) :x(v.x), y(v.y), z(v.z){}
        public:
            inline bool operator==(const customVector& v)const{ return x == v.x && y == v.y && z == v.z; }
            inline bool operator!=(const customVector& v)const{ return x != v.x && y != v.y && z != v.z; }
        public:
            inline customVector& operator+=(const customVector& v){ x += v.x; y += v.y; z += v.z; return *this; }
            inline customVector& operator-=(const customVector& v){ x -= v.x; y -= v.y; z -= v.z; return *this; }
            inline customVector& operator*=(const _FLOAT& f){ x *= f; y *= f; z *= f; return *this; }
        public:
            inline customVector operator+(const customVector& v)const{ return customVector(*this) += v; }
            inline customVector operator-(const customVector& v)const{ return customVector(*this) -= v; }
            inline customVector operator*(const _FLOAT& f)const{ return customVector(*this) *= f; }
        public:
            /// @brief 벡터의 길이(크기)를 구합니다.
            /// @return 실수 값
            inline _FLOAT length()const{ return sqrt((x ^ 2) + (y ^ 2) + (z ^ 2)); }

            /// @brief 단위 벡터를 구합니다.
            /// @return 벡터 값
            inline customVector normalize()const{
                _FLOAT len(length());
                return !len ? customVector(0.f, 0.f, 0.f) : customVector(*this) *= 1.f / len;
            }
        };
    };
};