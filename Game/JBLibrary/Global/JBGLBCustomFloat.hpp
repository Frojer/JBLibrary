#pragma once

#include<cmath>
#include<cfloat>

#include"JBGlobalMacro.hpp"

namespace JBL{
    namespace MATH{
        /// @brief 확장된 float클래스
        class customFloat{
        private:
            union innerFloat{
                float f; ///< 실제 값
                struct{
                    _DWORD mantissa : 23; ///< 가수부
                    _DWORD exponent : 8; ///< 지수부
                    _DWORD sign : 1; ///< 부호
                } parts;
                _DWORD opr;

                innerFloat(const float& _f){ f = _f; }
                innerFloat(const _DWORD& _opr){ opr = _opr; }
            };
        private:
            innerFloat val;
        private:
            /// @brief (this - f)의 절대값이 FLT_EPSILON보다 작은지 비교합니다.
            /// @param f 비교 대상
            /// @return 판별 여부
            inline bool ins_isEqual(const float& f)const{
                innerFloat c(f - val.f); c.parts.sign = 0;
                return c.f < FLT_EPSILON;
            }
        public:
            customFloat() : val((_DWORD)0L){}
            customFloat(const customFloat& f) : val(f.val.f){}
            customFloat(const float& f) : val(f){}
        public:
            inline customFloat& operator=(const customFloat& f){ val.f = f.val.f; return *this; }
            inline customFloat& operator=(const float& f){ val.f = f; return *this; }
        public:
            inline operator float()const{ return val.f; };
            inline operator float&(){ return val.f; };
        public:
            inline bool operator!()const{ return !val.opr; }
            inline bool operator==(const customFloat& f)const{ return ins_isEqual(f.val.f); }
            inline bool operator==(const float& f)const{ return ins_isEqual(f); }
            inline bool operator!=(const customFloat& f)const{ return !ins_isEqual(f.val.f); }
            inline bool operator!=(const float& f)const{ return !ins_isEqual(f); }
            inline bool operator>(const customFloat& f)const{ return val.f > f.val.f; }
            inline bool operator>(const float& f)const{ return val.f > f; }
            inline bool operator<(const customFloat& f)const{ return val.f < f.val.f; }
            inline bool operator<(const float& f)const{ return val.f < f; }
            inline bool operator>=(const customFloat& f)const{ return (*this > f) || (*this == f); }
            inline bool operator>=(const float& f)const{ return (*this > f) || (*this == f); }
            inline bool operator<=(const customFloat& f)const{ return (*this < f) || (*this == f); }
            inline bool operator<=(const float& f)const{ return (*this < f) || (*this == f); }
        public:
            /// @brief this에 this의 f제곱을 대입합니다.
            /// @param f 승수
            /// @return 대입 결과
            inline customFloat& operator^=(const customFloat& f){ val.f = pow(val.f, f.val.f); return *this; }
            /// @brief this에 this의 f제곱을 대입합니다.
            /// @param f 승수
            /// @return 대입 결과
            inline customFloat& operator^=(const float& f){ val.f = pow(val.f, f); return *this; }
            /// @brief this에 this의 f제곱을 대입합니다.
            /// @param f 승수
            /// @return 대입 결과
            inline customFloat& operator^=(const _INT& f){ val.f = pow(val.f, f); return *this; }

            inline customFloat& operator*=(const customFloat& f){ val.f *= f.val.f; return *this; }
            inline customFloat& operator*=(const float& f){ val.f *= f; return *this; }
            inline customFloat& operator/=(const customFloat& f){ val.f /= f.val.f; return *this; }
            inline customFloat& operator/=(const float& f){ val.f /= f; return *this; }
            inline customFloat& operator+=(const customFloat& f){ val.f += f.val.f; return *this; }
            inline customFloat& operator+=(const float& f){ val.f += f; return *this; }
            inline customFloat& operator-=(const customFloat& f){ val.f -= f.val.f; return *this; }
            inline customFloat& operator-=(const float& f){ val.f -= f; return *this; }
        public:
            /// @brief this의 f제곱을 반환합니다.
            /// @param f 승수
            /// @return 연산 결과
            inline customFloat operator^(const customFloat& f)const{ return customFloat(*this) ^= f; }
            /// @brief this의 f제곱을 반환합니다.
            /// @param f 승수
            /// @return 연산 결과
            inline customFloat operator^(const float& f)const{ return customFloat(*this) ^= f; }
            /// @brief this의 f제곱을 반환합니다.
            /// @param f 승수
            /// @return 연산 결과
            inline customFloat operator^(const _INT& f)const{ return customFloat(*this) ^= f; }

            inline customFloat operator*(const customFloat& f)const{ return customFloat(*this) *= f; }
            inline customFloat operator*(const float& f)const{ return customFloat(*this) *= f; }
            inline customFloat operator/(const customFloat& f)const{ return customFloat(*this) /= f; }
            inline customFloat operator/(const float& f)const{ return customFloat(*this) /= f; }
            inline customFloat operator+(const customFloat& f)const{ return customFloat(*this) += f; }
            inline customFloat operator+(const float& f)const{ return customFloat(*this) += f; }
            inline customFloat operator-(const customFloat& f)const{ return customFloat(*this) -= f; }
            inline customFloat operator-(const float& f)const{ return customFloat(*this) -= f; }
        public:
            /// @brief 절대값을 반환합니다.
            /// @return 절대값
            inline customFloat getAbs()const{ return customFloat(innerFloat(val.opr << 1 >> 1).f); }
        };
    };
};