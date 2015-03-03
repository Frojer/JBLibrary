#pragma once

namespace JBL{
    namespace SYSTEM{
        /// @brief 메세지 다이얼로그의 모양을 위한 열거체
        enum MESSAGE_TYPE :_BYTE{
            IF_ERROR, ///< 에러 마크
            IF_WARNING, ///< 경고 마크
            IF_INFO ///< 정보 마크
        };

        /// @brief 메세지 다이얼로그를 띄웁니다. 디버그 모드의 경우 디버그 출력창에도 메세지가 출력됩니다.
        /// @param type 메세지 타입(아이콘 및 소리)을 결정합니다.
        /// @param msg 출력할 메세지(멀티바이트)
        /// @return MessageBoxA(...)의 반환 값입니다.
        extern _INT glb_infoMsg(const MESSAGE_TYPE type, const char* msg);
        /// @brief 메세지 다이얼로그를 띄웁니다. 디버그 모드의 경우 디버그 출력창에도 메세지가 출력됩니다.
        /// @param type 메세지 타입(아이콘 및 소리)을 결정합니다.
        /// @param msg 출력할 메세지(와이드바이트)
        /// @return MessageBoxW(...)의 반환 값입니다.
        extern _INT glb_infoMsg(const MESSAGE_TYPE type, const wchar_t* msg);

        /// @brief 파일이 위치까지의 디렉토리를 생성합니다.
        /// @param path 파일의 위치까지 전체 경로를 입력합니다.(멀티바이트)
        /// @param len path의 길이를 입력합니다.
        /// @return 성공 여부
        extern bool glb_makeDir(const char* path, const _SIZE_T len);
        /// @brief 파일이 위치까지의 디렉토리를 생성합니다.
        /// @param path 파일의 위치까지 전체 경로를 입력합니다.(와이드바이트)
        /// @param len path의 길이를 입력합니다.
        /// @return 성공 여부
        extern bool glb_makeDir(const wchar_t* path, const _SIZE_T len);

        /// @brief 화면의 해상도를 얻어옵니다.
        /// @return 화면 해상도
        extern POINT glb_getScreenSize();

        /// @brief 해당 핸들에 포커스를 맞춥니다.
        extern void glb_setFocus(const HWND&);
    };
};