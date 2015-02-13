
#pragma once

#include <ionCore.h>
#include <ionGL.h>
#include <ionAsset.h>


class CTileManager : public Singleton<CTileManager>
{

public:

	void Init();

	void Draw();

protected:

	ion::GL::Program * shader = nullptr;
	ion::GL::DrawConfig * Config = nullptr;

	ion::GL::UniformValue<vec2f> * min = nullptr;
	ion::GL::UniformValue<vec2f> * max = nullptr;

};
