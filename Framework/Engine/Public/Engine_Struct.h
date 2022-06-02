#pragma once

namespace Engine
{
	typedef struct tagVertex
	{
		_float		x;
		_float		y;
		_float		z;


		tagVertex(float _x, float _y, float _z)
			:x(_x),y(_y),z(_z)
		{

		}


	}VTX;

	typedef struct tagVertex_Texture
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR2		vTexUV;
	}VTXTEX;


	typedef struct tagGraphicDesc
	{
		unsigned int iWinCX, iWinCY; 
		HWND	hWnd;
		bool	isWindowMode;
	}GRAPHICDESC;
}
