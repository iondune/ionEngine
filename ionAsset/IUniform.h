
#pragma once

#include <ionGL.h>


typedef ion::GL::Uniform IUniform;

template <typename T>
using CUniformValue = ion::GL::UniformValue<T>;

template <typename T>
using CUniformReference = ion::GL::UniformReference<T>;


typedef ion::GL::VertexBuffer CVertexBuffer;
typedef ion::GL::IndexBuffer CIndexBuffer;
