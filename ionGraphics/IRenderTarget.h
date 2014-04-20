
#pragma once


enum class ERenderTargetType
{
	Texture,
	RenderBuffer
};

class IRenderTarget
{

public:

	virtual ERenderTargetType const GetRenderTargetType() = 0;

};
