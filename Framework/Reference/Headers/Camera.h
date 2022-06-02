#pragma once

/* 화면에 그려져야할 객체들을 그리는 순서대로 모아서 관리하낟.  */
/* 가지고 있는 객체들의 렌더함수를 호출해주낟. */

#include "Component.h"
#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL CCamera abstract : public CComponent
{
protected:
	CCamera(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCamera(const CCamera& Prototype);
	virtual ~CCamera() = default;
public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
public:
	static CCamera*	Get_MainCamera();
	static HRESULT	Set_MainCamera(CCamera * _pCamera);
public:
	virtual HRESULT		Tick_Camera(D3DXMATRIX& _mat) = 0;
	virtual HRESULT		Render(float fWinCX, float fWinCY) = 0;
protected:
	static CCamera* g_pMainCamera;
protected:
	_float3 m_vOffset;
	D3DXMATRIX	m_matView;
	D3DXMATRIX	m_matProj;
public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END