#pragma once


#include "Client_Defines.h"
#include "Camera.h"

BEGIN(Engine)
class CTransform;
END

BEGIN(Client)
class CFirstPersonCamera : public CCamera
{
private:
	CFirstPersonCamera(LPDIRECT3DDEVICE9 pGraphic_Device);
	CFirstPersonCamera(const CFirstPersonCamera& Prototype);
	virtual ~CFirstPersonCamera() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
private: /* ���� ��ü���� �ʿ��� ������Ʈ�� �����ؿ´�. */
	HRESULT SetUp_Components();
public:
	static CFirstPersonCamera* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CFirstPersonCamera* Clone(void* pArg) override;
	virtual void Free() override;
};

END
