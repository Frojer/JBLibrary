#pragma once

#include<cmath>
#include<cfloat>

namespace JBL{
    namespace MATH{
        /// @brief 확장된 float클래스
        class __FLOAT{
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
            __FLOAT();
            __FLOAT(const __FLOAT&);
            __FLOAT(const float&);
        public:
            inline __FLOAT& operator=(const __FLOAT& f){ val.f = f.val.f; return *this; }
            inline __FLOAT& operator=(const float& f){ val.f = f; return *this; }
        public:
            inline operator float()const{ return val.f; };
            inline operator float&(){ return val.f; };
        public:
            inline bool operator==(const __FLOAT& f)const{ return ins_isEqual(f.val.f); }
            inline bool operator==(const float& f)const{ return ins_isEqual(f); }
            inline bool operator!=(const __FLOAT& f)const{ return !ins_isEqual(f.val.f); }
            inline bool operator!=(const float& f)const{ return !ins_isEqual(f); }
            inline bool operator>(const __FLOAT& f)const{ return val.f > f.val.f; }
            inline bool operator>(const float& f)const{ return val.f > f; }
            inline bool operator<(const __FLOAT& f)const{ return val.f < f.val.f; }
            inline bool operator<(const float& f)const{ return val.f < f; }
            inline bool operator>=(const __FLOAT& f)const{ return (*this > f) || (*this == f); }
            inline bool operator>=(const float& f)const{ return (*this > f) || (*this == f); }
            inline bool operator<=(const __FLOAT& f)const{ return (*this < f) || (*this == f); }
            inline bool operator<=(const float& f)const{ return (*this < f) || (*this == f); }
        public:
            inline __FLOAT& operator+=(const __FLOAT& f){ val.f += f.val.f; return *this; }
            inline __FLOAT& operator+=(const float& f){ val.f += f; return *this; }
            inline __FLOAT& operator-=(const __FLOAT& f){ val.f -= f.val.f; return *this; }
            inline __FLOAT& operator-=(const float& f){ val.f -= f; return *this; }
            inline __FLOAT& operator*=(const __FLOAT& f){ val.f *= f.val.f; return *this; }
            inline __FLOAT& operator*=(const float& f){ val.f *= f; return *this; }
            inline __FLOAT& operator/=(const __FLOAT& f){ val.f /= f.val.f; return *this; }
            inline __FLOAT& operator/=(const float& f){ val.f /= f; return *this; }

            /// @brief this에 this의 f제곱을 대입합니다.
            /// @param f 승수
            /// @return 대입 결과
            inline __FLOAT& operator^=(const __FLOAT& f){ val.f = pow(val.f, f.val.f); return *this; }
            /// @brief this에 this의 f제곱을 대입합니다.
            /// @param f 승수
            /// @return 대입 결과
            inline __FLOAT& operator^=(const float& f){ val.f = pow(val.f, f); return *this; }
            /// @brief this에 this의 f제곱을 대입합니다.
            /// @param f 승수
            /// @return 대입 결과
            inline __FLOAT& operator^=(const _INT& f){ val.f = pow(val.f, f); return *this; }
        public:
            inline __FLOAT operator+(const __FLOAT& f)const{ return __FLOAT(*this) += f; }
            inline __FLOAT operator+(const float& f)const{ return __FLOAT(*this) += f; }
            inline __FLOAT operator-(const __FLOAT& f)const{ return __FLOAT(*this) -= f; }
            inline __FLOAT operator-(const float& f)const{ return __FLOAT(*this) -= f; }
            inline __FLOAT operator*(const __FLOAT& f)const{ return __FLOAT(*this) *= f; }
            inline __FLOAT operator*(const float& f)const{ return __FLOAT(*this) *= f; }
            inline __FLOAT operator/(const __FLOAT& f)const{ return __FLOAT(*this) /= f; }
            inline __FLOAT operator/(const float& f)const{ return __FLOAT(*this) /= f; }

            /// @brief this의 f제곱을 반환합니다.
            /// @param f 승수
            /// @return 연산 결과
            inline __FLOAT operator^(const __FLOAT& f)const{ return __FLOAT(*this) ^= f; }
            /// @brief this의 f제곱을 반환합니다.
            /// @param f 승수
            /// @return 연산 결과
            inline __FLOAT operator^(const float& f)const{ return __FLOAT(*this) ^= f; }
            /// @brief this의 f제곱을 반환합니다.
            /// @param f 승수
            /// @return 연산 결과
            inline __FLOAT operator^(const _INT& f)const{ return __FLOAT(*this) ^= f; }
        public:
            /// @brief 절대값을 반환합니다.
            /// @return 절대값
            inline __FLOAT getAbs()const{ return __FLOAT(innerFloat(val.opr << 1 >> 1).f); }
        };

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