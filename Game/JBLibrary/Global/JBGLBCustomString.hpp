#pragma once

#include"JBGlobalMacro.hpp"

namespace JBL{
    namespace STRING{
        /// @brief 문자열 클래스
        template<typename T> class customString{
        private:
            _SIZE_T ins_capacitySz; ///< 실제 할당 공간
            _SIZE_T ins_length; ///< NULL문자 이전까지의 길이
            T* ins_str; ///< 문자열 시작 포인터
        private:
            /// @brief NULL문자 이전까지의 길이를 반환합니다.
            /// @param str 대상 문자열
            /// @return 문자열의 길이
            static _SIZE_T ins_strlen(const T* str){
                if (!str)return 0;

                _SIZE_T i = 0;
                while (*str != (T)0){
                    ++i;
                    ++str;
                }
                return i;
            }

            /// @brief 두 문자열을 비교합니다.
            /// @param str1 대상 문자열 A
            /// @param str2 대상 문자열 B
            /// @return A가 큰 경우 1, B가 큰 경우 -1, 서로 같은 경우 0을 반환합니다.
            static char ins_strcmp(const T* str1, const T* str2){
                if (!str1 || !str2){
                    if (str1)return 1;
                    if (str2)return -1;
                    return 0;
                }

                while (*str1 != (T)0 && *str2 != (T)0){
                    if (*str1 > *str2)return 1;
                    if (*str1 < *str2)return -1;
                    ++str1;
                    ++str2;
                }

                if (*str1)return 1;
                if (*str2)return -1;
                return 0;
            }
            /// @brief 두 문자열을 비교합니다.
            /// @param str1 대상 문자열 A
            /// @param str2 대상 문자열 B
            /// @param n 최대 비교 길이
            /// @return A가 큰 경우 1, B가 큰 경우 -1, 서로 같은 경우 0을 반환합니다.
            static char ins_strcmp(const T* str1, const T* str2, const _SIZE_T n){
                if (!str1 || !str2){
                    if (str1)return 1;
                    if (str2)return -1;
                    return 0;
                }

                _SIZE_T i = 0;
                while (*str1 != (T)0 && *str2 != (T)0 && i < n){
                    if (*str1 > *str2)return 1;
                    if (*str1 < *str2)return -1;
                    ++i;
                    ++str1;
                    ++str2;
                }
                return 0;
            }

            /// @brief 문자열을 복사합니다.
            /// @param dest 복사시킬 공간
            /// @param src 복사시킬 대상
            /// @return 복사가 이루어진 회수
            static _SIZE_T ins_strcpy(T* dest, const T* src){
                if (!dest || !src)return 0;

                _SIZE_T i = 0;
                while (*src != (T)0){
                    *dest = *src;
                    ++i;
                    ++dest;
                    ++src;
                }
                return i;
            }
            /// @brief 문자열을 복사합니다.
            /// @param dest 복사시킬 공간
            /// @param src 복사시킬 대상
            /// @param n 최대 복사 길이
            /// @return 복사가 이루어진 회수
            static _SIZE_T ins_strcpy(T* dest, const T* src, const _SIZE_T n){
                if (!dest || !src)return 0;

                _SIZE_T i = 0;
                while (*src != (T)0 && i < n){
                    *dest = *src;
                    ++i;
                    ++dest;
                    ++src;
                }
                return i;
            }

            /// @brief str의 모든 원소를 c로 초기화 합니다.
            /// @param str 초기화 대상
            /// @param c 초기화 값
            /// @return 초기화가 이루어진 회수
            static _SIZE_T ins_strset(T* str, const T& c){
                if (!str)return 0;

                _SIZE_T i = 0;
                while (*str != (T)0){
                    *str = c;
                    ++i;
                    ++str;
                }
                return i;
            }
            /// @brief str의 모든 원소를 c로 초기화 합니다.
            /// @param str 초기화 대상
            /// @param c 초기화 값
            /// @param n 최대 초기화 길이
            /// @return 초기화가 이루어진 회수
            static _SIZE_T ins_strset(T* str, const T& c, const _SIZE_T n){
                if (!str)return 0;

                _SIZE_T i = 0;
                while (*str != (T)0 && i < n){
                    *str = c;
                    ++i;
                    ++str;
                }
                return i;
            }
        private:
            /// @brief 문자열의 실제 크기를 정해진 값으로 설정합니다.
            /// @param sz 할당 크기
            /// @return 동작 성공 여부
            inline bool ins_sizing(const _SIZE_T& sz){
                if (sz > ins_capacitySz){
                    _FREE(ins_str);
                    ins_str = _ALLOC<T>(sz);
                    if (!ins_str)return false;

                    ins_capacitySz = sz;
                }
                return true;
            }
        public:
            inline bool operator>(const T* str)const{ return ins_strcmp(ins_str, str) == 1; }
            inline bool operator>(const customString& str)const{ return ins_strcmp(ins_str, str.ins_str) == 1; }
            inline bool operator<(const T* str)const{ return ins_strcmp(ins_str, str) == -1; }
            inline bool operator<(const customString& str)const{ return ins_strcmp(ins_str, str.ins_str) == -1; }
            inline bool operator==(const T* str)const{ return ins_strcmp(ins_str, str) == 0; }
            inline bool operator==(const customString& str)const{ return ins_strcmp(ins_str, str.ins_str) == 0; }
            inline bool operator>=(const T* str)const{ return ins_strcmp(ins_str, str) != -1; }
            inline bool operator>=(const customString& str)const{ return ins_strcmp(ins_str, str.ins_str) != -1; }
            inline bool operator<=(const T* str)const{ return ins_strcmp(ins_str, str) != 1; }
            inline bool operator<=(const customString& str)const{ return ins_strcmp(ins_str, str.ins_str) != 1; }
        public:
            /// @brief 문자열의 길이를 반환합니다.
            /// @return 길이
            inline const _SIZE_T length()const{ return ins_length; }
            /// @brief 실제 할당된 크기를 반환합니다.
            /// @return 크기
            inline const _SIZE_T capacitySize()const{ return ins_capacitySz; }
            /// @brief 문자열의 포인터형을 반환합니다.
            /// @return 문자열
            inline const T* c_str()const{ return ins_str; }
        public:
            /// @brief 문자열을 NULL문자로 초기화 합니다.
            inline void clear(){ ins_length = 0; ins_strset(ins_str, (T)0); }
            /// @brief 문자열의 실제 크기를 설정합니다. 현재 할당받은 크기보다 큰 경우에만 동작합니다.
            /// @param n 새로 할당할 크기
            /// @return 동작 성공 여부
            bool resize(const _SIZE_T n){
                T* tmp = nullptr;
                if (n > ins_capacitySz){
                    if (ins_str){
                        if (ins_length){
                            tmp = _ALLOC<T>(ins_length);
                            if (!tmp)goto RESIZE_FAIL;
                            ins_strcpy(tmp, ins_str, ins_length);
                        }
                    }

                    if (!ins_sizing(n))goto RESIZE_FAIL;
                    if (tmp && ins_length){
                        ins_strcpy(ins_str, tmp, ins_length);
                        ins_str[ins_length] = (T)0;
                        _FREE(tmp);
                    }
                }
                return true;
            RESIZE_FAIL:
                _FREE(tmp);
                return false;
            }
        public:
            /// @brief 문자열의 ind번째 원소를 반환합니다.
            /// @param ind 인덱스
            /// @return 해당 위치의 원소
            inline T& operator[](const _SIZE_T ind){ return ins_str[ind]; }
            /// @brief 문자열의 ind번째 원소를 반환합니다.
            /// @param ind 인덱스
            /// @return 해당 위치의 원소
            inline T operator[](const _SIZE_T ind)const{ return ins_str[ind]; }
            /// @brief 문자열의 ind번째 원소를 반환합니다. 할당 영역 밖의 인덱스를 참조하는 경우, 예외가 발생합니다.
            /// @param ind 인덱스
            /// @return 해당 위치의 원소
            inline T at(const _SIZE_T ind)const{
#ifdef _DEBUG
                if (ind >= ins_capacitySz)throw _ERROR_EXCEPTION(L"JBL::STRING::customString: out of range.");
#endif
                return ins_str[ind];
            }
        public:
            /// @brief 문자열의 전체 크기만큼 순회하며 원소마다 함수를 이행합니다.
            /// @param work 동작시킬 함수
            void transform(_FUNC<T(T)> work){
                if (!ins_str)return;
                if (!work)return;

                auto i = decltype(ins_capacitySz){0};
                T* p = ins_str;
                while (i < ins_capacitySz){
                    *p = work(*p);
                    ++p;
                    ++i;
                }
            }
        public:
            /// @brief 문자열을 pos위치부터 순방향으로 탐색하며 c가 발견되는 위치를 찾습니다.
            /// @param c 찾을 문자열
            /// @param pos 탐색 시작 위치
            /// @return 최초로 c가 발견되는 위치의 인덱스
            _SIZE_T find(const T c, const _SIZE_T pos)const{
                if (!ins_str)return STRING_NPOS;

                _SIZE_T i = pos;
                const T* p = ins_str + pos;
                while (*p != (T)0){
                    if (*p == c)return i;
                    ++i;
                    ++p;
                }
                return STRING_NPOS;
            }
            /// @brief 문자열을 처음부터 순방향으로 탐색하며 c가 발견되는 위치를 찾습니다.
            /// @param c 찾을 문자열
            /// @param pos 탐색 시작 위치
            /// @return 최초로 c가 발견되는 위치의 인덱스
            inline _SIZE_T find(const T c)const{ return find(c, 0); }

            /// @brief 문자열을 pos위치부터 역방향으로 탐색하며 c가 발견되는 위치를 찾습니다.
            /// @param c 찾을 문자열
            /// @param pos 탐색 시작 위치
            /// @return 최초로 c가 발견되는 위치의 인덱스
            _SIZE_T rfind(const T c, const _SIZE_T pos)const{
                if (!ins_str)return STRING_NPOS;

                _SIZE_T i = pos;
                const T* p = ins_str + i;
                while (i > 0){
                    if (*p == c)return i;
                    --p;
                    --i;
                }
                if (*p == c)return i;
                return STRING_NPOS;
            }
            /// @brief 문자열을 끝부터 역방향으로 탐색하며 c가 발견되는 위치를 찾습니다.
            /// @param c 찾을 문자열
            /// @param pos 탐색 시작 위치
            /// @return 최초로 c가 발견되는 위치의 인덱스
            inline _SIZE_T rfind(const T c)const{ if (!ins_length)return STRING_NPOS; return rfind(c, ins_length - 1); }
        public:
            /// @brief 문자열의 begin인덱스부터 len만큼까지를 반환합니다.
            /// @param begin 시작 위치
            /// @param len 반환 문자열의 크기
            /// @return 자른 문자열의 결과
            customString substr(const _SIZE_T begin, const _SIZE_T len)const{
                if (!ins_str)return customString();
                if (!len)return customString();

                if (!ins_length)return customString();

                if (begin == ins_length)return customString();
#ifdef _DEBUG
                if (begin > ins_length)throw _ERROR_EXCEPTION(L"JBL::STRING::customString: out of range.");
                if (begin + len - 1 >= ins_length)throw _ERROR_EXCEPTION(L"JBL::STRING::customString: out of range.");
#endif

                T* tmp = _ALLOC<T>(len + 1);
#ifdef _DEBUG
                if (!tmp)throw _ERROR_EXCEPTION(L"JBL::STRING::customString: failed to allocate memory.");
#endif
                ins_strcpy(tmp, ins_str + begin, len);

                return customString(_MOVE(tmp));
            }
            /// @brief 문자열의 begin인덱스부터 NULL문자 이전까지를 반환합니다.
            /// @param begin 시작 위치
            /// @return 자른 문자열의 결과
            customString substr(const _SIZE_T begin)const{
                if (!ins_str)return customString();

                if (!ins_length)return customString();

                if (begin == ins_length)return customString();
#ifdef _DEBUG
                if (begin > ins_length)throw _ERROR_EXCEPTION(L"JBL::STRING::customString: out of range.");
#endif

                T* tmp = _ALLOC<T>(ins_length - begin + 1);
#ifdef _DEBUG
                if (!tmp)throw _ERROR_EXCEPTION(L"JBL::STRING::customString: failed to allocate memory.");
#endif
                ins_strcpy(tmp, ins_str + begin);

                return customString(_MOVE(tmp));
            }
        public:
            customString(){
                ins_capacitySz = 0;
                ins_length = 0;
                ins_str = nullptr;
            }
            customString(const _SIZE_T& size){
                ins_capacitySz = 0;
                ins_length = 0;
                ins_str = nullptr;
#ifdef _DEBUG
                if (!ins_sizing(size))throw _ERROR_EXCEPTION(L"JBL::STRING::customString: failed to allocate memory.");
#else
                ins_sizing(size);
#endif
            }
            customString(const T* str, const _SIZE_T len){
                ins_capacitySz = 0;
                ins_str = nullptr;
#ifdef _DEBUG
                if (!ins_sizing(len + 1))throw _ERROR_EXCEPTION(L"JBL::STRING::customString: failed to allocate memory.");
#else
                ins_sizing(len + 1);
#endif
                ins_length = ins_strcpy(ins_str, str, len);
            }
            customString(const T* str){
                ins_capacitySz = 0;
                ins_str = nullptr;
#ifdef _DEBUG
                if (!ins_sizing(ins_strlen(str) + 1))throw _ERROR_EXCEPTION(L"JBL::STRING::customString: failed to allocate memory.");
#else
                ins_sizing(ins_strlen(str) + 1);
#endif
                ins_length = ins_strcpy(ins_str, str);
            }
            customString(T*&& str){
                ins_length = ins_strlen(str);
                ins_capacitySz = ins_length + 1;
                ins_str = str;
                str = nullptr;
            }
            customString(const customString& str, const _SIZE_T len){
                if (this != &str){
                    ins_capacitySz = 0;
                    ins_str = nullptr;
#ifdef _DEBUG
                    if (!ins_sizing(len + 1))throw _ERROR_EXCEPTION(L"JBL::STRING::customString: failed to allocate memory.");
#else
                    ins_sizing(len + 1);
#endif
                    ins_length = ins_strcpy(ins_str, str.ins_str, len);
                }
            }
            customString(const customString& str){
                if (this != &str){
                    ins_capacitySz = 0;
                    ins_str = nullptr;
#ifdef _DEBUG
                    if (!ins_sizing(str.ins_capacitySz))throw _ERROR_EXCEPTION(L"JBL::STRING::customString: failed to allocate memory.");
#else
                    ins_sizing(str.ins_capacitySz);
#endif
                    ins_length = ins_strcpy(ins_str, str.ins_str);
                }
            }
            customString(customString&& str){
                ins_capacitySz = 0;
                ins_str = nullptr;
                if (this != &str){
                    ins_str = str.ins_str;
                    ins_capacitySz = str.ins_capacitySz;
                    ins_length = str.ins_length;
                    str.ins_str = nullptr;
                    str.ins_capacitySz = 0;
                    str.ins_length = 0;
                }
            }
        public:
            customString& operator=(const T* str){
                ins_length = ins_strlen(str);
                if (ins_length + 1 > ins_capacitySz){
                    ins_capacitySz = 0;
                    _FREE(ins_str);
#ifdef _DEBUG
                    if (!ins_sizing(ins_length + 1))throw _ERROR_EXCEPTION(L"JBL::STRING::customString: failed to allocate memory.");
#else
                    ins_sizing(ins_length + 1);
#endif
                }
                ins_strcpy(ins_str, str);
                ins_str[ins_length] = (T)0;
                return *this;
            }
            customString& operator=(T*&& str){
                ins_length = ins_strlen(str);
                if (ins_length + 1 > ins_capacitySz){
                    _FREE(ins_str);
                    ins_capacitySz = ins_length + 1;
                    ins_str = str;
                }
                else{
                    ins_strcpy(ins_str, str);
                    ins_str[ins_length] = (T)0;
                    _FREE(str);
                }
                str = nullptr;
                return *this;
            }
            customString& operator=(const customString& str){
                if (this == &str)return *this;

                ins_length = str.ins_length;
                if (ins_length + 1 > ins_capacitySz){
                    ins_capacitySz = 0;
                    _FREE(ins_str);
#ifdef _DEBUG
                    if (!ins_sizing(ins_length + 1))throw _ERROR_EXCEPTION(L"JBL::STRING::customString: failed to allocate memory.");
#else
                    ins_sizing(ins_length + 1);
#endif
                }
                ins_strcpy(ins_str, str.ins_str);
                ins_str[ins_length] = (T)0;
                return *this;
            }
            customString& operator=(customString&& str){
                if (this == &str)return *this;

                if (str.ins_capacitySz >= ins_capacitySz){
                    _FREE(ins_str);
                    ins_capacitySz = str.ins_capacitySz;
                    ins_length = str.ins_length;
                    ins_str = str.ins_str;
                }
                else{
                    ins_length = ins_strcpy(ins_str, str.ins_str);
                    ins_str[ins_length] = (T)0;
                    _FREE(str.ins_str);
                }
                str.ins_str = nullptr;
                str.ins_capacitySz = 0;
                str.ins_length = 0;
                return *this;
            }
        public:
            virtual ~customString(){
                ins_capacitySz = 0;
                ins_length = 0;
                _FREE(ins_str);
            }
        public:
            customString& operator+=(const T c){
#ifdef _DEBUG
                if (!resize(ins_length + 2))throw _ERROR_EXCEPTION(L"JBL::STRING::customString: failed to allocate memory.");
#else
                resize(ins_length + 2);
#endif
                ins_str[ins_length] = c;
                ins_str[ins_length + 1] = (T)0;
                ++ins_length;
                return *this;
            }
            customString& operator+=(const T* str){
                _SIZE_T rawLen = ins_length;
                _SIZE_T tarLen = ins_strlen(str);
                if (!(rawLen + tarLen))return *this;
#ifdef _DEBUG
                if (!resize(rawLen + tarLen + 1))throw _ERROR_EXCEPTION(L"JBL::STRING::customString: failed to allocate memory.");
#else
                resize(rawLen + tarLen + 1);
#endif
                ins_length = ins_strcpy(ins_str + rawLen, str);
                ins_str[rawLen + tarLen] = (T)0;
                return *this;
            }
            customString& operator+=(const customString& str){
                _SIZE_T rawLen = ins_length;
                _SIZE_T tarLen = str.ins_length;
                if (!(rawLen + tarLen))return *this;
#ifdef _DEBUG
                if (!resize(rawLen + tarLen + 1))throw _ERROR_EXCEPTION(L"JBL::STRING::customString: failed to allocate memory.");
#else
                resize(rawLen + tarLen + 1);
#endif
                ins_length = ins_strcpy(ins_str + rawLen, str.ins_str);
                ins_str[rawLen + tarLen] = (T)0;
                return *this;
            }
        public:
            inline customString operator+(const T c)const{ return customString<T>(*this) += c; }
            inline customString operator+(const T* str)const{ return customString<T>(*this) += str; }
            inline customString operator+(const customString& str)const{ return customString<T>(*this) += str; }
        };
    };
};