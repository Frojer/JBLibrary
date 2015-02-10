﻿#include<forward_list>
#include<algorithm>
#include<io.h>
#include<limits.h>
#include"JBGlobalFunc.h"
#include"../Core/JBCoreModule.h"

using namespace JBL;
using namespace JBL::SYSTEM;

_BYTE FILELIBRARY::glb_cycleByte(const _BYTE raw, const short add){
    if (!add)return raw;

    _WORD out = raw;
    if (add > 0)out += add;
    else{
        _WORD t = -add;
        t %= 256;
        out += 256 - t;
    }
    out %= 256;

    return _BYTE(out);
}

/// @brief 라이브러리를 초기화 합니다.
/// @param file 파일 경로(와이드바이트)
/// @return 읽기 성공 여부
bool FILELIBRARY::FileLibrary::ins_init(const wchar_t* file){
    {
        _FREE(ins_fileRoute);

        auto len = wcslen(file) + 1;
        ins_fileRoute = _ALLOC<wchar_t>(len);
        wcscpy_s(ins_fileRoute, len, file);
    }

    if (!_waccess_s(ins_fileRoute, 0)){
        if (!ins_loadFile())goto INIT_FAIL;
    }
    else goto INIT_FAIL;

    _LOG_S((_WSTRING(L"JBL::FILELIBRARY::FileLibrary: succeeded to read \"") + _WSTRING(file) + L"\".").c_str());
    return true;

INIT_FAIL:
    glb_infoMsg(
        IF_ERROR,
        (_WSTRING(L"JBL::FILELIBRARY::FileLibrary: failed to read \"") + _WSTRING(file) + L"\".").c_str()
        );
    return false;
}
FILELIBRARY::FileLibrary::FileLibrary(const char blendCode){
    ins_blendCode = blendCode < 6 ? 6 : blendCode;

    ins_fileRoute = nullptr;
}
FILELIBRARY::FileLibrary::~FileLibrary(){
    if (!ins_fileData.empty())ins_fileData.clear();
    _FREE(ins_fileRoute);
}

_QWORD FILELIBRARY::FileLibrary::getFileSize(const HashSize data)const{
    auto itr = ins_fileData.find(data);
    return (itr == ins_fileData.cend()) ? 0u : itr->second.second;
}

IO::FILE_IO* FILELIBRARY::FileLibrary::moveFocus(const HashSize data, fileLibraryMap::const_iterator* target)const{
    IO::FILE_IO* inpFile = nullptr;

    fileLibraryMap::const_iterator itr = ins_fileData.find(data);
    if (itr == ins_fileData.cend())goto MOVE_FOCUS_FAIL;

    inpFile = _NEW<IO::FILE_IO>();
    if (!inpFile)return nullptr;
    if (!inpFile->init(true, ins_fileRoute))goto MOVE_FOCUS_FAIL;

    if (!inpFile->moveForwardI64(itr->second.first))goto MOVE_FOCUS_FAIL;
    if (target)*target = itr;

    return inpFile;

MOVE_FOCUS_FAIL:
    _DELETE(inpFile);
    return nullptr;
}

