#pragma once

#include<bitset>
#include<windows.h>

namespace JBL{
    /// 게임 버전을 설정합니다.
    static const _WORD glb_gameVersion = 0x0001;

    /// 파일 암호화 코드를 설정합니다.
    static const _BYTE glb_blendCode = 17;

    /// 각종 설정 값이 저장된 비트 테이블 입니다.
    static _BITSET<2> glb_state(0x01); // 초기 값: 10(2)(리틀엔디안)
#define JBL_STATE_VSYNC 0 ///< 수직 동기화 여부를 설정합니다.
#define JBL_STATE_FULLSCREEN 1 ///< 풀스크린 여부를 설정합니다.

    /// 창 크기를 설정합니다.
    static POINT glb_workSpace = { 640, 480 };
    /// 클래스 이름을 설정합니다.
    static const wchar_t* glb_className = L"PROTOTYPE";
    /// 타이틀 이름을 설정합니다.
    static const wchar_t* glb_titleName = L"Example";
};