
#include "FreeType.h"

#include <imgui.h>

// This whole library should be deprecated in favor of plain imGUI usage or perhaps some helpers
// Partial shim to use imGUI fonts for the time being

class CFont : public IFont
{

public:

	static IFont * init(const char * fname, unsigned int h);

	virtual ~CFont();

	virtual void measure(int * width, int * height, char const * fmt, ...);

	virtual void print(float x, float y, const char *fmt, ...) ;

protected:

	ImFont * Font = nullptr;
	float Size = 0;

};




IFont * IFont::init(const char * fname, unsigned int h)
{
	return CFont::init(fname, h);
}

IFont * CFont::init(const char * fname, unsigned int h)
{
	ImGuiIO& io = ImGui::GetIO();

	CFont * Font = new CFont();
	Font->Font = io.Fonts->AddFontFromFileTTF(fname, h);
	Font->Size = h;

	return Font;
}

CFont::~CFont()
{
	delete Font;
	Font = nullptr;
}

void CFont::measure(int * width, int * height, char const * fmt, ...)
{
	//Font->CalcTextSizeA(Size, std::numeric_limits<float>::max(), 0.f, 
	// BUGBUG todo
	*width = 0;
	*height = 0;
}

void CFont::print(float x, float y, const char * fmt, ...)
{
	// BUGBUG todo
}