bool FILELIBRARY::FileLibrary::getData(const HashSize data, _VECTOR<_BYTE>& _out)const{
    fileLibraryMap::const_iterator itr;
    _UNIQUE_PTR<IO::FILE_IO> inpFile(moveFocus(data, &itr));
    if (!inpFile)return false;

    _out = _MOVE(_VECTOR<_BYTE>(itr->second.second));
    _QWORD i = 0;
    short cycle = 1;
    _BYTE cur;
    while (i < itr->second.second){
        {
            auto c = inpFile->get(true);
            if (c == EOF)return false;
            cur = _BYTE(c);
        }

        cur ^= cycle;
        cur = glb_cycleByte(cur, -cycle);
        _out[i] = cur;

        if (!(cycle % 5)){
            std::swap(_out[i], _out[i - 2]);
            std::swap(_out[i - 4], _out[i - 3]);
        }

        if (cycle >= ins_blendCode){
            std::swap(_out[i], _out[i - ins_blendCode + 1]);

            cycle = 1;
        }
        else ++cycle;
        ++i;
    }

    return true;
}
/// @brief 라이브러리를 읽습니다.
/// @return 읽기 성공 여부
bool FILELIBRARY::FileLibrary::ins_loadFile(){
    _UNIQUE_PTR<IO::FILE_IO> inpFile(_NEW<IO::FILE_IO>());
    if (!inpFile)return false;
    if (!inpFile->init(true, ins_fileRoute))return false;

    struct TMP_DATA{
        HashSize key;
        _QWORD pos;
        _QWORD size;
    };
    _FORWARD_LIST<TMP_DATA> data;

    _QWORD dataNum;
    if (!inpFile->read((_BYTE*)&dataNum, sizeof dataNum, true))return false;

    long binPos = 0;
    {
        _QWORD totalSize = 0;

        _QWORD i = 0u;
        while (i < dataNum){
            TMP_DATA tmp;

            tmp.pos = totalSize;
            if (!inpFile->read((_BYTE*)&tmp.key, sizeof tmp.key, true))return false;
            if (!inpFile->read((_BYTE*)&tmp.size, sizeof tmp.size, true))return false;

            totalSize += tmp.size;
            i++;

            data.emplace_front(_MOVE(tmp));
        }
        binPos = inpFile->getCurPos();
    }

    for (auto i : data)ins_fileData.emplace(i.key, _MAKE_PAIR(i.pos + binPos, i.size));

    return true;
}


/// @brief 클래스를 초기화 합니다.
/// @param file 파일 경로(와이드바이트)
/// @return 읽기 성공 여부
bool FILELIBRARY::LibLog::ins_init(const wchar_t* file){
    {
        _FREE(ins_fileRoute);

        auto len = wcslen(file) + 1;
        ins_fileRoute = _ALLOC<wchar_t>(len);
        wcscpy_s(ins_fileRoute, len, file);
    }

    if (!_waccess_s(ins_fileRoute, 0)){
        if (!ins_loadFile())goto INIT_FAIL;
    }
    else goto INIT_FAIL;

    _LOG_S((_WSTRING(L"JBL::FILELIBRARY::LibLog: succeeded to read \"") + _WSTRING(file) + L"\".").c_str());
    return true;

INIT_FAIL:
    glb_infoMsg(
        IF_ERROR,
        (_WSTRING(L"JBL::FILELIBRARY::LibLog: failed to read \"") + _WSTRING(file) + L"\".").c_str()
        );
    return false;
}
FILELIBRARY::LibLog::LibLog(){
    ins_fileRoute = nullptr;
}
FILELIBRARY::LibLog::~LibLog(){
    if (!ins_fileData.empty())ins_fileData.clear();
    _FREE(ins_fileRoute);
}

/// @brief 파일을 읽어옵니다.
/// @return 읽기 성공 여부
bool FILELIBRARY::LibLog::ins_loadFile(){
    _UNIQUE_PTR<IO::FILE_IO> inpFile(_NEW<IO::FILE_IO>());
    if (!inpFile)return false;
    if (!inpFile->init(true, ins_fileRoute))return false;

    _QWORD dataNum;

    if (!inpFile->read((_BYTE*)&dataNum, sizeof dataNum, false))return false;

    _QWORD i = 0u;
    while (i < dataNum){
        HashSize strName;
        FILETIME modifyTime;

        if (!inpFile->read((_BYTE*)&strName, sizeof strName, false))return false;
        if (!inpFile->read((_BYTE*)&modifyTime, sizeof modifyTime, false))return false;

        ins_fileData.emplace(strName, modifyTime);
        i++;
    }

    if (!inpFile->read(&ins_blendCode, sizeof ins_blendCode, false))return false;

    return true;
}


FILELIBRARY::LibGenerator::LibGenerator(const _BYTE blendCode){
    ins_blendCode = blendCode < 6 ? 6 : blendCode;
}
FILELIBRARY::LibGenerator::~LibGenerator(){}
bool FILELIBRARY::LibGenerator::generate(const char* read, const char* write){
    fileLibraryTable fileTable;
    fileDateTable fileLog;
    fileGeneratorTable genTable;

    if (ins_searchDirectory(fileTable, fileLog, genTable, read, read))return false;

    _STRING rawRead = read;
    _STRING fileName = _MOVE(rawRead.rfind('\\') == STRING_NPOS ? rawRead : rawRead.substr(rawRead.rfind('\\') + 1));
    _STRING libRoute = _STRING(write) + "\\" + _MOVE(fileName);

    if (_access_s(libRoute.c_str(), 0)){
        if (!ins_genLib(libRoute, fileTable, fileLog, genTable))return false;
    }
    else{
        if (!ins_editLib(libRoute, fileTable, fileLog, genTable))return false;
    }

    return true;
}

