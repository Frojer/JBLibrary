#include<windows.h>
#include"JBGlobalFunc.h"
#include"../Core/JBCoreModule.h"

using namespace JBL;
using namespace JBL::SYSTEM;

_BYTE IO::glb_getReverseByte(const _BYTE self){
    return (self == _BYTE(~EOF) || self == _BYTE(EOF)) ? self : ~self;
}

/// @brief 입출력 객체를 초기화 합니다.
/// @param fileName 조작할 파일 경로(와이드바이트)
/// @return 초기화 성공 여부
bool IO::FILE_IO::ins_init(const wchar_t* fileName){
    _SIZE_T strLen = 0;

    {
        _FREE(ins_fileName);

        strLen = wcslen(fileName);
        ins_fileName = _ALLOC<wchar_t>(strLen + 1);
        if (!ins_fileName)return false;

        auto namePtr = ins_fileName;
        while (*fileName){
            *namePtr = *fileName;
            *namePtr = *namePtr == L'\\' ? L'/' : *namePtr;

            ++namePtr;
            ++fileName;
        }
    }

    if (!ins_state.read)glb_makeDir(ins_fileName, strLen);
    _wfopen_s(&ins_file, ins_fileName, ins_state.read ? L"rb" : L"wb");
    if (!ins_file){
        glb_infoMsg(
            IF_ERROR,
            (_WSTRING(L"JBL::IO::FILE_IO::ins_init: failed to read \"") + ins_fileName + L"\".").c_str()
            );
        return false;
    }
    _LOG_S((_WSTRING(L"JBL::IO::FILE_IO::ins_init: succeeded to read \"") + ins_fileName + L"\".").c_str());

    return true;
}

IO::FILE_IO::FILE_IO(){
    ins_file = nullptr;
    ins_fileName = nullptr;
}
IO::FILE_IO::~FILE_IO(){
    if (ins_file){ fclose(ins_file); ins_file = nullptr; }
    _FREE(ins_fileName);
}

long IO::FILE_IO::getFileSize(){
    auto cur = getCurPos();
    if (!moveBackward(0))return EOF;
    auto sz = getCurPos();
    if (!moveForward(cur))return EOF;
    return sz;
}
__int64 IO::FILE_IO::getFileSizeI64(){
    auto cur = getCurPosI64();
    if (!moveBackwardI64(0))return EOF;
    auto sz = getCurPosI64();
    if (!moveForwardI64(cur))return EOF;
    return sz;
}

bool IO::FILE_IO::read(_BYTE* data, const _DWORD size, const bool isFlip){
    if (fread_s(data, size, 1, size, ins_file) != size)return false;
    if (isFlip){
        auto i = decltype(size){0};
        while (i < size){
            *data = glb_getReverseByte(*data);
            ++data;
            ++i;
        }
    }
    return true;
}
bool IO::FILE_IO::readI64(_BYTE* data, const _QWORD size, const bool isFlip){
#ifndef _WIN64
    auto sizeT = (_DWORD)size;
    if (size <= ULONG_MAX){
        if (fread_s(data, sizeT, 1, sizeT, ins_file) != sizeT)return false;
        if (isFlip){
            auto i = decltype(sizeT){0};
            while (i < sizeT){
                *data = glb_getReverseByte(*data);
                ++data;
                ++i;
            }
        }
    }
    else{
        auto i = decltype(sizeT){0};
        while (i < sizeT){
            auto c = get();
            if (c == EOF)return false;
            if (isFlip)c = glb_getReverseByte(c);
            ++i;
        }
        return true;
    }
#else
    if (fread_s(data, size, 1, size, ins_file) != size)return false;
    if (isFlip){
        auto i = decltype(size){0};
        while (i < size){
            *data = glb_getReverseByte(*data);
            ++data;
            ++i;
        }
    }
#endif
    return true;
}

bool IO::FILE_IO::write(void* data, const _DWORD size, const bool isFlip){
    if (!isFlip){
        if (fwrite(data, 1, size, ins_file) != size)return false;
    }
    else{
        auto reverse = [](void* data, const _DWORD& size)->void{
            auto p = (_BYTE*)data;
            auto i = decltype(size){0};
            while (i < size){
                *p = glb_getReverseByte(*p);
                ++p;
                ++i;
            }
        };

        reverse(data, size);
        if (fwrite(data, 1, size, ins_file) != size){
            reverse(data, size);
            return false;
        }
        reverse(data, size);
    }
    return true;
}
bool IO::FILE_IO::writeI64(void* data, const _QWORD size, const bool isFlip){
#ifndef _WIN64
    if(size > ULONG_MAX){
        auto p = (_BYTE*)data;
        auto i = decltype(size){0};
        while (i < size){
            if (!put(isFlip ? glb_getReverseByte(*p) : *p))return false;
            ++p;
            ++i;
        }
        return true;
    }
#endif

    if (!isFlip){
#ifdef _WIN64
        if (fwrite(data, 1, size, ins_file) != size)return false;
#else
        auto sizeT = (_DWORD)size;
        if (fwrite(data, 1, sizeT, ins_file) != sizeT)return false;
#endif
    }
    else{
#ifdef _WIN64
        auto reverse = [](void* data, const _QWORD& size)->void{
            auto p = (_BYTE*)data;
            auto i = decltype(size){0};
            while (i < size){
                *p = glb_getReverseByte(*p);
                ++p;
                ++i;
            }
        };

        reverse(data, size);
        if (fwrite(data, 1, size, ins_file) != size){
            reverse(data, size);
            return false;
        }
        reverse(data, size);
#else
        auto sizeT = (_DWORD)size;

        auto reverse = [](void* data, const _DWORD& size)->void{
            auto p = (_BYTE*)data;
            auto i = decltype(size){0};
            while (i < size){
                *p = glb_getReverseByte(*p);
                ++p;
                ++i;
            }
        };

        reverse(data, sizeT);
        if (fwrite(data, 1, sizeT, ins_file) != sizeT){
            reverse(data, sizeT);
            return false;
        }
        reverse(data, sizeT);
#endif
    }
    return true;
}

void IO::FILE_IO::read(const BYTE* _read, BYTE* data, const _SIZE_T size, _SIZE_T* pos){
    if (_read){
        auto i = decltype(size){*pos};
        auto e = decltype(size){i + size};
        _read += i;
        while (i < e){
            *data = *_read;
            ++data;
            ++_read;

            ++i;
        }
        *pos = i;
    }
}