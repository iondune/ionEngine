#ifndef _CABBAGE_SCENE_IRENDERTARGET_H_INCLUDED_
#define _CABBAGE_SCENE_IRENDERTARGET_H_INCLUDED_


#include <ionEnum.h>

struct ERenderTargetTypeValues
{
	enum Domain
	{
		Texture,
		RenderBuffer
	};
};

typedef Enum<ERenderTargetTypeValues> ERenderTargetType;

class IRenderTarget
{

public:

	IRenderTarget()
	{}

	virtual ERenderTargetType const getRenderTargetType() = 0;

};

#endif
