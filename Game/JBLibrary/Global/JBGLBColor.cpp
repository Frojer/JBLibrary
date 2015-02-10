#include"JBGlobalFunc.h"

using namespace JBL;
using namespace JBL::SYSTEM;

#define MUL255 255.f
#define DIV255 0.0039215686274509803921568627451f

COLOR::RGBA_8BIT::RGBA_8BIT(){ raw = 0x00000000; }
COLOR::RGBA_8BIT::RGBA_8BIT(const _DWORD col){ raw = col; }
COLOR::RGBA_8BIT::RGBA_8BIT(const _BYTE r, const _BYTE g, const _BYTE b, const _BYTE a){
    parts.r = r;
    parts.g = g;
    parts.b = b;
    parts.a = a;
}

COLOR::ARGB_8BIT::ARGB_8BIT(){ raw = 0x00000000; }
COLOR::ARGB_8BIT::ARGB_8BIT(const _DWORD col){ raw = col; }
COLOR::ARGB_8BIT::ARGB_8BIT(const _BYTE a, const _BYTE r, const _BYTE g, const _BYTE b){
    parts.a = a;
    parts.r = r;
    parts.g = g;
    parts.b = b;
}


COLOR::RGBA_32BIT::RGBA_32BIT(){ rgba[0] = rgba[1] = rgba[2] = rgba[3] = 0.f; }
COLOR::RGBA_32BIT::RGBA_32BIT(const _FLOAT* col){ memcpy_s(rgba, sizeof rgba, col, sizeof col); }
COLOR::RGBA_32BIT::RGBA_32BIT(const _FLOAT r, const _FLOAT g, const _FLOAT b, const _FLOAT a){
    rgba[0] = r;
    rgba[1] = g;
    rgba[2] = b;
    rgba[3] = a;
}

COLOR::ARGB_32BIT::ARGB_32BIT(){ argb[0] = argb[1] = argb[2] = argb[3] = 0.f; }
COLOR::ARGB_32BIT::ARGB_32BIT(const _FLOAT* col){ memcpy_s(argb, sizeof argb, col, sizeof col); }
COLOR::ARGB_32BIT::ARGB_32BIT(const _FLOAT a, const _FLOAT r, const _FLOAT g, const _FLOAT b){
    argb[0] = a;
    argb[1] = r;
    argb[2] = g;
    argb[3] = b;
}


COLOR::ARGB_8BIT COLOR::glb_RGBA8_To_ARGB8(const RGBA_8BIT c){
    return ARGB_8BIT(c.parts.a, c.parts.r, c.parts.g, c.parts.b);
}
COLOR::RGBA_8BIT COLOR::glb_ARGB8_To_RGBA8(const ARGB_8BIT c){
    return RGBA_8BIT(c.parts.r, c.parts.g, c.parts.b, c.parts.a);
}

COLOR::ARGB_32BIT COLOR::glb_RGBA32_To_ARGB32(const RGBA_32BIT c){
    return ARGB_32BIT(c.rgba[3], c.rgba[0], c.rgba[1], c.rgba[2]);
}
COLOR::RGBA_32BIT COLOR::glb_ARGB32_To_RGBA32(const ARGB_32BIT c){
    return RGBA_32BIT(c.argb[1], c.argb[2], c.argb[3], c.argb[0]);
}

COLOR::RGBA_32BIT COLOR::glb_RGBA8_To_RGBA32(const RGBA_8BIT c){
    return RGBA_32BIT((_FLOAT)c.parts.r * DIV255, (_FLOAT)c.parts.g * DIV255, (_FLOAT)c.parts.b * DIV255, (_FLOAT)c.parts.a * DIV255);
}
COLOR::ARGB_32BIT COLOR::glb_RGBA8_To_ARGB32(const RGBA_8BIT c){
    return ARGB_32BIT((_FLOAT)c.parts.a * DIV255, (_FLOAT)c.parts.r * DIV255, (_FLOAT)c.parts.g * DIV255, (_FLOAT)c.parts.b * DIV255);
}

COLOR::RGBA_32BIT COLOR::glb_ARGB8_To_RGBA32(const ARGB_8BIT c){
    return RGBA_32BIT((_FLOAT)c.parts.r * DIV255, (_FLOAT)c.parts.g * DIV255, (_FLOAT)c.parts.b * DIV255, (_FLOAT)c.parts.a * DIV255);
}
COLOR::ARGB_32BIT COLOR::glb_ARGB8_To_ARGB32(const ARGB_8BIT c){
    return ARGB_32BIT((_FLOAT)c.parts.a * DIV255, (_FLOAT)c.parts.r * DIV255, (_FLOAT)c.parts.g * DIV255, (_FLOAT)c.parts.b * DIV255);
}

COLOR::RGBA_8BIT COLOR::glb_RGBA32_To_RGBA8(const RGBA_32BIT c){
    return RGBA_8BIT((_BYTE)(c.rgba[0] * MUL255), (_BYTE)(c.rgba[1] * MUL255), (_BYTE)(c.rgba[2] * MUL255), (_BYTE)(c.rgba[3] * MUL255));
}
COLOR::ARGB_8BIT COLOR::glb_RGBA32_To_ARGB8(const RGBA_32BIT c){
    return ARGB_8BIT((_BYTE)(c.rgba[3] * MUL255), (_BYTE)(c.rgba[0] * MUL255), (_BYTE)(c.rgba[1] * MUL255), (_BYTE)(c.rgba[2] * MUL255));
}

COLOR::RGBA_8BIT COLOR::glb_ARGB32_To_RGBA8(const ARGB_32BIT c){
    return RGBA_8BIT((_BYTE)(c.argb[1] * MUL255), (_BYTE)(c.argb[2] * MUL255), (_BYTE)(c.argb[3] * MUL255), (_BYTE)(c.argb[0] * MUL255));
}
COLOR::ARGB_8BIT COLOR::glb_ARGB32_To_ARGB8(const ARGB_32BIT c){
    return ARGB_8BIT((_BYTE)(c.argb[0] * MUL255), (_BYTE)(c.argb[1] * MUL255), (_BYTE)(c.argb[2] * MUL255), (_BYTE)(c.argb[3] * MUL255));
}