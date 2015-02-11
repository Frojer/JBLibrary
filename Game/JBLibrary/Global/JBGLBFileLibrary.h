#pragma once

#ifdef _DEBUG
#include<map>
#endif

#include<vector>
#include<boost/unordered_map.hpp>
#include<boost/functional/hash.hpp>
#include"JBGLBHash.hpp"
#include"JBGLBIO.h"
#include"JBGLBString.h"

namespace JBL{
    namespace FILELIBRARY{
        typedef boost::uint64_t HashSize;


        /// @brief 원본 바이트에서 add만큼 더한 값을 1byte크기로 순환하여 반환합니다.
        /// @param raw 원본 바이트
        /// @param add 오프셋
        /// @return 결과 값
        extern inline _BYTE glb_cycleByte(const _BYTE raw, const short add);


        /// @brief 파일 라이브러리
        /// @details 라이브러리는 다음과 같은 순서로 구성됩니다.
        /// @details 전체 파일 개수
        ///       \n -파일 이름
        ///       \n -파일 크기
        ///       \n 파일 바이너리 데이터 열거
        class FileLibrary{
        private:
            typedef _UNORDERED_MAP<HashSize, _PAIR<_QWORD, _QWORD>, HASH::hashedKeyHasher<HashSize>> fileLibraryMap;
        private:
            wchar_t* ins_fileRoute;
            char ins_blendCode;
            fileLibraryMap ins_fileData;
        public:
            /// @brief 클래스를 생성합니다.
            /// @param blendCode 파일 복호화를 위한 코드
            FileLibrary(const char blendCode);
            virtual ~FileLibrary();
        public:
            /// @brief 라이브러리를 초기화 합니다.
            /// @param file 파일 경로(와이드바이트)
            /// @return 읽기 성공 여부
            inline bool init(const wchar_t* file){ return ins_init(file); }
            /// @brief 라이브러리를 초기화 합니다.
            /// @param file 파일 경로(멀티바이트)
            /// @return 읽기 성공 여부
            inline bool init(const char* file){ return ins_init(STRING::glb_ansiToWide(file).c_str()); }
        public:
            /// @brief 파일의 개수를 얻습니다.
            /// @return 파일 개수
            inline _QWORD getCount()const{ return _QWORD(ins_fileData.size()); }
            /// @brief 해당 파일의 크기를 얻습니다.
            /// @param data 해당 파일의 해쉬 키
            /// @return 해당 파일의 크기
            _QWORD getFileSize(const HashSize data)const;
            
            /// @brief 현재 읽어들인 라이브러리의 경로를 반환합니다.
            /// @return 현재 라이브러리의 경로
            inline _WSTRING getfileRoute()const{ return ins_fileRoute; }
        public:
            /// @brief 라이브러리 파일의 커서를 해당 파일의 바이너리 시작 위치로 옮깁니다. 바이너리 데이터는 암호화 되어있는 상태입니다.
            /// @param data 해당 파일의 해쉬 키
            /// @param target 해당 파일을 가리키는 컨테이너의 반복자를 포인터로 반환합니다.
            /// @return 라이브러리를 파일을 가리키는 파일 클래스입니다. 동적 객체이기 때문에 사용 후 소멸해야 합니다.
            IO::FILE_IO* moveFocus(const HashSize data, fileLibraryMap::const_iterator* target = nullptr)const;
            /// @brief 해당 파일의 복호화 과정이 완료된 바이너리 데이터를 반환합니다.
            /// @param data 해당 파일의 해쉬 키
            /// @param _out 바이너리 데이터를 받을 공간
            /// @return 동작 성공 여부
            bool getData(const HashSize data, _VECTOR<_BYTE>& _out)const;
        public:
            /// @brief 컨테이너의 시작 위치를 반환합니다.
            /// @return const속성의 반복자
            inline fileLibraryMap::const_iterator getBegin()const{ return ins_fileData.cbegin(); }
            /// @brief 컨테이너의 끝 위치를 반환합니다.
            /// @return const속성의 반복자
            inline fileLibraryMap::const_iterator getEnd()const{ return ins_fileData.cend(); }
        private:
            bool ins_init(const wchar_t* file);
            bool ins_loadFile();
        };


#ifdef _DEBUG
        typedef _MAP<HashSize, _QWORD> fileLibraryTable;
        typedef _MAP<HashSize, FILETIME> fileDateTable;
        typedef _MAP<HashSize, _STRING> fileGeneratorTable;


        /// @brief 라이브러리 캐시를 위한 클래스
        /// @details 정보 파일은 다음과 같은 순서로 구성됩니다.
        /// @details 전체 파일 개수
        ///       \n -파일 이름
        ///       \n -파일 최종 편집 날짜
        class LibLog{
        private:
            wchar_t* ins_fileRoute;
            _BYTE ins_blendCode;
            fileDateTable ins_fileData;
        public:
            LibLog();
            virtual ~LibLog();
        public:
            /// @brief 클래스를 초기화 합니다.
            /// @param file 파일 경로(와이드바이트)
            /// @return 읽기 성공 여부
            inline bool init(const wchar_t* file){ return ins_init(file); }
            /// @brief 클래스를 초기화 합니다.
            /// @param file 파일 경로(멀티바이트)
            /// @return 읽기 성공 여부
            inline bool init(const char* file){ return ins_init(STRING::glb_ansiToWide(file).c_str()); }
        public:
            /// @brief 라이브러리의 암호화 코드를 얻습니다.
            /// @return 현재 라이브러리의 암호화 코드
            inline _BYTE getBlendCode()const{ return ins_blendCode; };
            /// @brief 해당 파일의 정보를 얻습니다.
            /// @param key 해당 파일의 해쉬 키
            /// @return 해당 파일의 정보 값
            inline FILETIME getData(const HashSize key)const{ return ins_fileData.at(key); };
        private:
            bool ins_init(const wchar_t* file);
            bool ins_loadFile();
        };

        /// @brief 라이브러리 생성기
        class LibGenerator{
        private:
            _BYTE ins_blendCode;
        public:
            /// @brief 클래스를 생성합니다.
            /// @param blendCode 파일 암호화를 위한 코드
            LibGenerator(const _BYTE blendCode);
            virtual ~LibGenerator();
        public:
            /// @brief read에 존재하는 모든 파일(이 경로로부터 하위 경로 포함)을 읽어 write에 라이브러리로 기록합니다.
            /// @param read 라이브러리로 묶을 대상의 경로
            /// @param write 라이브러리를 기록할 경로
            /// @return 동작 성공 여부
            bool generate(const char* read, const char* write);
        private:
            _DWORD ins_searchDirectory(
                fileLibraryTable& refvecFiles,
                fileDateTable& libLog,
                fileGeneratorTable& refvecList,
                const _STRING& refcstrRootDirectory,
                const _STRING& defDir
                );
        private:
            bool ins_genLib(
                const _STRING& libRoute,
                const fileLibraryTable&,
                const fileDateTable&,
                const fileGeneratorTable&
                );
            bool ins_editLib(
                const _STRING& libRoute,
                const fileLibraryTable&,
                const fileDateTable&,
                const fileGeneratorTable&
                );
        };
#endif
    };
}