#pragma once

/* 화면에 그려져야할 객체들을 그리는 순서대로 모아서 관리하낟.  */
/* 가지고 있는 객체들의 렌더함수를 호출해주낟. */

#include "Component.h"
#include "Camera.h"
BEGIN(Engine)

class ENGINE_DLL CThirdPersonCamera final : public CCamera
{
private:
	CThirdPersonCamera(LPDIRECT3DDEVICE9 pGraphic_Device);
	CThirdPersonCamera(const CThirdPersonCamera& Prototype);
	virtual ~CThirdPersonCamera() = default;
public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Render(float fWinCX, float fWinCY);
	virtual HRESULT		Tick_Camera(D3DXMATRIX & _mat);

public:
	static CThirdPersonCamera* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END