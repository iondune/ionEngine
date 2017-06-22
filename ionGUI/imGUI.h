
#pragma once


#include <ionMath.h>

//---- Define constructor and implicit cast operators to convert back<>forth from your math types and ImVec2/ImVec4.

#define IM_VEC2_CLASS_EXTRA                                                 \
        ImVec2(const ion::vec2f& f) { x = f.X; y = f.Y; }                       \
        operator ion::vec2f() const { return ion::vec2f(x,y); }

#define IM_VEC4_CLASS_EXTRA                                                 \
        ImVec4(const ion::vec4f& f) { x = f.X; y = f.Y; z = f.Z; w = f.W; }     \
        operator ion::vec4f() const { return ion::vec4f(x,y,z,w); }

#include <imgui.h>
