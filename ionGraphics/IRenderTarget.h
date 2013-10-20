
#pragma once


enum class ERenderTargetType
{
	Texture,
	RenderBuffer
};

class IRenderTarget
{

public:

	IRenderTarget()
	{}

	virtual ERenderTargetType const getRenderTargetType() = 0;

};
