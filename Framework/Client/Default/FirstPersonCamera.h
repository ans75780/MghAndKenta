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
private: /* 현재 객체에게 필요한 컴포넌트를 복제해온다. */
	HRESULT SetUp_Components();
public:
	static CFirstPersonCamera* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CFirstPersonCamera* Clone(void* pArg) override;
	virtual void Free() override;
};

END