/// @brief 재귀호출을 통해 지정된 경로 내 모든 디렉토리 및 파일을 탐색하며 파일을 수집합니다.
/// @return 에러 코드
_DWORD FILELIBRARY::LibGenerator::ins_searchDirectory(
    fileLibraryTable& refvecFiles,
    fileDateTable& libLog,
    fileGeneratorTable& refvecList,
    const _STRING& refcstrRootDirectory,
    const _STRING& defDir
    ){
    _STRING strFilePath;
    _STRING strPattern;
    HANDLE hFile;
    WIN32_FIND_DATAA FileInformation;

    strPattern = refcstrRootDirectory + "\\*.*";

    hFile = ::FindFirstFileA(strPattern.c_str(), &FileInformation);
    if (hFile != INVALID_HANDLE_VALUE){
        do{
            if (FileInformation.cFileName[0] != '.'){
                strFilePath.clear();
                strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;

                if (FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
                    _INT iRC = ins_searchDirectory(refvecFiles, libLog, refvecList, strFilePath, defDir);
                    if (iRC){
                        ::FindClose(hFile);
                        return iRC;
                    }
                }
                else if (!(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)){
                    auto str = _MOVE(strFilePath.substr(defDir.length() + 1));
                    auto hash = _PATH2HASH_M(str.c_str(), str.length());

                    for(auto i : refvecFiles){
                        if (i.first == hash){
                            ::FindClose(hFile);
                            glb_infoMsg(
                                IF_ERROR, (
                                _STRING("JBL::FILELIBRARY::LibGenerator: the overlapping hash key is exist.\n") +
                                +"\"" + refvecList[hash] + "\", \"" + str + "\""
                                ).c_str()
                                );
                            return 0xffffffff;
                        }
                    }

                    refvecFiles.emplace(
                        hash,
                        _QWORD((_QWORD)FileInformation.nFileSizeHigh << 32 | FileInformation.nFileSizeLow)
                        );
                    libLog.emplace(
                        hash,
                        FileInformation.ftLastWriteTime
                        );

                    refvecList.emplace(hash, strFilePath);
                }
            }
        } while (::FindNextFileA(hFile, &FileInformation) == TRUE);

        ::FindClose(hFile);

        _DWORD dwError = ::GetLastError();
        if (dwError != ERROR_NO_MORE_FILES)return dwError;
    }

    return 0;
}

/// @brief 지정된 경로에 이미 라이브러리가 존재한다면, 캐싱된 정보파일을 통해 원본 데이터와 같은지 유추해 냅니다.
///     \n 원본과 다른 경우 라이브러리를 다시 생성합니다.
/// @return 동작 성공 여부
bool FILELIBRARY::LibGenerator::ins_editLib(
    const _STRING& libRoute,
    const fileLibraryTable& fileTable,
    const fileDateTable& libLog,
    const fileGeneratorTable& genTable
    ){
    _UNIQUE_PTR<FILELIBRARY::FileLibrary> lib(_NEW<FILELIBRARY::FileLibrary>(ins_blendCode));
    if (!lib)return false;
    if (!lib->init(libRoute.c_str()))return false;

    _UNIQUE_PTR<FILELIBRARY::LibLog> logL(_NEW<FILELIBRARY::LibLog>());
    if (!logL)return false;
    if (!logL->init((libRoute + ".info").c_str()))return false;

    if (glb_blendCode != logL->getBlendCode())goto EDIT_LIB_RES_FAIL;
    if (lib->getCount() != fileTable.size())goto EDIT_LIB_RES_FAIL;
    for (auto libI = lib->getBegin(), libE = lib->getEnd(); libI != libE; ++libI){
        auto dateLogL = logL->getData(libI->first);

        auto lenFileTable = fileTable.at(libI->first);
        auto dateLibLog = libLog.at(libI->first);

        if (
            libI->second.second != lenFileTable ||
            dateLogL.dwHighDateTime != dateLibLog.dwHighDateTime ||
            dateLogL.dwLowDateTime != dateLibLog.dwLowDateTime
            ){
            goto EDIT_LIB_RES_FAIL;
        }
    }

    _LOG_I((_STRING("JBL::FILELIBRARY::LibGenerator: no changed items. ") +
        "\"" + libRoute + "\"."
        ).c_str());
    return true;

EDIT_LIB_RES_FAIL:
    lib.reset();
    if (remove(libRoute.c_str())){
        glb_infoMsg(
            IF_ERROR, (
            _STRING("JBL::FILELIBRARY::LibGenerator: failed to delete file. ") +
            "\"" + libRoute + "\""
            ).c_str()
            );
        return false;
    }
    return ins_genLib(libRoute, fileTable, libLog, genTable);
}

