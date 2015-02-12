#include<tchar.h>
#include"JBLibrary/Global/JBGlobalFunc.h"
#include"JBLibrary/Core/JBCoreModule.h"

using namespace JBL;
using namespace JBL::SYSTEM;

#ifdef _DEBUG
bool genFile(const char* rawRoute, const char* genRoute);
#endif

_INT APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE prevInst, LPTSTR cmdLine, _INT showCmd){
    UNREFERENCED_PARAMETER(prevInst);

#ifdef _DEBUG
    glb_instLog.reset(_NEW<JBCORLogWindow>(hInst));
    if (!glb_instLog){
        glb_infoMsg(IF_ERROR, L"MAIN: failed to initialize JBCORLogWindow.");
        return -1;
    }
    _LOG_S(L"MAIN: succeeded to initialize JBCORLogWindow.");

    if (!genFile("..\\data_raw", "..\\data")){
        glb_infoMsg(IF_ERROR, L"MAIN: failed to create library.");
        return -2;
    }
    _LOG_S(L"MAIN: succeeded to create library.");
#endif

    glb_instWindow.reset(_NEW<JBCORWindow>(hInst));
    if (!glb_instWindow){
        glb_infoMsg(IF_ERROR, L"MAIN: failed to initialize JBCORWindow.");
        return -1;
    }
    _LOG_S(L"MAIN: succeeded to initialize JBCORWindow.");

    glb_instDraw.reset(_NEW<JBCORDraw>(glb_instWindow.get()));
    if (!glb_instDraw){
        glb_infoMsg(IF_ERROR, L"MAIN: failed to initialize JBCORDraw.");
        return -1;
    }
    _LOG_S(L"MAIN: succeeded to initialize JBCORDraw.");

    glb_instRender.reset(_NEW<JBCORRender>(glb_instDraw.get()));
    if (!glb_instRender){
        glb_infoMsg(IF_ERROR, L"MAIN: failed to initialize JBCORRender.");
        return -1;
    }
    _LOG_S(L"MAIN: succeeded to initialize JBCORRender.");

    MSG msg;
    ZeroMemory(&msg, sizeof msg);
    while (true){
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (msg.message == WM_QUIT)break;
        else{
            if (!glb_instRender->update()){
                glb_infoMsg(IF_ERROR, L"MAIN: failed to update JBCORRender.");
                return -1;
            }
        }
    }

    return (_INT)msg.wParam;
}

#ifdef _DEBUG
bool genFile(const char* rawRoute, const char* genRoute){
    _UNIQUE_PTR<FILELIBRARY::LibGenerator> f(_NEW<FILELIBRARY::LibGenerator>(glb_blendCode));

    _STRING strFilePath;
    _STRING strPattern = _STRING(rawRoute) + "\\*.*";
    _STRING strExtension;
    WIN32_FIND_DATAA FileInformation;
    HANDLE hFile = ::FindFirstFileA(strPattern.c_str(), &FileInformation);

    if (hFile == INVALID_HANDLE_VALUE)return false;

    do{
        if (FileInformation.cFileName[0] != '.'){
            strFilePath.clear();
            strFilePath = _STRING(rawRoute) + "\\" + FileInformation.cFileName;

            strExtension = FileInformation.cFileName;
            if (strExtension.rfind('.') != _STRING_NPOS){
                strExtension = _MOVE(strExtension.substr(strExtension.rfind('.') + 1));
            }
            else strExtension = "";

            if (
                (strExtension == "jbl") &&
                (FileInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
                (!(FileInformation.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
                ){
                if (!f->generate(strFilePath.c_str(), genRoute)){
                    ::FindClose(hFile);
                    return false;
                }
            }
        }
    } while (::FindNextFileA(hFile, &FileInformation) == TRUE);

    ::FindClose(hFile);
    return true;
}
#endif