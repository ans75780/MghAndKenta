#pragma once

/* ȭ�鿡 �׷������� ��ü���� �׸��� ������� ��Ƽ� �����ϳ�.  */
/* ������ �ִ� ��ü���� �����Լ��� ȣ�����ֳ�. */

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