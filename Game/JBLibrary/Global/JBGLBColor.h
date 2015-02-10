#pragma once

#include"JBGlobalMacro.hpp"

namespace JBL{
    namespace COLOR{
        union RGBA_8BIT{
            _DWORD raw;
            struct{
                _BYTE a : 8;
                _BYTE b : 8;
                _BYTE g : 8;
                _BYTE r : 8;
            } parts;

            RGBA_8BIT();
            RGBA_8BIT(const _DWORD col);
            RGBA_8BIT(const _BYTE r, const _BYTE g, const _BYTE b, const _BYTE a);
        };
        union ARGB_8BIT{
            _DWORD raw;
            struct{
                _BYTE b : 8;
                _BYTE g : 8;
                _BYTE r : 8;
                _BYTE a : 8;
            } parts;

            ARGB_8BIT();
            ARGB_8BIT(const _DWORD col);
            ARGB_8BIT(const _BYTE a, const _BYTE r, const _BYTE g, const _BYTE b);
        };

        struct RGBA_32BIT{
            _FLOAT rgba[4];

            RGBA_32BIT();
            RGBA_32BIT(const _FLOAT* col);
            RGBA_32BIT(const _FLOAT r, const _FLOAT g, const _FLOAT b, const _FLOAT a);
        };
        struct ARGB_32BIT{
            _FLOAT argb[4];

            ARGB_32BIT();
            ARGB_32BIT(const _FLOAT* col);
            ARGB_32BIT(const _FLOAT a, const _FLOAT r, const _FLOAT g, const _FLOAT b);
        };


        extern inline ARGB_8BIT glb_RGBA8_To_ARGB8(const RGBA_8BIT c);
        extern inline RGBA_8BIT glb_ARGB8_To_RGBA8(const ARGB_8BIT c);

        extern inline ARGB_32BIT glb_RGBA32_To_ARGB32(const RGBA_32BIT c);
        extern inline RGBA_32BIT glb_ARGB32_To_RGBA32(const ARGB_32BIT c);

        extern inline RGBA_32BIT glb_RGBA8_To_RGBA32(const RGBA_8BIT c);
        extern inline ARGB_32BIT glb_RGBA8_To_ARGB32(const RGBA_8BIT c);

        extern inline RGBA_32BIT glb_ARGB8_To_RGBA32(const ARGB_8BIT c);
        extern inline ARGB_32BIT glb_ARGB8_To_ARGB32(const ARGB_8BIT c);

        extern inline RGBA_8BIT glb_RGBA32_To_RGBA8(const RGBA_32BIT c);
        extern inline ARGB_8BIT glb_RGBA32_To_ARGB8(const RGBA_32BIT c);

        extern inline RGBA_8BIT glb_ARGB32_To_RGBA8(const ARGB_32BIT c);
        extern inline ARGB_8BIT glb_ARGB32_To_ARGB8(const ARGB_32BIT c);
    };
};