/// @brief 수집된 파일들을 토대로 라이브러리를 생성합니다.
/// @return 동작 성공 여부
bool FILELIBRARY::LibGenerator::ins_genLib(
    const _STRING& libRoute,
    const fileLibraryTable& fileTable,
    const fileDateTable& libLog,
    const fileGeneratorTable& genTable
    ){
    _UNIQUE_PTR<IO::FILE_IO> f(_NEW<IO::FILE_IO>());
    if (!f)return false;
    if (!f->init(false, libRoute.c_str()))return false;

    _UNIQUE_PTR<IO::FILE_IO> fLog(_NEW<IO::FILE_IO>());
    if (!fLog)return false;
    if (!fLog->init(false, (libRoute + ".info").c_str()))return false;

    _QWORD tmpNum;

    tmpNum = decltype(tmpNum)(fileTable.size());
    if (!f->write((_BYTE*)&tmpNum, sizeof tmpNum, true))return false;
    if (!fLog->write((_BYTE*)&tmpNum, sizeof tmpNum, false))return false;

    for (auto i = fileTable.cbegin(), e = fileTable.cend(); i != e; ++i){
        if (!f->write((_BYTE*)&i->first, sizeof i->first, true))return false;
        if (!f->write((_BYTE*)&i->second, sizeof i->second, true))return false;

        auto curLog = libLog.at(i->first);
        if (!fLog->write((_BYTE*)&i->first, sizeof i->first, false))return false;
        if (!fLog->write((_BYTE*)&curLog, sizeof curLog, false))return false;
    }
    for (auto i = fileTable.cbegin(), e = fileTable.cend(); i != e; ++i){
        _UNIQUE_PTR<IO::FILE_IO> n(_NEW<IO::FILE_IO>());
        if (!n)return false;
        if (!n->init(true, genTable.at(i->first).c_str()))return false;

        _VECTOR<_BYTE> tmp(i->second);
        if (!n->read(&tmp[0], i->second, false))return false;

        _QWORD i2 = 0;
        short cycle = 1;
        while (i2 < i->second){
            if ((i2 == 0 || ((i2 + 1) % ins_blendCode) == 0) && (i2 + ins_blendCode - 1 < i->second)){
                std::swap(tmp[i2], tmp[i2 + ins_blendCode - 1]);
            }

            if (!(cycle % 5)){
                std::swap(tmp[i2], tmp[i2 - 2]);
                std::swap(tmp[i2 - 4], tmp[i2 - 3]);
            }

            if (cycle >= ins_blendCode)cycle = 1;
            else ++cycle;
            ++i2;
        }

        i2 = 0;
        cycle = 1;
        while (i2 < i->second){
            tmp[i2] = glb_cycleByte(tmp[i2], cycle);
            tmp[i2] ^= cycle;

            if (!f->put(tmp[i2], true))return false;

            if (cycle >= ins_blendCode)cycle = 1;
            else ++cycle;
            ++i2;
        }
    }

    _BYTE blendCode = glb_blendCode;
    if (!fLog->write(&blendCode, sizeof blendCode, false))return false;

    //char last[3] = { 'R', 'I', 'P' };
    //if (!f->write(&last, sizeof last, false))return false;
    //if (!fLog->write(&last, sizeof last, false))return false;

    return true;
}