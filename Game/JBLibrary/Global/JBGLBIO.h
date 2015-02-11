#pragma once

#include"JBGlobalMacro.hpp"
#include"JBGLBString.h"

namespace JBL{
    namespace IO{
        /// @brief 뒤집힌 바이트 값을 구합니다.
        /// @param self 대상 바이트
        /// @return 뒤집힌 값
        extern inline _BYTE glb_getReverseByte(const _BYTE self);

        /// @brief 파일 입출력을 위한 구조체
        class FILE_IO{
        private:
            FILE* ins_file;
            wchar_t* ins_fileName;
        private:
            struct{
                bool read : 1;
            } ins_state;
        private:
            bool ins_init(const wchar_t* fileName);
        public:
            FILE_IO();
            virtual ~FILE_IO();
        public:
            /// @brief 클래스를 초기화 합니다.
            /// @param isRead 파일 읽기/쓰기 여부를 설정합니다.
            /// @param fileName 조작할 파일 경로(와이드바이트)
            /// @return 초기화 성공 여부
            inline bool init(const bool isRead, const wchar_t* fileName){
                ins_state.read = isRead;
                return ins_init(fileName);
            }
            /// @brief 클래스를 초기화 합니다.
            /// @param isRead 파일 읽기/쓰기 여부를 설정합니다.
            /// @param fileName 조작할 파일 경로(멀티바이트)
            /// @return 초기화 성공 여부
            inline bool init(const bool isRead, const char* fileName){
                ins_state.read = isRead;
                return ins_init(STRING::glb_ansiToWide(fileName).c_str());
            }
        public:
            /// @brief 현재 입출력 객체가 읽고 있는 파일의 위치를 구합니다.
            /// @return 현재 위치(4바이트)
            inline long getCurPos(){ return ftell(ins_file); }
            /// @brief 현재 입출력 객체가 읽고 있는 파일의 위치를 구합니다.
            /// @return 현재 위치(8바이트)
            inline __int64 getCurPosI64(){ return _ftelli64(ins_file); }
        public:
            /// @brief 현재 파일의 크기를 구합니다.
            /// @return 파일 크기(4바이트)
            long getFileSize();
            /// @brief 현재 파일의 크기를 구합니다.
            /// @return 파일 크기(8바이트)
            __int64 getFileSizeI64();
        public:
            /// @brief 맨 처음 위치로부터 입출력 객체가 읽을 위치를 설정합니다.
            /// @param size 위치 크기(4바이트)
            /// @return 동작 성공 여부
            inline bool moveForward(const long size){ return !fseek(ins_file, size, SEEK_SET); }
            /// @brief 맨 처음 위치로부터 입출력 객체가 읽을 위치를 설정합니다.
            /// @param size 위치 크기(8바이트)
            /// @return 동작 성공 여부
            inline bool moveForwardI64(const __int64 size){ return !_fseeki64(ins_file, size, SEEK_SET); }
        public:
            /// @brief 맨 마지막 위치로부터 입출력 객체가 읽을 위치를 설정합니다.
            /// @param size 위치 크기(4바이트)
            /// @return 동작 성공 여부
            inline bool moveBackward(const long size){ return !fseek(ins_file, size, SEEK_END); }
            /// @brief 맨 마지막 위치로부터 입출력 객체가 읽을 위치를 설정합니다.
            /// @param size 위치 크기(8바이트)
            /// @return 동작 성공 여부
            inline bool moveBackwardI64(const __int64 size){ return !_fseeki64(ins_file, size, SEEK_END); }
        public:
            /// @brief 현재 위치로부터 입출력 객체가 읽을 위치를 설정합니다.
            /// @param size 위치 크기(4바이트)
            /// @return 동작 성공 여부
            inline bool jump(const long size){ return !fseek(ins_file, size, SEEK_CUR); }
            /// @brief 현재 위치로부터 입출력 객체가 읽을 위치를 설정합니다.
            /// @param size 위치 크기(8바이트)
            /// @return 동작 성공 여부
            inline bool jumpI64(const __int64 size){ return !_fseeki64(ins_file, size, SEEK_CUR); }
        public:
            /// @brief 현재 위치에 1바이트 크기만큼 데이터를 기록합니다.
            /// @param data 기록할 데이터
            /// @param isFlip 바이트 뒤집기 여부
            /// @return 동작 성공 여부
            inline bool put(_BYTE data, const bool isFlip = false){ data = isFlip ? glb_getReverseByte(data) : data; return putc(data, ins_file) == data; }
            /// @brief 현재 위치로부터 1바이트 크기만큼 데이터를 읽어옵니다.
            /// @param isFlip 바이트 뒤집기 여부
            /// @return 읽어올 데이터(EOF일 경우 오류)
            inline _INT get(const bool isFlip = false){ auto c = getc(ins_file); return c != EOF ? isFlip ? glb_getReverseByte(c) : c : EOF; }
        public:
            /// @brief 현재 위치로부터 정해진 크기만큼 데이터를 읽어옵니다.(읽기 전용)
            /// @param data 데이터를 기록할 공간
            /// @param size 읽을 크기(4바이트)
            /// @param isFlip 바이트 뒤집기 여부
            /// @return 동작 성공 여부
            bool read(_BYTE* data, const _DWORD size, const bool isFlip = false);
            /// @brief 현재 위치로부터 정해진 크기만큼 데이터를 읽어옵니다.(읽기 전용)
            /// @param data 데이터를 기록할 공간
            /// @param size 읽을 크기(8바이트)
            /// @param isFlip 바이트 뒤집기 여부
            /// @return 동작 성공 여부
            bool readI64(_BYTE* data, const _QWORD size, const bool isFlip = false);
        public:
            /// @brief 현재 위치로부터 정해진 크기만큼 데이터를 기록합니다.(쓰기 전용)
            /// @param data 기록할 데이터
            /// @param size 기록할 크기(4바이트)
            /// @param isFlip 바이트 뒤집기 여부
            /// @return 동작 성공 여부
            bool write(void* data, const _DWORD size, const bool isFlip = false);
            /// @brief 현재 위치로부터 정해진 크기만큼 데이터를 기록합니다.(쓰기 전용)
            /// @param data 기록할 데이터
            /// @param size 기록할 크기(8바이트)
            /// @param isFlip 바이트 뒤집기 여부
            /// @return 동작 성공 여부
            bool writeI64(void* data, const _QWORD size, const bool isFlip = false);
        public:
            /// @brief _read에서 pos로부터 size만큼 데이터를 읽어서 data에 기록합니다.
            /// @param _read 읽어올 데이터
            /// @param data 기록할 위치
            /// @param size 읽어올 크기
            /// @param pos 읽어올 위치 / 함수 반환시 _read에서 읽은 마지막 위치 + 1이 기록됩니다.
            static void read(const _BYTE* _read, _BYTE* data, const _SIZE_T size, _SIZE_T* pos);
        };
    };
};