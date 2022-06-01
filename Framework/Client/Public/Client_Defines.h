#pragma once

namespace Client 
{
	static const unsigned int g_iWinCX = 1280;
	static const unsigned int g_iWinCY = 720;

	enum LEVEL { LEVEL_STATIC, LEVEL_LOADING, LEVEL_LOGO, LEVEL_GAMEPLAY, LEVEL_END };
}



#define CUSTOM_FVF (D3DFVF_XYZ)

extern HWND g_hWnd;

using namespace Client;